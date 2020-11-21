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

#include "RotateHandlesFactory.h"

namespace kImageAnnotator {

AbstractItemRotateHandles *RotateHandlesFactory::createRotateHandles(AbstractAnnotationItem *item, double zoomValue)
{
    auto rotateHandles = GetLineRotateHandles(item, zoomValue);
    if (rotateHandles != nullptr) {
        return rotateHandles;
    }

	rotateHandles = GetPointerRectRotateHandles(item, zoomValue);
	if (rotateHandles != nullptr) {
		return rotateHandles;
	}

    rotateHandles = GetRectRotateHandles(item, zoomValue);
    if (rotateHandles != nullptr) {
        return rotateHandles;
    }

    rotateHandles = GetPathRotateHandles(item, zoomValue);
    return rotateHandles;
}

AbstractItemRotateHandles *RotateHandlesFactory::GetLineRotateHandles(AbstractAnnotationItem *item, double zoomValue)
{
    auto lineItem = dynamic_cast<AbstractAnnotationLine *>(item);
    if (lineItem != nullptr) {
        return new LineRotateHandles(lineItem, zoomValue);
    }
    return nullptr;
}

AbstractItemRotateHandles *RotateHandlesFactory::GetRectRotateHandles(AbstractAnnotationItem *item, double zoomValue)
{
    auto rectItem = dynamic_cast<AbstractAnnotationRect *>(item);
    if (rectItem != nullptr) {
        return new RectRotateHandles(rectItem, zoomValue);
    }
    return nullptr;
}

AbstractItemRotateHandles *RotateHandlesFactory::GetPointerRectRotateHandles(AbstractAnnotationItem *item, double zoomValue)
{
	auto rectItem = dynamic_cast<AbstractAnnotationPointerRect *>(item);
	if (rectItem != nullptr) {
		return new PointerRectRotateHandles(rectItem, zoomValue);
	}
	return nullptr;
}

AbstractItemRotateHandles *RotateHandlesFactory::GetPathRotateHandles(AbstractAnnotationItem *item, double zoomValue)
{
    auto pathItem = dynamic_cast<AbstractAnnotationPath *>(item);
    if (pathItem != nullptr) {
		return new PathRotateHandles(pathItem, zoomValue);
    }
    return nullptr;
}

} // namespace kImageAnnotator
