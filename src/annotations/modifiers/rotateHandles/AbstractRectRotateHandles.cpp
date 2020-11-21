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

#include "AbstractRectRotateHandles.h"

namespace kImageAnnotator {

void AbstractRectRotateHandles::update()
{
    auto rect = getRect();
    auto offset = getOffset();
    mHandles[0].moveCenter(ShapeHelper::rectTopLeftWithOffset(rect, offset));
	mHandles[0].setAnchor(rect.topLeft());
	mHandles[1].moveCenter(ShapeHelper::rectTopRightWithOffset(rect, offset));
	mHandles[1].setAnchor(rect.topRight());
	mHandles[2].moveCenter(ShapeHelper::rectBottomRightWithOffset(rect, offset));
	mHandles[2].setAnchor(rect.bottomRight());
	mHandles[3].moveCenter(ShapeHelper::rectBottomLeftWithOffset(rect, offset));
	mHandles[3].setAnchor(rect.bottomLeft());

    updateRectCursors();
}

void AbstractRectRotateHandles::initCursors()
{
    mCursors.clear();
	mCursors.append(CursorHelper::fDiagResizeCursor());
	mCursors.append(CursorHelper::verticalResizeCursor());
	mCursors.append(CursorHelper::bDiagResizeCursor());
	mCursors.append(CursorHelper::horizontalResizeCursor());
}

void AbstractRectRotateHandles::updateRectCursors()
{
    if (mCursors.isEmpty()) {
        return;
    }

    auto rect = getItemBoundingRect();
	mCursors[indexOfHandleWithAnchorAt(rect.topLeft())] = CursorHelper::fDiagResizeCursor();
	mCursors[indexOfHandleWithAnchorAt(rect.topRight())] = CursorHelper::bDiagResizeCursor();
	mCursors[indexOfHandleWithAnchorAt(rect.bottomRight())] = CursorHelper::fDiagResizeCursor();
	mCursors[indexOfHandleWithAnchorAt(rect.bottomLeft())] = CursorHelper::bDiagResizeCursor();
}

} // namespace kImageAnnotator
