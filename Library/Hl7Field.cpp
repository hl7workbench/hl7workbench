#include "Hl7Field.h"

#include "Hl7Component.h"
#include "Hl7EncodingCharacters.h"
#include "Hl7Segment.h"

namespace HL7WB {

QSharedPointer<Hl7Field> Hl7Field::fromString(QWeakPointer<const Hl7Segment> parent,
                                              qint64 fieldId,
                                              const QString &input,
                                              QSharedPointer<const Hl7EncodingCharacters> encodingCharacters)
{
    QSharedPointer<Hl7Field> result =
            QSharedPointer<Hl7Field>(new Hl7Field(parent,
                                                  fieldId,
                                                  QMap<qint64, QSharedPointer<Hl7Component> >(),
                                                  encodingCharacters));

    QStringList componentStrings =
            input.split((*encodingCharacters).componentSeparator(),
                        QString::KeepEmptyParts,
                        Qt::CaseSensitive);

    qint64 componentId = 1;
    for(const QString &s : componentStrings)
    {
        (*result).m_components[componentId] =
                Hl7Component::fromString(result,
                                         componentId,
                                         s,
                                         encodingCharacters);
        componentId++;
    }

    return result;
}

QSharedPointer<Hl7Component> Hl7Field::component(qint64 componentId) const
{
    if (m_components.contains(componentId))
    {
        return m_components[componentId];
    }
    else
    {
        return QSharedPointer<Hl7Component>();
    }
}

bool Hl7Field::isValid() const
{
    if (!Hl7MessagePart::isValid())
    {
        return false;
    }

    QMapIterator<qint64, QSharedPointer<Hl7Component> > i(m_components);
    while (i.hasNext()) {
        i.next();

        if (!(*i.value()).isValid())
        {
            return false;
        }
    }

    return true;
}

QString Hl7Field::toString(QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) const
{
    QStringList componentStrings;

    QMapIterator<qint64, QSharedPointer<Hl7Component> > i(m_components);
    while (i.hasNext()) {
        i.next();

        componentStrings.append(i.value()->toString(encodingCharacters));
    }

    return componentStrings.join(encodingCharacters->componentSeparator());
}

Hl7Field::Hl7Field() :
    Hl7MessagePart(),
    m_components(),
    m_fieldId(-1)
{
}

Hl7Field::Hl7Field(QWeakPointer<const Hl7Segment> parent,
                   qint64 fieldId,
                   const QMap<qint64, QSharedPointer<Hl7Component> > &components,
                   QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) :
    Hl7MessagePart(parent, encodingCharacters),
    m_components(components),
    m_fieldId(fieldId)
{
}

} // namespace
