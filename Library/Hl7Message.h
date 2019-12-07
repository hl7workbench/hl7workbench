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
