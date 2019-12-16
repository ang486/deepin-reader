#include "LeftSidebarWidget.h"
#include <DStackedWidget>
#include <QButtonGroup>
#include <QVBoxLayout>

#include "controller/DataManager.h"
#include "pdfControl/BookMarkWidget.h"
#include "pdfControl/BufferWidget.h"
#include "pdfControl/NotesWidget.h"
#include "pdfControl/SearchResWidget.h"
#include "pdfControl/ThumbnailWidget.h"

#include "MainOperationWidget.h"
#include "controller/AppSetting.h"

LeftSidebarWidget::LeftSidebarWidget(CustomWidget *parent)
    : CustomWidget("LeftSidebarWidget", parent)
{
    resize(LEFTNORMALWIDTH, this->height());
    setMinimumWidth(LEFTMINWIDTH);
    setMaximumWidth(LEFTMAXWIDTH);

    initWidget();
    initConnections();

    slotWidgetVisible(0);  //  默认 隐藏
    slotUpdateTheme();
}

void LeftSidebarWidget::slotStackSetCurIndex(const int &iIndex)
{
    AppSetting::instance()->setKeyValue(KEY_WIDGET, QString("%1").arg(iIndex));

    auto pWidget = this->findChild<DStackedWidget *>();
    if (pWidget) {
        if (WIDGET_SEARCH > iIndex) {
            DataManager::instance()->setCurrentWidget(iIndex);
            auto opWidget = this->findChild<MainOperationWidget *>();
            if (opWidget) {
                opWidget->setOperatAction(iIndex);
            }
        }
        pWidget->setCurrentIndex(iIndex);
    }
}

void LeftSidebarWidget::slotWidgetVisible(const int &nVis)
{
    this->setVisible(nVis);
}

void LeftSidebarWidget::slotUpdateTheme()
{
    updateWidgetTheme();
}

void LeftSidebarWidget::initConnections()
{
    connect(this, SIGNAL(sigStackSetCurIndex(const int &)),
            SLOT(slotStackSetCurIndex(const int &)));
    connect(this, SIGNAL(sigWidgetVisible(const int &)), SLOT(slotWidgetVisible(const int &)));
    connect(this, SIGNAL(sigUpdateTheme()), SLOT(slotUpdateTheme()));
}

void LeftSidebarWidget::initWidget()
{
    auto pVBoxLayout = new QVBoxLayout;
    pVBoxLayout->setContentsMargins(0, 0, 0, 0);
    pVBoxLayout->setSpacing(0);
    this->setLayout(pVBoxLayout);

    auto pStackedWidget = new DStackedWidget;
    pStackedWidget->insertWidget(0, new ThumbnailWidget(this));
    pStackedWidget->insertWidget(1, new BookMarkWidget(this));
    pStackedWidget->insertWidget(2, new NotesWidget(this));
    pStackedWidget->insertWidget(3, new SearchResWidget(this));
    pStackedWidget->insertWidget(4, new BufferWidget(this));
    pStackedWidget->setCurrentIndex(0);

    for (int index = 0; index < pStackedWidget->count(); ++index) {
        auto widget = pStackedWidget->widget(index);
        if (widget) {
            widget->setMinimumWidth(LEFTMINWIDTH);
            widget->setMaximumWidth(LEFTMAXWIDTH);
            widget->adjustSize();
            widget->resize(226, this->height());
        }
    }

    pVBoxLayout->addWidget(pStackedWidget);
    pVBoxLayout->addWidget(new MainOperationWidget, 0, Qt::AlignBottom);
}

int LeftSidebarWidget::dealWithData(const int &msgType, const QString &msgContent)
{
    if (msgType == MSG_SWITCHLEFTWIDGET) {  //切换页面
        emit sigStackSetCurIndex(msgContent.toInt());
        return ConstantMsg::g_effective_res;
    }
    if (msgType == MSG_SLIDER_SHOW_STATE) {  //  控制 侧边栏显隐
        emit sigWidgetVisible(msgContent.toInt());
        return ConstantMsg::g_effective_res;
    } else if (msgType == MSG_OPERATION_UPDATE_THEME) {
        emit sigUpdateTheme();
    }

    return 0;
}

void LeftSidebarWidget::resizeEvent(QResizeEvent *event)
{
    CustomWidget::resizeEvent(event);

    update();
}
