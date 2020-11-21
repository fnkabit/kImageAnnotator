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

#include "AbstractItemRotateHandles.h"

namespace kImageAnnotator {

AbstractItemRotateHandles::AbstractItemRotateHandles()
{
}

int AbstractItemRotateHandles::indexOfHandleAt(const QPointF &pos) const
{
    for (auto handle : mHandles) {
        if (handle.contains(pos)) {
            return mHandles.indexOf(handle);
        }
    }
    return -1;
}

int AbstractItemRotateHandles::indexOfHandleWithAnchorAt(const QPointF &pos) const
{
    for (auto handle : mHandles) {
        if (handle.anchor() == pos) {
            return mHandles.indexOf(handle);
        }
    }
    return -1;
}

RotateHandle AbstractItemRotateHandles::handle(int index) const
{
    if (index < 0 || index >= mHandles.count()) {
        return RotateHandle();
    }

    return mHandles[index];
}

QList<RotateHandle> AbstractItemRotateHandles::handles() const
{
    return mHandles;
}

Qt::CursorShape AbstractItemRotateHandles::cursorForPos(const QPointF &pos) const
{
    auto index = indexOfHandleAt(pos);
    return cursorForHandle(index);
}

Qt::CursorShape AbstractItemRotateHandles::cursorForHandle(int index) const
{
    if (index == -1 || mCursors.isEmpty()) {
        return CursorHelper::defaultCursor();
    }

    return mCursors[index];
}

void AbstractItemRotateHandles::initHandles(int count, double zoomValue)
{
    mHandles.clear();
    for (auto i = 0; i < count; i++) {
        mHandles.append(RotateHandle(zoomValue));
    }
}

double AbstractItemRotateHandles::handleSize() const
{
    return mHandles.empty() ? 0.0 : mHandles.first().handleSize();
}

void AbstractItemRotateHandles::applyZoomValue(double value)
{
    for (auto &handle : mHandles) {
        handle.applyZoomValue(value);
    }
}

} // namespace kImageAnnotator
