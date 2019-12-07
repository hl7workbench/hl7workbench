#include "Hl7MessagePart.h"

namespace HL7WB
{

QSharedPointer<const Hl7EncodingCharacters> Hl7MessagePart::encodingUsed() const
{
    return m_encodingUsed;
}

bool Hl7MessagePart::isValid() const
{
    return !m_parent.isNull();
}

QDate Hl7MessagePart::toDate() const
{
    return QDate::fromString(toString(), "yyyyMMdd");
}

QDateTime Hl7MessagePart::toDateTime() const
{
    QDateTime result;

    result = QDateTime::fromString(toString(), "yyyyMMddHHmmss");
    if (result.isValid())
    {
        return result;
    }

    result = QDateTime::fromString(toString(), "yyyyMMddHHmm");
    if (result.isValid())
    {
        return result;
    }

    return QDateTime();
}

QString Hl7MessagePart::toString() const
{
    return toString(m_encodingUsed);
}

Hl7MessagePart::Hl7MessagePart() :
    m_encodingUsed(),
    m_parent()
{
}

Hl7MessagePart::Hl7MessagePart(QWeakPointer<const Hl7MessagePart> parent,
                               QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) :
    m_encodingUsed(encodingCharacters),
    m_parent(parent)
{
}

} // namespace
