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

#ifndef HL7SPECIALCHARACTERS_H
#define HL7SPECIALCHARACTERS_H

#include <QChar>

namespace HL7WB
{

class Hl7EncodingCharacters
{
public:
    Hl7EncodingCharacters();
    Hl7EncodingCharacters(const QChar &fieldSeparator,
                          const QChar &componentSeparator,
                          const QChar &repetitionSeparator,
                          const QChar &escapeCharacter,
                          const QChar &subcomponentSeparator,
                          const QChar &segmentSeparator = '\r');
    Hl7EncodingCharacters(const Hl7EncodingCharacters &other);

    bool areNull() const;
    bool areValid() const;
    const QChar &componentSeparator() const;

    QString escape(const QString &in) const;

    const QChar &escapeCharacter() const;
    const QChar &fieldSeparator() const;

    static Hl7EncodingCharacters recommended();

    const QChar &repetitionSeparator() const;
    const QChar &segmentSeparator() const;
    const QChar &subcomponentSeparator() const;

    QString unescape(const QString &in) const;

    Hl7EncodingCharacters &operator =(const Hl7EncodingCharacters &other);

private:
    QChar m_componentSeparator;
    QChar m_escapeCharacter;
    QChar m_fieldSeparator;
    QChar m_repetitionSeparator;
    QChar m_segmentSeparator;
    QChar m_subcomponentSeparator;
};

} // namespace

#endif // HL7SPECIALCHARACTERS_H
