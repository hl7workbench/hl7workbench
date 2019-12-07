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

#include "Hl7MessagePart.h"

namespace HL7WB
{

QSharedPointer<const Hl7EncodingCharacters> Hl7MessagePart::encodingUsed() const
{
    return m_encodingUsed;
}

bool Hl7MessagePart::isValid() const
{
    return !m_parent.isNull();
}

QDate Hl7MessagePart::toDate() const
{
    return QDate::fromString(toString(), "yyyyMMdd");
}

QDateTime Hl7MessagePart::toDateTime() const
{
    QDateTime result;

    result = QDateTime::fromString(toString(), "yyyyMMddHHmmss");
    if (result.isValid())
    {
        return result;
    }

    result = QDateTime::fromString(toString(), "yyyyMMddHHmm");
    if (result.isValid())
    {
        return result;
    }

    return QDateTime();
}

QString Hl7MessagePart::toString() const
{
    return toString(m_encodingUsed);
}

Hl7MessagePart::Hl7MessagePart() :
    m_encodingUsed(),
    m_parent()
{
}

Hl7MessagePart::Hl7MessagePart(QWeakPointer<const Hl7MessagePart> parent,
                               QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) :
    m_encodingUsed(encodingCharacters),
    m_parent(parent)
{
}

} // namespace
