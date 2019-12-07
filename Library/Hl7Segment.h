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

#ifndef HL7SEGMENT_H
#define HL7SEGMENT_H

#include "Hl7MessagePart.h"

#include <QMap>
#include <QSharedPointer>
#include <QString>
#include <QWeakPointer>

namespace HL7WB
{

class Hl7Component;
class Hl7Field;
class Hl7Message;


class Hl7Segment : public Hl7MessagePart
{
public:
    static QSharedPointer<Hl7Segment> fromString(QWeakPointer<const Hl7Message> parent,
                                                 const QString &segmentId,
                                                 const QString &input,
                                                 QSharedPointer<const Hl7EncodingCharacters> encodingCharacters);

    QSharedPointer<Hl7Component> component(qint64 fieldId,
                                           qint64 componentId) const;
    QSharedPointer<Hl7Field> field(qint64 fieldId) const;

    virtual bool isValid() const override;

    const QString &segmentId() const;

    using Hl7MessagePart::toString;
    virtual QString toString(QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) const override;

private:
    Hl7Segment();
    Hl7Segment(QWeakPointer<const Hl7Message> parent,
               const QString &segmentId,
               const QMap<qint64, QSharedPointer<Hl7Field> > &fields,
               QSharedPointer<const Hl7EncodingCharacters> encodingCharacters);

    QMap<qint64, QSharedPointer<Hl7Field> > m_fields;
    QString m_segmentId;
};

} // namespace

#endif // HL7SEGMENT_H
