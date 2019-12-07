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

#ifndef HL7MESSAGE_H
#define HL7MESSAGE_H

#include "Hl7MessagePart.h"
#include "Hl7Segment.h"

#include <QMap>
#include <QSharedPointer>
#include <QString>
#include <QWeakPointer>

namespace HL7WB
{

class Hl7EncodingCharacters;
class Hl7Component;

class Hl7Message : public Hl7MessagePart
{
public:
    static QSharedPointer<Hl7Message> fromString(const QString &input);
    static QSharedPointer<Hl7Message> fromString(const QString &input,
                                                 QSharedPointer<const Hl7EncodingCharacters> encodingCharacters);

    QSharedPointer<Hl7Component> component(const QString &segmentId,
                                           qint64 fieldId,
                                           qint64 componentId) const;
    QSharedPointer<Hl7Field> field(const QString &segmentId,
                                   qint64 fieldId) const;

    virtual bool isValid() const override;

    QSharedPointer<Hl7Segment> segment(const QString &segmentId) const;

    using Hl7MessagePart::toString;
    virtual QString toString(QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) const override;

private:
    Hl7Message();
    Hl7Message(QSharedPointer<const Hl7EncodingCharacters> encodingCharacters);

    QList<QSharedPointer<Hl7Segment> > m_segmentList;
    QMap<QString, QSharedPointer<Hl7Segment> > m_segmentMap;
};

} // namespace

#endif // HL7MESSAGE_H
