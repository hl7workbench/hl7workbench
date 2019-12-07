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
