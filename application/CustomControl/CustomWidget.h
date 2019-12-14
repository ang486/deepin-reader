#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <DFontSizeManager>
#include <DGuiApplicationHelper>
#include <DPalette>
#include <DWidget>

#include "controller/MsgSubject.h"
#include "controller/NotifySubject.h"
#include "subjectObserver/IObserver.h"
#include "subjectObserver/ModuleHeader.h"
#include "subjectObserver/MsgHeader.h"
#include "utils/utils.h"

#include <QDebug>

DWIDGET_USE_NAMESPACE

/**
 * @brief The CustomWidget class
 * @brief   封装 DWidget 和 观察者， 便于 继承 DWidget
 *          实现 相应的消息处理， 更关注于 对应的业务处理
 */

const int FIRST_LOAD_PAGES = 20;
const int LEFTMINWIDTH = 190;
const int LEFTMAXWIDTH = 380;

class CustomWidget : public DWidget, public IObserver
{
    Q_OBJECT
    Q_DISABLE_COPY(CustomWidget)

public:
    CustomWidget(const QString &, DWidget *parent = nullptr);
    ~CustomWidget() Q_DECL_OVERRIDE;

    //  主题更新信号
signals:
    void sigUpdateTheme();

protected:
    virtual void initWidget() = 0;
    void updateWidgetTheme();

protected:
    void sendMsg(const int &msgType, const QString &msgContent = "") Q_DECL_OVERRIDE;
    void notifyMsg(const int &msgType, const QString &msgContent = "") Q_DECL_OVERRIDE;
    void showScreenCenter();

protected:
    QList<int>      m_pMsgList;     //  需要处理的消息列表

private:
    MsgSubject *m_pMsgSubject = nullptr;
    NotifySubject *m_pNotifySubject = nullptr;
};

#endif  // CUSTOMWIDGET_H
