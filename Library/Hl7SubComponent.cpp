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

#include "Hl7SubComponent.h"

#include "Hl7Component.h"
#include "Hl7EncodingCharacters.h"

namespace HL7WB
{

QSharedPointer<Hl7SubComponent> Hl7SubComponent::fromString(QWeakPointer<const Hl7Component> parent,
                                                            qint64 subcomponentId,
                                                            const QString &input,
                                                            QSharedPointer<const Hl7EncodingCharacters> encodingCharacters)
{
    return QSharedPointer<Hl7SubComponent>(new Hl7SubComponent(parent,
                                           subcomponentId,
                                           encodingCharacters->unescape(input),
                                           encodingCharacters));
}

bool Hl7SubComponent::isValid() const
{
    return Hl7MessagePart::isValid() && (m_subcomponentId != -1);
}


QString Hl7SubComponent::toString(QSharedPointer<const Hl7EncodingCharacters> /*encodingCharacters*/) const
{
    return m_data;
}

Hl7SubComponent::Hl7SubComponent() :
    Hl7MessagePart(),
    m_data(),
    m_subcomponentId(-1)
{
}

Hl7SubComponent::Hl7SubComponent(QWeakPointer<const Hl7Component> parent,
                                 qint64 subcomponentId,
                                 const QString &data,
                                 QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) :
    Hl7MessagePart(parent, encodingCharacters),
    m_data(data),
    m_subcomponentId(subcomponentId)
{
}

}
