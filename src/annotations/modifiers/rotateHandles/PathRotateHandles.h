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

#ifndef KIMAGEANNOTATOR_PATHROTATEHANDLES_H
#define KIMAGEANNOTATOR_PATHROTATEHANDLES_H

#include "AbstractRectRotateHandles.h"
#include "src/annotations/items/AbstractAnnotationPath.h"

namespace kImageAnnotator {

class PathRotateHandles : public AbstractRectRotateHandles
{
public:
    PathRotateHandles(AbstractAnnotationPath *pathItem, double zoomValue);
    ~PathRotateHandles() override = default;

protected:
    QRectF getRect() const override;
    double getOffset() const override;
    QRectF getItemBoundingRect() const override;

private:
    AbstractAnnotationPath *mPathItem;
};

} // namespace kImageAnnotator

#endif //KIMAGEANNOTATOR_PATHROTATEHANDLES_H
