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

#include "Hl7Segment.h"

#include "Hl7EncodingCharacters.h"
#include "Hl7Field.h"
#include "Hl7Message.h"

namespace HL7WB
{

QSharedPointer<Hl7Segment> Hl7Segment::fromString(QWeakPointer<const Hl7Message> parent,
                                                  const QString &segmentId,
                                                  const QString &input,
                                                  QSharedPointer<const Hl7EncodingCharacters> encodingCharacters)
{
    QSharedPointer<Hl7Segment> result =
            QSharedPointer<Hl7Segment>(new Hl7Segment(parent,
                                                      segmentId,
                                                      QMap<qint64, QSharedPointer<Hl7Field> >(),
                                                      encodingCharacters));

    QStringList fieldStrings =
            input.split(encodingCharacters->fieldSeparator(),
                        QString::KeepEmptyParts,
                        Qt::CaseSensitive);

    qint64 fieldId = 1;

    if (segmentId == "MSH")
    {
        result->m_fields[fieldId] =
                Hl7Field::fromString(result,
                                     fieldId,
                                     QString(encodingCharacters->fieldSeparator()),
                                     encodingCharacters);
        fieldId++;
    }

    for(const QString &s : fieldStrings)
    {
        result->m_fields[fieldId] =
                Hl7Field::fromString(result,
                                     fieldId,
                                     s,
                                     encodingCharacters);
        fieldId++;
    }

    return result;
}

QSharedPointer<Hl7Component> Hl7Segment::component(qint64 fieldId, qint64 componentId) const
{
    return field(fieldId)->component(componentId);
}

QSharedPointer<Hl7Field> Hl7Segment::field(qint64 fieldId) const
{
    if (m_fields.contains(fieldId))
    {
        return m_fields[fieldId];
    }
    else
    {
        return QSharedPointer<Hl7Field>();
    }
}

bool Hl7Segment::isValid() const
{
    if (!Hl7MessagePart::isValid())
    {
        return false;
    }

    QMapIterator<qint64, QSharedPointer<Hl7Field> > i(m_fields);
    while (i.hasNext()) {
        i.next();

        if (!(*i.value()).isValid())
        {
            return false;
        }
    }

    return true;
}

const QString &Hl7Segment::segmentId() const
{
    return m_segmentId;
}

QString Hl7Segment::toString(QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) const
{
    QStringList fieldStrings;

    QMapIterator<qint64, QSharedPointer<Hl7Field> > i(m_fields);
    while (i.hasNext()) {
        i.next();

        fieldStrings.append(i.value()->toString(encodingCharacters));
    }

    return m_segmentId +
            encodingCharacters->fieldSeparator() +
            fieldStrings.join(encodingCharacters->fieldSeparator());
}

Hl7Segment::Hl7Segment() :
    Hl7MessagePart(),
    m_fields(),
    m_segmentId()
{
}

Hl7Segment::Hl7Segment(QWeakPointer<const Hl7Message> parent,
                       const QString &segmentId,
                       const QMap<qint64, QSharedPointer<Hl7Field> > &fields,
                       QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) :
    Hl7MessagePart(parent, encodingCharacters),
    m_fields(fields),
    m_segmentId(segmentId)
{
}

}

