/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     leiyu <leiyu@uniontech.com>
*
* Maintainer: leiyu <leiyu@uniontech.com>
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
#ifndef TIPSWIDGET_H
#define TIPSWIDGET_H

#include <DWidget>
#include <QTimer>

DWIDGET_USE_NAMESPACE
class TipsWidget : public DWidget
{
    Q_OBJECT
public:
    explicit TipsWidget(QWidget *parent = nullptr);

    void setText(const QString &text);
    void setAlignment(Qt::Alignment);
    void setLeftRightMargin(int margin);
    void setTopBottomMargin(int margin);
    void setMaxLineCount(int maxLinecnt);
    void setAutoChecked(bool autoChecked);

private:
    void initWidget();
    void adjustContent(const QString &text);

protected:
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

private slots:
    void onUpdateTheme();
    void onTimeOut();

private:
    QString m_text;
    int m_lrMargin;
    int m_tbMargin;
    int m_maxLineCount;
    Qt::Alignment m_alignment;

    QTimer m_timer;
    QWidget *m_parent;
    bool m_autoChecked = false;
};

#endif // TIPSWIDGET_H
