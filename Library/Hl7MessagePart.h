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

#ifndef HL7MESSAGEPART_H
#define HL7MESSAGEPART_H

#include <QDate>
#include <QDateTime>
#include <QSharedPointer>
#include <QString>

namespace HL7WB
{

class Hl7EncodingCharacters;

class Hl7MessagePart
{
public:
    QSharedPointer<const Hl7EncodingCharacters> encodingUsed() const;

    virtual bool isValid() const;

    QDate toDate() const;
    QDateTime toDateTime() const;
    QString toString() const;
    virtual QString toString(QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) const = 0;

protected:
    Hl7MessagePart();
    Hl7MessagePart(QWeakPointer<const Hl7MessagePart> parent,
                   QSharedPointer<const Hl7EncodingCharacters> encodingCharacters);

private:
    QSharedPointer<const Hl7EncodingCharacters> m_encodingUsed;
    QWeakPointer<const Hl7MessagePart> m_parent;
};

} // namespace

#endif // HL7MESSAGEPART_H
