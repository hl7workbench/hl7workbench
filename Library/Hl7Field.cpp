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

#include "Hl7Field.h"

#include "Hl7Component.h"
#include "Hl7EncodingCharacters.h"
#include "Hl7Segment.h"

namespace HL7WB {

QSharedPointer<Hl7Field> Hl7Field::fromString(QWeakPointer<const Hl7Segment> parent,
                                              qint64 fieldId,
                                              const QString &input,
                                              QSharedPointer<const Hl7EncodingCharacters> encodingCharacters)
{
    QSharedPointer<Hl7Field> result =
            QSharedPointer<Hl7Field>(new Hl7Field(parent,
                                                  fieldId,
                                                  QMap<qint64, QSharedPointer<Hl7Component> >(),
                                                  encodingCharacters));

    QStringList componentStrings =
            input.split((*encodingCharacters).componentSeparator(),
                        QString::KeepEmptyParts,
                        Qt::CaseSensitive);

    qint64 componentId = 1;
    for(const QString &s : componentStrings)
    {
        (*result).m_components[componentId] =
                Hl7Component::fromString(result,
                                         componentId,
                                         s,
                                         encodingCharacters);
        componentId++;
    }

    return result;
}

QSharedPointer<Hl7Component> Hl7Field::component(qint64 componentId) const
{
    if (m_components.contains(componentId))
    {
        return m_components[componentId];
    }
    else
    {
        return QSharedPointer<Hl7Component>();
    }
}

qint64 Hl7Field::fieldId() const
{
    return m_fieldId;
}

bool Hl7Field::isValid() const
{
    if (!Hl7MessagePart::isValid())
    {
        return false;
    }

    QMapIterator<qint64, QSharedPointer<Hl7Component> > i(m_components);
    while (i.hasNext()) {
        i.next();

        if (!(*i.value()).isValid())
        {
            return false;
        }
    }

    return true;
}

QString Hl7Field::toString(QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) const
{
    QStringList componentStrings;

    QMapIterator<qint64, QSharedPointer<Hl7Component> > i(m_components);
    while (i.hasNext()) {
        i.next();

        componentStrings.append(i.value()->toString(encodingCharacters));
    }

    return componentStrings.join(encodingCharacters->componentSeparator());
}

Hl7Field::Hl7Field() :
    Hl7MessagePart(),
    m_components(),
    m_fieldId(-1)
{
}

Hl7Field::Hl7Field(QWeakPointer<const Hl7Segment> parent,
                   qint64 fieldId,
                   const QMap<qint64, QSharedPointer<Hl7Component> > &components,
                   QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) :
    Hl7MessagePart(parent, encodingCharacters),
    m_components(components),
    m_fieldId(fieldId)
{
}

} // namespace
