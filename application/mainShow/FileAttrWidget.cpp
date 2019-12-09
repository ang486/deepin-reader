#include "FileAttrWidget.h"

#include <DFontSizeManager>
#include <DFrame>
#include <DWindowCloseButton>
#include <QFileInfo>
#include "AttrScrollWidget.h"
#include "controller/DataManager.h"
#include "frame/DocummentFileHelper.h"

#include "CustomControl/DFMGlobal.h"

FileAttrWidget::FileAttrWidget(DWidget *parent)
    : DAbstractDialog(parent)
{
    setAttribute(Qt::WA_ShowModal, true);  //  模态对话框， 属性设置
    setAttribute(Qt::WA_DeleteOnClose);
    setFixedSize(QSize(300, 642));

    m_pVBoxLayout = new QVBoxLayout;
    m_pVBoxLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(m_pVBoxLayout);

    initWidget();
}

//  各个 对应的 label 赋值
void FileAttrWidget::setFileAttr()
{
    auto dproxy = DocummentFileHelper::instance();
    if (nullptr == dproxy) {
        return;
    }

    QImage image;
    bool rl = dproxy->getImage(0, image, 92, 111);
    if (rl) {
        //        labelImage->setPixmap(QPixmap::fromImage(image));
        if (frameImage) {
            //            frameImage->setBackgroundPix(QPixmap::fromImage(image));
            frameImage->setBackgroundPix(QPixmap::fromImage(image));
        }
    }

    QString filePath = DataManager::instance()->strOnlyFilePath();
    QFileInfo info(filePath);
    QString szTitle = info.fileName();

    addTitleFrame(szTitle);

    m_pVBoxLayout->addSpacing(35);

    QFrame *infoframe = new QFrame(this);
    infoframe->setFrameShape(QFrame::NoFrame);
    QVBoxLayout *scrollWidgetLayout = new QVBoxLayout;
    scrollWidgetLayout->setContentsMargins(10, 0, 10, 10);
    infoframe->setLayout(scrollWidgetLayout);

    auto scroll = new DScrollArea;
    QPalette palette = scroll->viewport()->palette();
    palette.setBrush(QPalette::Background, Qt::NoBrush);
    scroll->viewport()->setPalette(palette);

    scroll->viewport()->setContentsMargins(0, 0, 0, 0);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll->setWidget(infoframe);
    scroll->setWidgetResizable(true);

    QVBoxLayout *scrolllayout = new QVBoxLayout;
    scrolllayout->setContentsMargins(0, 0, 3, 0);
    scrolllayout->addWidget(scroll);

    qobject_cast<QVBoxLayout *>(scroll->widget()->layout())->insertWidget(0, new AttrScrollWidget);

    m_pVBoxLayout->addLayout(scrolllayout, 10);
}

void FileAttrWidget::addTitleFrame(const QString &sData)
{
    QFrame *m_textShowFrame = new QFrame(this);

    QFont font = DFontSizeManager::instance()->get(DFontSizeManager::T8);
    QString t = DFMGlobal::elideText(sData, QSize(300, 60), QTextOption::WrapAnywhere, font,
                                     Qt::ElideMiddle, 0);
    QStringList labelTexts = t.split("\n");
    const int maxLineCount = 3;

    int textHeight = 0;
    QVBoxLayout *textShowLayout = new QVBoxLayout;

    for (int i = 0; i < labelTexts.length(); i++) {
        if (i > (maxLineCount - 1)) {
            break;
        }
        QString labelText = labelTexts.at(i);
        QLabel *label = new QLabel(labelText, m_textShowFrame);
        DFontSizeManager::instance()->bind(label, DFontSizeManager::T8);

        label->setAlignment(Qt::AlignHCenter);
        QHBoxLayout *hLayout = new QHBoxLayout;

        textHeight += label->fontInfo().pixelSize() + 10;

        hLayout->addStretch(1);
        hLayout->addWidget(label);
        if (i < (labelTexts.length() - 1) && i != (maxLineCount - 1)) {
            if (label->fontMetrics().width(labelText) > (300 - 10)) {
                label->setFixedWidth(300);
            }
        } else {
            // the final line of file name label, with a edit btn.
            if (labelTexts.length() >= maxLineCount) {
                for (int idx = i + 1; idx < labelTexts.length(); idx++) {
                    labelText += labelTexts.at(idx);
                }
            }

            if (label->fontMetrics().width(labelText) > 300 &&
                labelTexts.length() >= maxLineCount) {
                labelText = label->fontMetrics().elidedText(labelText, Qt::ElideMiddle, 300);
            }
            label->setText(labelText);
            hLayout->addSpacing(2);
        }
        textShowLayout->addLayout(hLayout);
        hLayout->addStretch(1);
    }

    textShowLayout->setContentsMargins(0, 0, 0, 0);
    textShowLayout->setSpacing(0);
    m_textShowFrame->setLayout(textShowLayout);
    textShowLayout->addStretch(1);

    m_textShowFrame->setFixedHeight(textHeight);

    m_pVBoxLayout->addWidget(m_textShowFrame);
}

void FileAttrWidget::showScreenCenter()
{
    setFileAttr();

    Dtk::Widget::moveToCenter(this);
    this->show();
}

void FileAttrWidget::initWidget()
{
    initCloseBtn();

    initImageLabel();
}

void FileAttrWidget::initCloseBtn()
{
    auto layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addStretch(1);

    auto closeButton = new DWindowCloseButton(this);
    closeButton->setFixedSize(QSize(50, 50));
    closeButton->setIconSize(QSize(50, 50));
    closeButton->setToolTip(tr("close"));
    connect(closeButton, &DWindowCloseButton::clicked, this, &FileAttrWidget::slotBtnCloseClicked);

    layout->addWidget(closeButton);

    m_pVBoxLayout->addItem(layout);
}

void FileAttrWidget::initImageLabel()
{
    frameImage = new /*ImageFrame*/ ImageLabel(this);
    frameImage->setFixedSize(94, 113);

    auto vlayout = new QVBoxLayout;
    vlayout->setContentsMargins(104, 6, 0, 14);
    //    vlayout->setSpacing(10);
    vlayout->addWidget(/*labelImage*/ frameImage);

    m_pVBoxLayout->addItem(vlayout);
}

void FileAttrWidget::slotBtnCloseClicked()
{
    this->close();
}
