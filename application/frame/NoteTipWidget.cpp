#include "NoteTipWidget.h"
#include "CustomControl/CustomClickLabel.h"
#include <QHBoxLayout>
#include <DTextEdit>
#include <DPlatformWindowHandle>

NoteTipWidget::NoteTipWidget(CustomWidget *parnet)
    : CustomWidget("NoteTipWidget", parnet)
    , m_iwidth(254)
{
    setWindowFlags(Qt::ToolTip);
    //  setFixedSize(200, 50);
    setFixedWidth(m_iwidth);
    DPlatformWindowHandle handle(this);
    int radius = 8;
    handle.setWindowRadius(radius);
    setWindowOpacity(0.97);

    initWidget();
//    initConnection();
    slotUpdateTheme();
}

void NoteTipWidget::setTipContent(const QString &content)
{
    DTextEdit *label = this->findChild<DTextEdit *>();
    if (label) {
        QFontMetrics fm(label->font());
        int pixelsWide = fm.horizontalAdvance(content);
        int pixelsHigh = fm.height();
//        qDebug() << pixelsWide << pixelsHigh << fm.lineSpacing();
        QString strcontent;
        //判断是否超过十行
        if (pixelsWide > (m_iwidth - 16) * 10) {
            setFixedHeight(pixelsHigh * 11 + 8);
            strcontent = label->fontMetrics().elidedText(content, Qt::ElideRight, (m_iwidth - 16) * 10, Qt::TextWordWrap);
        } else {
            int line = pixelsWide / (m_iwidth - 16);
            line = line > 2 ? line + 2 : 3;
            setFixedHeight(pixelsHigh * line + 8);
            strcontent = content;
        }
        label->setFixedWidth(m_iwidth - 16);
        label->setText(strcontent);
    }
}

void NoteTipWidget::initConnection()
{
    connect(this, SIGNAL(sigUpdateTheme()), SLOT(slotUpdateTheme()));
}

void NoteTipWidget::slotUpdateTheme()
{
    updateWidgetTheme();
}

int NoteTipWidget::dealWithData(const int &msgType, const QString &)
{
    if (msgType == MSG_OPERATION_UPDATE_THEME) {
//        emit sigUpdateTheme();
    }
    return 0;
}

void NoteTipWidget::initWidget()
{
    auto label = new DTextEdit(this);
    label->setFrameShape(QFrame::NoFrame);
    label->setReadOnly(true);
    label->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    label->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    label->setWordWrapMode(QTextOption::WrapAnywhere /*WordWrap*/);
    auto layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(label);

    this->setLayout(layout);
}