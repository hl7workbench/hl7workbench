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

#ifndef MESSAGELOGVIEW_H
#define MESSAGELOGVIEW_H

#include <QTableView>

namespace HL7WB
{

class MessageLogModel;

class MessageLogView : public QTableView
{
    Q_OBJECT

public:
    MessageLogView(QWidget *parent = Q_NULLPTR);

    void setModel(MessageLogModel *model);
};

} // namespace

#endif // MESSAGELOGVIEW_H