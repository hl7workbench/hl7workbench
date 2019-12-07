#include "Hl7SubComponent.h"

#include "Hl7Component.h"
#include "Hl7EncodingCharacters.h"

namespace HL7WB
{

QSharedPointer<Hl7SubComponent> Hl7SubComponent::fromString(QWeakPointer<const Hl7Component> parent,
                                                            qint64 subcomponentId,
                                                            const QString &input,
                                                            QSharedPointer<const Hl7EncodingCharacters> encodingCharacters)
{
    return QSharedPointer<Hl7SubComponent>(new Hl7SubComponent(parent,
                                           subcomponentId,
                                           encodingCharacters->unescape(input),
                                           encodingCharacters));
}

bool Hl7SubComponent::isValid() const
{
    return Hl7MessagePart::isValid() && (m_subcomponentId != -1);
}


QString Hl7SubComponent::toString(QSharedPointer<const Hl7EncodingCharacters> /*encodingCharacters*/) const
{
    return m_data;
}

Hl7SubComponent::Hl7SubComponent() :
    Hl7MessagePart(),
    m_data(),
    m_subcomponentId(-1)
{
}

Hl7SubComponent::Hl7SubComponent(QWeakPointer<const Hl7Component> parent,
                                 qint64 subcomponentId,
                                 const QString &data,
                                 QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) :
    Hl7MessagePart(parent, encodingCharacters),
    m_data(data),
    m_subcomponentId(subcomponentId)
{
}

}
