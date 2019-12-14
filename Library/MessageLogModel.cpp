/*
 * This file is part of the HL7 Workbench project.
 *
 * Copyright (C) 2019  Individual HL7 Workbench contributors.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "MessageLogModel.h"

namespace HL7WB
{

MessageLogModel::MessageLogModel(QObject *parent) :
    QAbstractTableModel(parent)
{
}

int MessageLogModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
    {
        return 3;
    }
    else
    {
        return 0;
    }
}

QVariant MessageLogModel::headerData(int section, Qt::Orientation orientation,
                                     int role) const
{
    if (Qt::Horizontal == orientation)
    {
        if (Qt::DisplayRole == role)
        {
            switch (section) {
            case 0:
                return QStringLiteral("Time");
                break;
            case 1:
                return QStringLiteral("Message");
                break;
            case 2:
                return QStringLiteral("Details");
                break;
            default:
                return QVariant();
                break;
            }
        }
    }

    return QAbstractTableModel::headerData(section, orientation, role);
}

QVariant MessageLogModel::data(const QModelIndex &index, int role) const
{
    if (Qt::DisplayRole == role)
    {
        if (index.row() == 0)
        {
            switch (index.column()) {
            case 0:
                return QStringLiteral("14 Dec 2019 14:45:00");
                break;
            case 1:
                return QStringLiteral("Lorem ipsum sed dolor");
                break;
            case 2:
                return QStringLiteral("Have your advertisements appear here!");
                break;
            default:
                return QVariant();
                break;
            }
        }
    }

    return QVariant();
}

int MessageLogModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


} // namespace
