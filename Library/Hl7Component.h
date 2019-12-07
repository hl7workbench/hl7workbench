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

#ifndef HL7COMPONENT_H
#define HL7COMPONENT_H

#include "Hl7MessagePart.h"

#include <QMap>
#include <QSharedPointer>
#include <QString>
#include <QWeakPointer>

namespace HL7WB
{

class Hl7Field;
class Hl7SubComponent;

class Hl7Component : public Hl7MessagePart
{
public:
    static QSharedPointer<Hl7Component> fromString(QWeakPointer<const Hl7Field> parent,
                                                   qint64 componentId,
                                                   const QString &input,
                                                   QSharedPointer<const Hl7EncodingCharacters> encodingCharacters);

    virtual bool isValid() const override;

    using Hl7MessagePart::toString;
    virtual QString toString(QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) const override;

private:
    Hl7Component();
    Hl7Component(QWeakPointer<const Hl7Field> parent,
                 qint64 componentId,
                 const QMap<qint64, QSharedPointer<Hl7SubComponent> > &subcomponents,
                 QSharedPointer<const Hl7EncodingCharacters> encodingCharacters);

    qint64 m_componentId;
    QMap<qint64, QSharedPointer<Hl7SubComponent> > m_subcomponents;
};

} // namespace

#endif // HL7COMPONENT_H
