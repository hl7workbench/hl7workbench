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

#ifndef HL7FIELD_H
#define HL7FIELD_H

#include "Hl7MessagePart.h"

#include <QMap>
#include <QSharedPointer>
#include <QString>
#include <QWeakPointer>

namespace HL7WB
{

class Hl7Component;
class Hl7Segment;


class Hl7Field : public Hl7MessagePart
{
public:
    static QSharedPointer<Hl7Field> fromString(QWeakPointer<const Hl7Segment> parent,
                                               qint64 fieldId,
                                               const QString &input,
                                               QSharedPointer<const Hl7EncodingCharacters> encodingCharacters);

    QSharedPointer<Hl7Component> component(qint64 componentId) const;

    virtual bool isValid() const override;

    using Hl7MessagePart::toString;
    virtual QString toString(QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) const override;

private:
    Hl7Field();
    Hl7Field(QWeakPointer<const Hl7Segment> parent,
             qint64 fieldId,
             const QMap<qint64, QSharedPointer<Hl7Component> > &components,
             QSharedPointer<const Hl7EncodingCharacters> encodingCharacters);

    QMap<qint64, QSharedPointer<Hl7Component> > m_components;
    qint64 m_fieldId;
};

} // namespace

#endif // HL7FIELD_H
