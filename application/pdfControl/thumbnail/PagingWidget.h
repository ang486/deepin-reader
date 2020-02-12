/*
 * Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     duanxiaohui
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef PAGINGWIDGET_H
#define PAGINGWIDGET_H

#include <DSpinBox>
#include <DIconButton>
#include <DLineEdit>

#include <QIntValidator>
#include <QKeyEvent>
#include <QVBoxLayout>

#include "CustomControl/CustomWidget.h"
#include "CustomControl/CustomClickLabel.h"

/**
 * @brief The ThumbnailItemWidget class
 * @brief   显示的数字 比 实际的文档 多 1
 * @brief   跳转页窗体
 */

class PagingWidget : public CustomWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(PagingWidget)

public:
    explicit PagingWidget(CustomWidget *parent = nullptr);
    ~PagingWidget() Q_DECL_OVERRIDE;

signals:
    void sigDocFilePageChange(const QString &);
    void sigDocFileOpenOk();

private slots:
    void slotPrePage();
    void slotNextPage();
    void slotUpdateTheme();
    void SlotDocFilePageChange(const QString &);
    void SlotDocFileOpenOk();

protected:
    void initWidget() Q_DECL_OVERRIDE;
    bool eventFilter(QObject *watched, QEvent *event) Q_DECL_OVERRIDE;

private:
    void initConnections();

private:
    CustomClickLabel *m_pTotalPagesLab = nullptr;        // 当前文档总页数标签
    DIconButton *m_pPrePageBtn = nullptr;      // 按钮 前一页
    DIconButton *m_pNextPageBtn = nullptr;     // 按钮 后一页
//    DSpinBox *m_pJumpPageSpinBox = nullptr;    // 输入框 跳转页码
    DLineEdit *m_pJumpPageLineEdit = nullptr;  // 输入框 跳转页码
    int m_nMaxPage = 0;                        // 文档总页数

public:
    int dealWithData(const int &, const QString &) Q_DECL_OVERRIDE;
};

#endif // PAGINGWIDGET_H