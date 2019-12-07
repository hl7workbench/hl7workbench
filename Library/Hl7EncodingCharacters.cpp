#include "Hl7EncodingCharacters.h"

#include <QString>

namespace HL7WB
{

Hl7EncodingCharacters::Hl7EncodingCharacters() :
    m_componentSeparator(),
    m_escapeCharacter(),
    m_fieldSeparator(),
    m_repetitionSeparator(),
    m_segmentSeparator(),
    m_subcomponentSeparator()
{
}

Hl7EncodingCharacters::Hl7EncodingCharacters(const QChar &fieldSeparator,
                                             const QChar &componentSeparator,
                                             const QChar &repetitionSeparator,
                                             const QChar &escapeCharacter,
                                             const QChar &subcomponentSeparator,
                                             const QChar &segmentSeparator) :
    m_componentSeparator(componentSeparator),
    m_escapeCharacter(escapeCharacter),
    m_fieldSeparator(fieldSeparator),
    m_repetitionSeparator(repetitionSeparator),
    m_segmentSeparator(segmentSeparator),
    m_subcomponentSeparator(subcomponentSeparator)
{
}

Hl7EncodingCharacters::Hl7EncodingCharacters(const Hl7EncodingCharacters &other) :
    m_componentSeparator(other.m_componentSeparator),
    m_escapeCharacter(other.m_escapeCharacter),
    m_fieldSeparator(other.m_fieldSeparator),
    m_repetitionSeparator(other.m_repetitionSeparator),
    m_segmentSeparator(other.m_segmentSeparator),
    m_subcomponentSeparator(other.m_subcomponentSeparator)
{
}

bool Hl7EncodingCharacters::areNull() const
{
    return m_componentSeparator.isNull() &&
           m_escapeCharacter.isNull() &&
           m_fieldSeparator.isNull() &&
           m_repetitionSeparator.isNull() &&
           m_subcomponentSeparator.isNull();
}

bool Hl7EncodingCharacters::areValid() const
{
    return !(m_componentSeparator.isNull() ||
            m_escapeCharacter.isNull() ||
            m_fieldSeparator.isNull() ||
            m_repetitionSeparator.isNull() ||
            m_subcomponentSeparator.isNull());
}

const QChar &Hl7EncodingCharacters::componentSeparator() const
{
    return m_componentSeparator;
}

QString Hl7EncodingCharacters::escape(const QString &in) const
{
    // create a copy to lose constness
    QString out(in);

    // escape the escape character to not escape the ones added for other
    // encoding charactes
    out.replace(m_escapeCharacter,
                QString(m_escapeCharacter) +
                QString("E") +
                QString(m_escapeCharacter),
                Qt::CaseSensitive);

    out.replace(m_fieldSeparator,
                QString(m_escapeCharacter) +
                QString("F") +
                QString(m_escapeCharacter),
                Qt::CaseSensitive);

    out.replace(m_repetitionSeparator,
                QString(m_escapeCharacter) +
                QString("R") +
                QString(m_escapeCharacter),
                Qt::CaseSensitive);

    out.replace(m_componentSeparator,
                QString(m_escapeCharacter) +
                QString("S") +
                QString(m_escapeCharacter),
                Qt::CaseSensitive);

    out.replace(m_subcomponentSeparator,
                QString(m_escapeCharacter) +
                QString("T") +
                QString(m_escapeCharacter),
                Qt::CaseSensitive);

    return out;
}

const QChar &Hl7EncodingCharacters::escapeCharacter() const
{
    return m_escapeCharacter;
}

const QChar &Hl7EncodingCharacters::fieldSeparator() const
{
    return m_fieldSeparator;
}

Hl7EncodingCharacters Hl7EncodingCharacters::recommended()
{
    return Hl7EncodingCharacters('|', '^', '~', '\\', '&', '\r');
}

const QChar &Hl7EncodingCharacters::repetitionSeparator() const
{
    return m_repetitionSeparator;
}

const QChar &Hl7EncodingCharacters::segmentSeparator() const
{
    return m_segmentSeparator;
}

const QChar &Hl7EncodingCharacters::subcomponentSeparator() const
{
    return m_subcomponentSeparator;
}

QString Hl7EncodingCharacters::unescape(const QString &in) const
{
    // create a copy to lose constness
    QString out(in);

    out.replace(QString(m_escapeCharacter) +
                QString("F") +
                QString(m_escapeCharacter),
                m_fieldSeparator,
                Qt::CaseSensitive);

    out.replace(QString(m_escapeCharacter) +
                QString("R") +
                QString(m_escapeCharacter),
                m_repetitionSeparator,
                Qt::CaseSensitive);

    out.replace(QString(m_escapeCharacter) +
                QString("S") +
                QString(m_escapeCharacter),
                m_componentSeparator,
                Qt::CaseSensitive);

    out.replace(QString(m_escapeCharacter) +
                QString("T") +
                QString(m_escapeCharacter),
                m_subcomponentSeparator,
                Qt::CaseSensitive);

    // unescape the escape character last to not unescape the ones added for
    // other encoding charactes
    out.replace(QString(m_escapeCharacter) +
                QString("E") +
                QString(m_escapeCharacter),
                m_escapeCharacter,
                Qt::CaseSensitive);

    return out;
}

Hl7EncodingCharacters &Hl7EncodingCharacters::operator =(const Hl7EncodingCharacters &other)
{
    *this = other;
    return *this;
}

} // namespace
