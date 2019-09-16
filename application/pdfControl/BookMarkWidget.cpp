#include "BookMarkWidget.h"
#include <QDebug>
#include "application.h"

BookMarkWidget::BookMarkWidget(CustomWidget *parent) :
    CustomWidget("BookMarkWidget", parent)
{
    m_pVBoxLayout = new QVBoxLayout;
    m_pVBoxLayout->setContentsMargins(0, 0, 0, 0);
    m_pVBoxLayout->setSpacing(0);
    this->setLayout(m_pVBoxLayout);

    initWidget();

    initConnection();
}

void BookMarkWidget::slotShowSelectItem(QListWidgetItem *item)
{
    m_pCurrentItem = item;
}

void BookMarkWidget::slotAddBookMark()
{
    int page = DocummentProxy::instance()->currentPageNo();

    QImage image;

    DocummentProxy::instance()->getImage(page, image, 130, 150);
}

//  打开文件成功，　获取该文件的书签数据
void BookMarkWidget::slotOpenFileOk()
{
    QString sAllPages = dApp->dbM->getBookMarks();
    QStringList sPageList = sAllPages.split(",", QString::SkipEmptyParts);
    foreach (QString s, sPageList) {
        int nPage = s.toInt();

        m_pAllPageList.append(nPage);

        QImage image;

        DocummentProxy::instance()->getImage(nPage, image, 130, 150);

        addBookMarkItem(image, nPage);
    }
}

void BookMarkWidget::initWidget()
{
    m_pBookMarkListWidget = new DListWidget;
    m_pBookMarkListWidget->setSpacing(10);
    //设置自动适应布局调整（Adjust适应，Fixed不适应），默认不适应
    m_pBookMarkListWidget->setResizeMode(QListWidget::Adjust);

    m_pAddBookMarkBtn = new DImageButton;
    m_pAddBookMarkBtn->setFixedSize(QSize(250, 50));
    m_pAddBookMarkBtn->setText(tr("adding bookmark"));
    connect(m_pAddBookMarkBtn, SIGNAL(clicked()), this, SLOT(slotAddBookMark()));

    m_pVBoxLayout->addWidget(m_pBookMarkListWidget);
    m_pVBoxLayout->addWidget(m_pAddBookMarkBtn);
}

void BookMarkWidget::keyPressEvent(QKeyEvent *e)
{
    QString key = Utils::getKeyshortcut(e);

    if (key == "Del") {
        dltItem();
//        qDebug() << "dlt bookmark item by key";
    }  else {
        // Pass event to CustomWidget continue, otherwise you can't type anything after here. ;)
        CustomWidget::keyPressEvent(e);
    }
}

void BookMarkWidget::initConnection()
{
    connect(this, SIGNAL(sigOpenFileOk()), this, SLOT(slotOpenFileOk()));
    connect(m_pBookMarkListWidget, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(slotShowSelectItem(QListWidgetItem *)));
}

void BookMarkWidget::dltItem()
{
    if (m_pCurrentItem != nullptr) {
        BookMarkItemWidget *t_widget = reinterpret_cast<BookMarkItemWidget *>(m_pBookMarkListWidget->itemWidget(m_pCurrentItem));

        if (t_widget) {
            int page = t_widget->PageNumber();

            t_widget->deleteLater();
            t_widget = nullptr;
        }
    }
}

void BookMarkWidget::addBookMarkItem(const QImage &image, const int &page)
{
    BookMarkItemWidget *t_widget = new BookMarkItemWidget(this);
    t_widget->setItemImage(image);
    t_widget->setPageNumber(page);
    t_widget->setMinimumSize(QSize(250, 150));

    QListWidgetItem *item = new QListWidgetItem(m_pBookMarkListWidget);
    item->setFlags(Qt::ItemIsSelectable);
    item->setSizeHint(QSize(250, 150));

    m_pBookMarkListWidget->addItem(item);
    m_pBookMarkListWidget->setItemWidget(item, t_widget);
}

int BookMarkWidget::dealWithData(const int &msgType, const QString &msgContent)
{
    if (MSG_BOOKMARK_DLTITEM == msgType) {
        dltItem();
        qDebug() << "dlt bookmark item by menu";
        return ConstantMsg::g_effective_res;
    }

    if (MSG_OPERATION_OPEN_FILE_OK == msgType) {
        emit sigOpenFileOk();
    }

    return 0;
}
