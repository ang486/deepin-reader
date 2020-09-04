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
#include "TipsWidget.h"

#include <DPlatformWindowHandle>
#include <DGuiApplicationHelper>
#include <DFontSizeManager>

#include <QPainter>
#include <QDebug>

TipsWidget::TipsWidget(QWidget *parent) : DWidget(parent)
{
    m_parent = parent;
    setWindowFlags(Qt::ToolTip);
    initWidget();
    onUpdateTheme();
}

void TipsWidget::initWidget()
{
    m_tbMargin = 8;
    m_lrMargin = 10;
    m_maxLineCount = 10;
    m_alignment = Qt::AlignLeft | Qt::AlignVCenter;
    setFixedWidth(254);
    setWindowOpacity(0.97);
    DPlatformWindowHandle handle(this);
    handle.setWindowRadius(8);

    DFontSizeManager::instance()->bind(this, DFontSizeManager::T8);
    connect(DGuiApplicationHelper::instance(), &DGuiApplicationHelper::themeTypeChanged, this, &TipsWidget::onUpdateTheme);

    m_timer.setInterval(100);
    connect(&m_timer, &QTimer::timeout, this, &TipsWidget::onTimeOut);
}

void TipsWidget::onUpdateTheme()
{
    DPalette plt = Dtk::Gui::DGuiApplicationHelper::instance()->applicationPalette();
    plt.setColor(Dtk::Gui::DPalette::Background, plt.color(Dtk::Gui::DPalette::Base));
    setPalette(plt);
}

void TipsWidget::setText(const QString &text)
{
    m_text = text;
    m_text.replace(QChar('\n'), QString(""));
    m_text.replace(QChar('\t'), QString(""));
    update();
}

void TipsWidget::setAlignment(Qt::Alignment alignment)
{
    m_alignment = alignment;
    update();
}

void TipsWidget::setLeftRightMargin(int margin)
{
    m_lrMargin = margin;
    update();
}

void TipsWidget::setTopBottomMargin(int margin)
{
    m_tbMargin = margin;
    update();
}

void TipsWidget::setMaxLineCount(int maxLinecnt)
{
    m_maxLineCount = maxLinecnt;
    update();
}

void TipsWidget::paintEvent(QPaintEvent *event)
{
    DWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    QTextOption option;
    const QString &text = m_text;
    adjustContent(text);
    option.setAlignment(m_alignment);
    option.setWrapMode(QTextOption::WrapAnywhere);
    painter.setPen(QPen(DTK_NAMESPACE::Gui::DGuiApplicationHelper::instance()->applicationPalette().text().color()));
    painter.drawText(QRect(m_lrMargin, m_tbMargin, this->width() -  2 * m_lrMargin, this->height() -  2 * m_tbMargin), text, option);
}

void TipsWidget::adjustContent(const QString &text)
{
    QFontMetricsF fontMetris(this->font());
    int wordHeight = static_cast<int>(fontMetris.boundingRect(QRectF(0, 0, this->width() - 2 * m_lrMargin, 0),
                                                              static_cast<int>(m_alignment | Qt::TextWrapAnywhere), text).height() + 2 * m_tbMargin);
    if (this->height() == wordHeight) return;
    setFixedHeight(wordHeight);
}

void TipsWidget::showEvent(QShowEvent *event)
{
    DWidget::showEvent(event);
    if (m_autoChecked)
        m_timer.start();
}

void TipsWidget::hideEvent(QHideEvent *event)
{
    DWidget::hideEvent(event);
    m_timer.stop();
}

void TipsWidget::setAutoChecked(bool autoChecked)
{
    m_autoChecked = autoChecked;
}

void TipsWidget::onTimeOut()
{
    if (this->isVisible() && !m_parent->rect().contains(m_parent->mapFromGlobal(QCursor::pos()))) {
        this->hide();
    }
}
