#ifndef BOOKMARKFORM_H
#define BOOKMARKFORM_H

#include "CustomListWidget.h"
#include <DPushButton>

#include <QVBoxLayout>
#include <QMap>
#include <QStringList>
#include <QThread>

#include "BookMarkItemWidget.h"
#include "subjectObserver/CustomWidget.h"
#include "docview/docummentproxy.h"
#include "application.h"

/**
 * @brief The BookMarkWidget class
 * @brief   书签  列表数据
 */

class BookMarkWidget;

class LoadBookMarkThread : public QThread
{
    Q_OBJECT
public:
    LoadBookMarkThread(QObject *parent = nullptr);

signals:
    void sigLoadImage(const int &, const QImage &);

public:
    inline void setBookMark(BookMarkWidget *bookMarkW)
    {
        m_pBookMarkWidget = bookMarkW;
    }

    inline void setBookMarks(const int &count)
    {
        m_bookMarks = count;
    }

    void stopThreadRun();

protected:
    void run() Q_DECL_OVERRIDE;

private:
    BookMarkWidget *m_pBookMarkWidget = nullptr;
    int m_bookMarks   = 0;   // 书签总数
    int m_nStartIndex = 0;   // 加载图片起始位置
    int m_nEndIndex   = 19;  // 加载图片结束位置
    bool m_isRunning = true; // 运行状态
};

class BookMarkWidget : public CustomWidget
{
    Q_OBJECT

public:
    BookMarkWidget(CustomWidget *parent = nullptr);
    ~BookMarkWidget() Q_DECL_OVERRIDE;

signals:
    void sigOpenFileOk();
    void sigDeleteBookItem(const int &);
    void sigAddBookMark(const int &);
    void sigCloseFile();
    void sigDelBKItem();

private slots:
    void slotAddBookMark();
    void slotAddBookMark(const int &);
    void slotOpenFileOk();
    void slotDocFilePageChanged(int);
    void slotDeleteBookItem(const int &);
    void slotCloseFile();
    void slotLoadImage(const int &, const QImage &);
    void slotDelBkItem();
    void slotUpdateTheme();

protected:
    void initWidget() Q_DECL_OVERRIDE;

private:
    void initConnection();
    QListWidgetItem *addBookMarkItem(const int &);
    void setSelectItemBackColor(QListWidgetItem *);
    void deleteIndexPage(const int &pageIndex);

public:
    // IObserver interface
    int dealWithData(const int &, const QString &) Q_DECL_OVERRIDE;
    int getBookMarkPage(const int &index);

private:
    CustomListWidget    *m_pBookMarkListWidget = nullptr;
    DPushButton         *m_pAddBookMarkBtn = nullptr;
    LoadBookMarkThread  m_loadBookMarkThread;
};

#endif // BOOKMARKFORM_H
