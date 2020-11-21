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

#include "AnnotationItemRotator.h"

namespace kImageAnnotator {

AnnotationItemRotator::AnnotationItemRotator(AbstractAnnotationItem *item, ZoomValueProvider *zoomValueProvider) :
	mAnnotationItem(item),
	mZoomValueProvider(zoomValueProvider),
	mCurrentHandle(-1)
{
	mRotateHandles = RotateHandlesFactory::createRotateHandles(item, zoomValueProvider->zoomValue());
	connect(zoomValueProvider, &ZoomValueProvider::zoomValueChanged, this, &AnnotationItemRotator::applyZoomValue);
	prepareGeometryChange();
}

AnnotationItemRotator::~AnnotationItemRotator()
{
	mAnnotationItem = nullptr;
	delete mRotateHandles;
}

QRectF AnnotationItemRotator::boundingRect() const
{
	auto size = mRotateHandles->handleSize() / 2;
	return mAnnotationItem->boundingRect().normalized().adjusted(-size, -size, size, size);
}

void AnnotationItemRotator::grabHandle(const QPointF &pos)
{
	mCurrentHandle = mRotateHandles->indexOfHandleAt(pos);
	if (mCurrentHandle != -1) {
		mClickOffset = pos - mRotateHandles->handle(mCurrentHandle).anchor();
	}
}

void AnnotationItemRotator::moveHandle(const QPointF &pos)
{
	if (mCurrentHandle != -1) {
		emit newCommand(new RotateCommand(mAnnotationItem, mCurrentHandle, pos - mClickOffset));
	}
}

void AnnotationItemRotator::releaseHandle()
{
	mCurrentHandle = -1;
}

bool AnnotationItemRotator::isRotating() const
{
	return mCurrentHandle != -1;
}

void AnnotationItemRotator::refresh()
{
	prepareGeometryChange();
	mRotateHandles->update();
}

bool AnnotationItemRotator::isItemVisible() const
{
	return mAnnotationItem != nullptr && mAnnotationItem->isVisible();
}

Qt::CursorShape AnnotationItemRotator::cursorForPos(const QPointF &pos)
{
	return mRotateHandles->cursorForPos(pos);
}

Qt::CursorShape AnnotationItemRotator::cursorForCurrentHandle()
{
	return mRotateHandles->cursorForHandle(mCurrentHandle);
}

void AnnotationItemRotator::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setPen(QPen(Qt::white, 1.0 / mZoomValueProvider->zoomValue()));
	painter->setBrush(Qt::green);
	auto handles = mRotateHandles->handles();
	for (auto &handle : handles) {
		painter->drawRect(handle);
	}
}

void AnnotationItemRotator::applyZoomValue(double value)
{
	mRotateHandles->applyZoomValue(value);
}

} // namespace kImageAnnotator
