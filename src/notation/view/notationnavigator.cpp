/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "notationnavigator.h"

#include "libmscore/system.h"

using namespace mu::notation;

NotationNavigator::NotationNavigator(QQuickItem* parent)
    : NotationPaintView(parent)
{
    setReadonly(true);
}

void NotationNavigator::load()
{
    initOrientation();
    initVisible();

    uiConfiguration()->currentThemeChanged().onNotify(this, [this]() {
        update();
    });

    NotationPaintView::load();
}

bool NotationNavigator::isVerticalOrientation() const
{
    return configuration()->canvasOrientation().val == framework::Orientation::Vertical;
}

PageList NotationNavigator::pages() const
{
    auto notation = globalContext()->currentNotation();
    if (!notation) {
        return {};
    }

    auto elements = notation->elements();
    if (!elements) {
        return {};
    }

    return elements->pages();
}

void NotationNavigator::rescale()
{
    PageList pages = this->pages();
    if (pages.empty()) {
        return;
    }

    const Page* lastPage = pages.back();

    qreal scaling = 1.0;

    if (isVerticalOrientation()) {
        qreal scoreWidth = lastPage->width();
        scaling = width() / scoreWidth;
    } else {
        qreal scoreHeight = lastPage->height();
        scaling = height() / scoreHeight;
    }

    if (qFuzzyIsNull(scaling)) {
        return;
    }

    setScaling(scaling, PointF());
}

void NotationNavigator::wheelEvent(QWheelEvent*)
{
}

void NotationNavigator::mousePressEvent(QMouseEvent* event)
{
    PointF logicPos = toLogical(event->pos());
    m_startMove = logicPos;
    if (m_cursorRect.contains(logicPos)) {
        return;
    }

    double dx = logicPos.x() - (m_cursorRect.x() + (m_cursorRect.width() / 2));
    double dy = logicPos.y() - (m_cursorRect.y() + (m_cursorRect.height() / 2));

    moveNotationRequested(-dx, -dy);
}

void NotationNavigator::mouseMoveEvent(QMouseEvent* event)
{
    PointF logicPos = toLogical(event->pos());
    PointF delta = logicPos - m_startMove;
    moveNotationRequested(-delta.x(), -delta.y());

    m_startMove = logicPos;
}

void NotationNavigator::moveCanvasToRect(const RectF& viewRect)
{
    RectF newViewRect = viewRect;
    RectF viewport = this->viewport();
    RectF notationContentRect = this->notationContentRect();

    qreal dx = 0;
    qreal dy = 0;

    if (isVerticalOrientation()) {
        newViewRect.setHeight(std::min(viewport.height(), newViewRect.height()));

        PointF top = newViewRect.topLeft();
        PointF bottom = newViewRect.bottomRight();

        if (!notationContentRect.contains(top) && !notationContentRect.contains(bottom)) {
            return;
        }

        if (viewport.top() > top.y()) {
            dy = top.y() - viewport.top();
        } else if (viewport.bottom() < bottom.y()) {
            dy = bottom.y() - viewport.bottom();
        }
    } else {
        newViewRect.setWidth(std::min(viewport.width(), newViewRect.width()));

        PointF left = newViewRect.topLeft();
        PointF right = newViewRect.bottomRight();

        if (!notationContentRect.contains(left) && !notationContentRect.contains(right)) {
            return;
        }

        if (viewport.left() > left.x()) {
            dx = left.x() - viewport.left();
        } else if (viewport.right() < right.x()) {
            dx = right.x() - viewport.right();
        }
    }

    moveCanvas(-dx, -dy);
}

void NotationNavigator::setCursorRect(const QRectF& rect)
{
    if (!rect.isValid()) {
        return;
    }

    RectF newCursorRect = notationContentRect().intersected(RectF::fromQRectF(rect));

    moveCanvasToRect(newCursorRect);

    m_cursorRect = newCursorRect;
    rescale();
    update();
}

int NotationNavigator::orientation() const
{
    return static_cast<int>(configuration()->canvasOrientation().val);
}

INotationPtr NotationNavigator::currentNotation() const
{
    return globalContext()->currentNotation();
}

void NotationNavigator::initOrientation()
{
    ValCh<framework::Orientation> orientation = configuration()->canvasOrientation();
    orientation.ch.onReceive(this, [this](framework::Orientation) {
        moveCanvasToPosition(PointF(0, 0));
        emit orientationChanged();
    });

    emit orientationChanged();
}

void NotationNavigator::initVisible()
{
    connect(this, &NotationNavigator::visibleChanged, [this]() {
        update();
    });
}

ViewMode NotationNavigator::notationViewMode() const
{
    auto notation = currentNotation();
    if (!notation) {
        return ViewMode::PAGE;
    }

    return notation->viewMode();
}

void NotationNavigator::paint(QPainter* painter)
{
    if (!isVisible()) {
        return;
    }

    NotationPaintView::paint(painter);
    paintCursor(painter);

    paintPageNumbers(painter);
}

void NotationNavigator::paintCursor(QPainter* painter)
{
    QColor color(configuration()->selectionColor());
    QPen pen(color, configuration()->borderWidth());
    painter->setPen(pen);
    painter->setBrush(QColor(color.red(), color.green(), color.blue(), configuration()->cursorOpacity()));

    painter->drawRect(m_cursorRect.toQRectF());
}

void NotationNavigator::paintPageNumbers(QPainter* painter)
{
    if (notationViewMode() != ViewMode::PAGE) {
        return;
    }

    constexpr int PAGE_NUMBER_FONT_SIZE = 2000;
    QFont font(QString::fromStdString(configuration()->fontFamily()), PAGE_NUMBER_FONT_SIZE);

    for (const Page* page : pages()) {
        painter->translate(page->pos().toQPointF());

        painter->setFont(font);
        painter->setPen(engravingConfiguration()->formattingMarksColor().toQColor());
        painter->drawText(page->bbox().toQRectF(), Qt::AlignCenter, QString("%1").arg(page->no() + 1));

        painter->translate(-page->pos().toQPointF());
    }
}
