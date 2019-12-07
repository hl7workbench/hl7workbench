#ifndef HL7MESSAGEPART_H
#define HL7MESSAGEPART_H

#include <QDate>
#include <QDateTime>
#include <QSharedPointer>
#include <QString>

namespace HL7WB
{

class Hl7EncodingCharacters;

class Hl7MessagePart
{
public:
    QSharedPointer<const Hl7EncodingCharacters> encodingUsed() const;

    virtual bool isValid() const;

    QDate toDate() const;
    QDateTime toDateTime() const;
    QString toString() const;
    virtual QString toString(QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) const = 0;

protected:
    Hl7MessagePart();
    Hl7MessagePart(QWeakPointer<const Hl7MessagePart> parent,
                   QSharedPointer<const Hl7EncodingCharacters> encodingCharacters);

private:
    QSharedPointer<const Hl7EncodingCharacters> m_encodingUsed;
    QWeakPointer<const Hl7MessagePart> m_parent;
};

} // namespace

#endif // HL7MESSAGEPART_H
