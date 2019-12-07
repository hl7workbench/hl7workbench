#include "Hl7Component.h"

#include "Hl7EncodingCharacters.h"
#include "Hl7Field.h"
#include "Hl7SubComponent.h"

namespace HL7WB
{

QSharedPointer<Hl7Component> Hl7Component::fromString(QWeakPointer<const Hl7Field> parent,
                                      qint64 componentId,
                                      const QString &input,
                                      QSharedPointer<const Hl7EncodingCharacters> encodingCharacters)
{
    QSharedPointer<Hl7Component> result =
            QSharedPointer<Hl7Component>(new Hl7Component(parent,
                                                          componentId,
                                                          QMap<qint64, QSharedPointer<Hl7SubComponent> >(),
                                                          encodingCharacters));

    QStringList subcomponentStrings =
            input.split(encodingCharacters->subcomponentSeparator(),
                        QString::KeepEmptyParts,
                        Qt::CaseSensitive);

    qint64 subcomponentId = 1;
    for(const QString &s : subcomponentStrings)
    {
        (*result).m_subcomponents[subcomponentId] =
                Hl7SubComponent::fromString(result,
                                            subcomponentId,
                                            s,
                                            encodingCharacters);
        subcomponentId++;
    }

    return result;
}

bool Hl7Component::isValid() const
{
    if (!Hl7MessagePart::isValid())
    {
        return false;
    }

    QMapIterator<qint64, QSharedPointer<Hl7SubComponent> > i(m_subcomponents);
    while (i.hasNext()) {
        i.next();

        if (!(*i.value()).isValid())
        {
            return false;
        }
    }

    return true;
}

QString Hl7Component::toString(QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) const
{
    QStringList subcomponentStrings;

    QMapIterator<qint64, QSharedPointer<Hl7SubComponent> > i(m_subcomponents);
    while (i.hasNext()) {
        i.next();

        subcomponentStrings.append(i.value()->toString(encodingCharacters));
    }

    return subcomponentStrings.join(encodingCharacters->subcomponentSeparator());
}

Hl7Component::Hl7Component() :
    Hl7MessagePart(),
    m_componentId(-1),
    m_subcomponents()
{
}

Hl7Component::Hl7Component(QWeakPointer<const Hl7Field> parent,
                           qint64 componentId,
                           const QMap<qint64, QSharedPointer<Hl7SubComponent> > &subcomponents,
                           QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) :
    Hl7MessagePart(parent, encodingCharacters),
    m_componentId(componentId),
    m_subcomponents(subcomponents)
{
}

} // namespace
