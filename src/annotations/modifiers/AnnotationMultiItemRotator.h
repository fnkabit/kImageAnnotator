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

#ifndef KIMAGEANNOTATOR_ANNOTATIONMULTIITEMROTATOR_H
#define KIMAGEANNOTATOR_ANNOTATIONMULTIITEMROTATOR_H

#include <QGraphicsItemGroup>
#include <QGraphicsScene>

#include "AnnotationItemRotator.h"

namespace kImageAnnotator {

class ZoomValueProvider;

class AnnotationMultiItemRotator : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit AnnotationMultiItemRotator(ZoomValueProvider *zoomValueProvider);
    ~AnnotationMultiItemRotator() override = default;
    QRectF boundingRect() const override;
    void attachTo(const QList<AbstractAnnotationItem *>& items);
    void detach();
    void grabHandle(const QPointF &pos);
    void moveHandle(const QPointF &pos);
    void releaseHandle();
    bool isRotating() const;
    void refresh();
    void update();
    bool hasItemsAttached() const;
    Qt::CursorShape cursorForPos(const QPointF &pos);
    Qt::CursorShape cursorForCurrentHandle();
    void hideCurrentRotator();
    void showCurrentRotator();

signals:
    void newCommand(RotateCommand *rotate) const;

private:
    ZoomValueProvider *mZoomValueProvider;
    QHash<AbstractAnnotationItem *, AnnotationItemRotator *> mItemToRotate;
    AnnotationItemRotator *mCurrentRotator;

    AnnotationItemRotator *getRotatorForItem(AbstractAnnotationItem *item);
    void showRotator(AnnotationItemRotator *rotator);
    void hideRotator(QGraphicsItem *rotator);
    AnnotationItemRotator *castToRotator(QGraphicsItem *item) const;
};

} // namespace kImageAnnotator

#endif // KIMAGEANNOTATOR_ANNOTATIONMULTIITEMROTATOR_H
