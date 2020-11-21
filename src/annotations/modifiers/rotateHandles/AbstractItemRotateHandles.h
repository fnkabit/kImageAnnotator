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

#ifndef KIMAGEANNOTATOR_ABSTRACTITEMROTATEHANDLES_H
#define KIMAGEANNOTATOR_ABSTRACTITEMROTATEHANDLES_H

#include "RotateHandle.h"
#include "src/annotations/items/AbstractAnnotationItem.h"
#include "src/common/helper/CursorHelper.h"

namespace kImageAnnotator {

class AbstractItemRotateHandles
{
public:
    AbstractItemRotateHandles();
    virtual ~AbstractItemRotateHandles() = default;
    virtual void update() = 0;
    virtual int indexOfHandleAt(const QPointF &pos) const;
    virtual int indexOfHandleWithAnchorAt(const QPointF &pos) const;
    virtual RotateHandle handle(int index) const;
    virtual QList<RotateHandle> handles() const;
    virtual Qt::CursorShape cursorForPos(const QPointF &pos) const;
    virtual Qt::CursorShape cursorForHandle(int index) const;
    double handleSize() const;
    void applyZoomValue(double value);

protected:
    QList<RotateHandle> mHandles;
    QList<Qt::CursorShape> mCursors;

    virtual void initHandles(int count, double zoomValue);
    virtual void initCursors() = 0;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_ABSTRACTITEMROTATEHANDLES_H
