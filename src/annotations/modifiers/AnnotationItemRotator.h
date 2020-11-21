/*
 * Copyright (C) 2020 Damir Porobic <damir.porobic@gmx.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef KIMAGEANNOTATOR_ANNOTATIONITEMROTATOR_H
#define KIMAGEANNOTATOR_ANNOTATIONITEMROTATOR_H

#include <QGraphicsWidget>

#include "rotateHandles/RotateHandlesFactory.h"
#include "src/annotations/undo/RotateCommand.h"
#include "src/annotations/core/ZoomValueProvider.h"

namespace kImageAnnotator {

class AnnotationItemRotator : public QGraphicsWidget
{
Q_OBJECT
public:
    AnnotationItemRotator(AbstractAnnotationItem *item, ZoomValueProvider *zoomValueProvider);
    ~AnnotationItemRotator() override;
    QRectF boundingRect() const override;
    void grabHandle(const QPointF &pos);
    void moveHandle(const QPointF &pos);
    void releaseHandle();
    bool isRotating() const;
    void refresh();
    bool isItemVisible() const;
    Qt::CursorShape cursorForPos(const QPointF &pos);
    Qt::CursorShape cursorForCurrentHandle();

signals:
    void newCommand(RotateCommand *rotate) const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    AbstractItemRotateHandles *mRotateHandles;
    AbstractAnnotationItem *mAnnotationItem;
    ZoomValueProvider *mZoomValueProvider;
    int mCurrentHandle;
    QPointF mClickOffset;

    void applyZoomValue(double value);
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ANNOTATIONITEMROTATOR_H
