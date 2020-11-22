/*
 * Copyright (C) 2018 Damir Porobic <damir.porobic@gmx.com>
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

#include "AnnotationRect.h"
#include <QtCore/QDebug>

namespace kImageAnnotator {

AnnotationRect::AnnotationRect(const QPointF &startPosition, const PropertiesPtr &properties) : AbstractAnnotationRect(startPosition, properties)
{
}

AnnotationRect::AnnotationRect(const AnnotationRect &other) : AbstractAnnotationRect(other)
{
}

Tools AnnotationRect::toolType() const
{
	return Tools::Rect;
}

void AnnotationRect::updateShape()
{
	QPainterPath path;
	if (mAngle == 0) {
		path.addRect(*mRect);
	} else {
		QTransform t = QTransform().translate(mRect->center().x(), mRect->center().y()).rotate(mAngle).translate(-mRect->center().x(), -mRect->center().y());
		const auto rotatedPolygon = t.mapToPolygon(mRect->toRect());
		path.addPolygon(rotatedPolygon);
	}

	setShape(path);
}

} // namespace kImageAnnotator
