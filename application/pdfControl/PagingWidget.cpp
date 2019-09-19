#include "PagingWidget.h"
#include <QDebug>

PagingWidget::PagingWidget(CustomWidget *parent) :
    CustomWidget("PagingWidget", parent)
{
    resize(250, 20);
    initWidget();
}

void PagingWidget::initWidget()
{
    m_pTotalPagesLab = new DLabel(this);
    m_pTotalPagesLab->setText(QString("/xxx页"));
    m_pTotalPagesLab->setMinimumWidth(80);

    m_pPrePageBtn = new DImageButton(this);
    m_pPrePageBtn->setText(tr("<"));
    m_pPrePageBtn->setFixedSize(QSize(40, 40));

    m_pNextPageBtn = new DImageButton(this);
    m_pNextPageBtn->setText(tr(">"));
    m_pNextPageBtn->setFixedSize(QSize(40, 40));

    connect(m_pPrePageBtn, SIGNAL(clicked()), SLOT(slotPrePage()));
    connect(m_pNextPageBtn, SIGNAL(clicked()), SLOT(slotNextPage()));

    m_pJumpPageSpinBox = new DSpinBox(this);
    m_pJumpPageSpinBox->setRange(1, 100);
    m_pJumpPageSpinBox->setValue(1);
    m_pJumpPageSpinBox->setMinimumWidth(50);
    m_pJumpPageSpinBox->installEventFilter(this);
    m_pJumpPageSpinBox->setWrapping(true);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_pJumpPageSpinBox);
    hLayout->addWidget(m_pTotalPagesLab);
    hLayout->addWidget(m_pPrePageBtn);
    hLayout->addWidget(m_pNextPageBtn);
    this->setLayout(hLayout);
}

bool PagingWidget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_pJumpPageSpinBox) {
        if (event->type() == QEvent::KeyPress) {

            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {

                int index = m_pJumpPageSpinBox->value() - 1;
                if (this->getPreRowVal() != index) {

                    this->setPreRowVal(index);
                    setCurrentPageValue(index);
                    sendMsg(MSG_THUMBNAIL_JUMPTOPAGE, QString::number(index));
                }
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void PagingWidget::setCurrentPage(const int &index)
{
    int t_page = index - 1;

    this->setPreRowVal(t_page);

    m_pJumpPageSpinBox->setValue(index);

    DocummentProxy::instance()->pageJump(t_page);
}

void PagingWidget::createBtn(DImageButton *btn, QWidget *parent, const QString &text, const QString &btnName, const QString &normalPic, const QString &hoverPic, const QString &pressPic, const QString &checkedPic, const char *member, bool checkable, bool checked)
{
    btn = new DImageButton(normalPic, hoverPic, pressPic, checkedPic, parent);
    btn->setText(text);
    btn->setFixedSize(QSize(40, 40));
    btn->setToolTip(btnName);
    btn->setCheckable(checkable);

    connect(btn, SIGNAL(checkedChanged()), member);
}

void PagingWidget::setTotalPages(int pages)
{
    m_totalPage = pages;
    m_currntPage = FIRSTPAGES;
    m_pTotalPagesLab->setText(QString("/%1页").arg(pages));

    m_pJumpPageSpinBox->setRange(1, (pages < 1) ? 1 : pages);
}

int PagingWidget::dealWithData(const int &msgType, const QString &msgContant)
{
    switch (msgType) {
    case MSG_OPERATION_FIRST_PAGE:              //  第一页
        qDebug() << "   MSG_OPERATION_FIRST_PAGE  ";
        setCurrentPageValue(0);
        return ConstantMsg::g_effective_res;
    case MSG_OPERATION_PREV_PAGE:               //  上一页
        qDebug() << "   MSG_OPERATION_PREV_PAGE  ";
        slotPrePage();
        return ConstantMsg::g_effective_res;
    case MSG_OPERATION_NEXT_PAGE:               //  下一页
        qDebug() << "   MSG_OPERATION_NEXT_PAGE  ";
        slotNextPage();
        return ConstantMsg::g_effective_res;
    case MSG_OPERATION_END_PAGE:                //  最后一页
        qDebug() << "   MSG_OPERATION_END_PAGE  ";
        setCurrentPageValue(m_totalPage - FIRSTPAGES);
        return ConstantMsg::g_effective_res;
    }
    return 0;
}

void PagingWidget::slotPrePage()
{
    if (m_currntPage == FIRSTPAGES) {
        return;
    }
    int t_page = --m_currntPage;

    m_pNextPageBtn->setEnabled(true);
    if (t_page <= FIRSTPAGES) {
        m_pPrePageBtn->setEnabled(false);
    }
    if (t_page < FIRSTPAGES) {
        m_currntPage = FIRSTPAGES;
        return;
    }
    m_currntPage = t_page;

    m_pJumpPageSpinBox->setValue(m_currntPage);

    sendMsg(MSG_THUMBNAIL_JUMPTOPAGE, QString::number(m_currntPage - FIRSTPAGES));
}

void PagingWidget::slotNextPage()
{
    if (m_currntPage == m_totalPage) {
        return;
    }
    int t_page = ++m_currntPage;

    m_pPrePageBtn->setEnabled(true);
    if (t_page >= m_totalPage) {
        m_pNextPageBtn->setEnabled(false);
    }
    if (t_page > m_totalPage) {
        m_currntPage = m_totalPage;
        return;
    }
    m_currntPage = t_page;

    m_pJumpPageSpinBox->setValue(m_currntPage);

    sendMsg(MSG_THUMBNAIL_JUMPTOPAGE, QString::number(m_currntPage - FIRSTPAGES));
}

void PagingWidget::setCurrentPageValue(const int &index)
{
    setPageValue(index);

    setCurrentPage(m_currntPage);
}

void PagingWidget::setPageValue(const int &index)
{
    m_currntPage = index + FIRSTPAGES;

    if (m_currntPage <= FIRSTPAGES) {
        m_pPrePageBtn->setEnabled(false);
        m_pNextPageBtn->setEnabled(true);
    } else if (m_currntPage >= m_totalPage && m_totalPage != FIRSTPAGES) {
        m_pPrePageBtn->setEnabled(true);
        m_pNextPageBtn->setEnabled(false);
    } else {
        m_pPrePageBtn->setEnabled(true);
        m_pNextPageBtn->setEnabled(true);
    }

    if (m_totalPage == FIRSTPAGES) {
        m_pPrePageBtn->setEnabled(false);
        m_pNextPageBtn->setEnabled(false);
    }

    m_pJumpPageSpinBox->setValue(m_currntPage);
}
