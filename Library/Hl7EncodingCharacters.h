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
