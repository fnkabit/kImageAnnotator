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

#include "AnnotationMultiItemRotator.h"

namespace kImageAnnotator {

AnnotationMultiItemRotator::AnnotationMultiItemRotator(ZoomValueProvider *zoomValueProvider)
{
	mZoomValueProvider = zoomValueProvider;
	mCurrentRotator = nullptr;
}

QRectF AnnotationMultiItemRotator::boundingRect() const
{
	QRectF rect;
	for (auto rotator : childItems()) {
		rect = rect.united(rotator->boundingRect());
	}
	return rect;
}

void AnnotationMultiItemRotator::attachTo(const QList<AbstractAnnotationItem *>& items)
{
	detach();
	for (auto item : items) {
		auto rotator = getRotatorForItem(item);
		showRotator(rotator);
	}
}

void AnnotationMultiItemRotator::detach()
{
	for (auto rotator : childItems()) {
		hideRotator(rotator);
	}

	mCurrentRotator = nullptr;
}

void AnnotationMultiItemRotator::grabHandle(const QPointF &pos)
{
	for (auto item : childItems()) {
		auto rotator = castToRotator(item);
		rotator->grabHandle(pos);
		if (rotator->isRotating()) {
			mCurrentRotator = rotator;
			return;
		}
	}
	mCurrentRotator = nullptr;
}

void AnnotationMultiItemRotator::moveHandle(const QPointF &pos)
{
	if (mCurrentRotator == nullptr) {
		return;
	}

	mCurrentRotator->moveHandle(pos);
}

void AnnotationMultiItemRotator::releaseHandle()
{
	if (mCurrentRotator == nullptr) {
		return;
	}

	mCurrentRotator->releaseHandle();
}

bool AnnotationMultiItemRotator::isRotating() const
{
	return mCurrentRotator != nullptr && mCurrentRotator->isRotating();
}

void AnnotationMultiItemRotator::refresh()
{
	for (auto item : childItems()) {
		auto rotator = castToRotator(item);
		rotator->refresh();
	}
}

void AnnotationMultiItemRotator::update()
{
	for (auto item : childItems()) {
		auto rotator = castToRotator(item);
		if (!rotator->isItemVisible()) {
			hideRotator(rotator);
		}
	}
}

bool AnnotationMultiItemRotator::hasItemsAttached() const
{
	return childItems().count() > 0;
}

Qt::CursorShape AnnotationMultiItemRotator::cursorForPos(const QPointF &pos)
{
	for (auto item : childItems()) {
		auto rotator = castToRotator(item);
		if (rotator->boundingRect().contains(pos)) {
			return rotator->cursorForPos(pos);
		}
	}

	return CursorHelper::defaultCursor();
}

Qt::CursorShape AnnotationMultiItemRotator::cursorForCurrentHandle()
{
	if (mCurrentRotator == nullptr) {
		return CursorHelper::defaultCursor();
	}
	return mCurrentRotator->cursorForCurrentHandle();
}

void AnnotationMultiItemRotator::hideCurrentRotator()
{
	if (mCurrentRotator == nullptr) {
		return;
	}

	mCurrentRotator->hide();
}

void AnnotationMultiItemRotator::showCurrentRotator()
{
	if (mCurrentRotator == nullptr) {
		return;
	}

	mCurrentRotator->show();
}

AnnotationItemRotator *AnnotationMultiItemRotator::getRotatorForItem(AbstractAnnotationItem *item)
{
	if (!mItemToRotate.contains(item)) {
		mItemToRotate[item] = new AnnotationItemRotator(item, mZoomValueProvider);
		connect(mItemToRotate[item], &AnnotationItemRotator::newCommand, this, &AnnotationMultiItemRotator::newCommand);
	}

	return mItemToRotate[item];
}

void AnnotationMultiItemRotator::hideRotator(QGraphicsItem *rotator)
{
	removeFromGroup(rotator);
	rotator->hide();
}

void AnnotationMultiItemRotator::showRotator(AnnotationItemRotator *rotator)
{
	addToGroup(rotator);
	rotator->show();
}

AnnotationItemRotator *AnnotationMultiItemRotator::castToRotator(QGraphicsItem *item) const
{
	return dynamic_cast<AnnotationItemRotator *>(item);
}

} // namespace kImageAnnotator
