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

#include "RotateCommand.h"
#include <QtCore/QDebug>
#include <QtMath>
#include <QTransform>

namespace kImageAnnotator {

RotateCommand::RotateCommand(AbstractAnnotationItem *item, int handleIndex, qreal angle)
{
    mItem = item;
    mHandleIndex = handleIndex;
	mAngle = angle;
    mOriginalPos = item->pointAt(handleIndex);
}

void RotateCommand::undo()
{
    mItem->setPointAt(mOriginalPos, mHandleIndex);
}

void RotateCommand::redo()
{
	mItem->rotate(mAngle);


//	float angleRad = qAtan2(mNewPos.y() - mItem->rect().y(),
//							mNewPos.x() - mItem->rect().x());
//	float angle = angleRad * 180 / M_PI;
//	qWarning() << "angle:\t" << angle;

	// mItem->setPointAt(mNewPos, mHandleIndex);
}

bool RotateCommand::mergeWith(const QUndoCommand *command)
{
//	const auto rotateCommand = dynamic_cast<const RotateCommand *>(command);

//	if (mItem != rotateCommand->mItem || mHandleIndex != rotateCommand->mHandleIndex) {
//        return false;
//    }

//	mNewPos = rotateCommand->mNewPos;

//    return true;
}

int RotateCommand::id() const
{
    return Id;
}

} // namespace kImageAnnotator