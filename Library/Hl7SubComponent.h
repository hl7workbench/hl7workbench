#ifndef HL7SUBCOMPONENT_H
#define HL7SUBCOMPONENT_H

#include "Hl7MessagePart.h"

#include <QSharedPointer>
#include <QString>

namespace HL7WB
{

class Hl7Component;

class Hl7SubComponent : public Hl7MessagePart
{
public:
    static QSharedPointer<Hl7SubComponent> fromString(QWeakPointer<const Hl7Component> parent,
                                                      qint64 subcomponentId,
                                                      const QString &input,
                                                      QSharedPointer<const Hl7EncodingCharacters> encodingCharacters);

    virtual bool isValid() const override;

    using Hl7MessagePart::toString;
    virtual QString toString(QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) const override;

private:
    Hl7SubComponent();
    Hl7SubComponent(QWeakPointer<const Hl7Component> parent,
                    qint64 subcomponentId,
                    const QString &data,
                    QSharedPointer<const Hl7EncodingCharacters> encodingCharacters);

    QString m_data;
    qint64 m_subcomponentId;
};

} // namespace

#endif // HL7SUBCOMPONENT_H
