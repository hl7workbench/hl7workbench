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

#include "Hl7Message.h"

#include "Hl7EncodingCharacters.h"
#include "Hl7Field.h"
#include "Hl7Segment.h"

#include <QSharedPointer>
#include <QString>

namespace HL7WB {

QSharedPointer<Hl7Message> Hl7Message::fromString(const QString &input)
{
    QSharedPointer<Hl7EncodingCharacters> autoDetectedEncodingCharacters;

    if (input.startsWith("MSH"))
    {
        autoDetectedEncodingCharacters = QSharedPointer<Hl7EncodingCharacters>(
                    new Hl7EncodingCharacters(input.at(3),
                                              input.at(4),
                                              input.at(5),
                                              input.at(6),
                                              input.at(7)));
    }
    else
    {
        return QSharedPointer<Hl7Message>();
    }

    return fromString(input, autoDetectedEncodingCharacters);
}

QSharedPointer<Hl7Message> Hl7Message::fromString(const QString &input,
                                                  QSharedPointer<const Hl7EncodingCharacters> encodingCharacters)
{
    if (!input.startsWith("MSH"))
    {
        return QSharedPointer<Hl7Message>();
    }

    QSharedPointer<Hl7Message> result =
            QSharedPointer<Hl7Message>(new Hl7Message(encodingCharacters));

    QStringList segmentStrings =
            input.split((*encodingCharacters).segmentSeparator(),
                        QString::SkipEmptyParts,
                        Qt::CaseSensitive);

    for(const QString &s : segmentStrings)
    {
        QString segmentId = s.left(3);

        QSharedPointer<Hl7Segment> segment = Hl7Segment::fromString(result,
                                                                    segmentId,
                                                                    s.mid(4),
                                                                    encodingCharacters);

        (*result).m_segmentMap[segmentId] = segment;
        (*result).m_segmentList.append(segment);
    }

    return result;
}

QSharedPointer<Hl7Component> Hl7Message::component(const QString &segmentId,
                                                   qint64 fieldId,
                                                   qint64 componentId) const
{
    QWeakPointer<Hl7Field> f = field(segmentId, fieldId);

    if (!f.isNull())
    {
        return f->component(componentId);
    }
    else
    {
        return QSharedPointer<Hl7Component>();
    }
}

QSharedPointer<Hl7Field> Hl7Message::field(const QString &segmentId,
                                           qint64 fieldId) const
{
    QWeakPointer<Hl7Segment> s = segment(segmentId);

    if (!s.isNull())
    {
        return s->field(fieldId);
    }
    else
    {
        return QSharedPointer<Hl7Field>();
    }
}

bool Hl7Message::isValid() const
{
    if (!m_segmentMap.contains("MSH"))
    {
        return false;
    }

    QMapIterator<QString, QSharedPointer<Hl7Segment> > i(m_segmentMap);
    while (i.hasNext()) {
        i.next();

        if (!(*i.value()).isValid())
        {
            return false;
        }
    }

    return true;
}

QSharedPointer<Hl7Segment> Hl7Message::segment(const QString &segmentId) const
{
    if (m_segmentMap.contains(segmentId))
    {
        return m_segmentMap[segmentId];
    }
    else
    {
        return QSharedPointer<Hl7Segment>();
    }
}

QString Hl7Message::toString(QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) const
{
    QStringList segmentStrings;

    for(QSharedPointer<const Hl7Segment> i : m_segmentList)
    {
        segmentStrings.append(i->toString(encodingCharacters));
    }

    return segmentStrings.join(encodingCharacters->segmentSeparator());
}

Hl7Message::Hl7Message() :
    Hl7MessagePart(),
    m_segmentList(),
    m_segmentMap()
{
}

Hl7Message::Hl7Message(QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) :
    Hl7MessagePart(QSharedPointer<const Hl7MessagePart>(), encodingCharacters),
    m_segmentList(),
    m_segmentMap()
{

}

} // namespace
