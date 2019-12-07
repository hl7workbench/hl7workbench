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
