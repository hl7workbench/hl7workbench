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
