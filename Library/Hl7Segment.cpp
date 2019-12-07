#include "Hl7Segment.h"

#include "Hl7EncodingCharacters.h"
#include "Hl7Field.h"
#include "Hl7Message.h"

namespace HL7WB
{

QSharedPointer<Hl7Segment> Hl7Segment::fromString(QWeakPointer<const Hl7Message> parent,
                                                  const QString &segmentId,
                                                  const QString &input,
                                                  QSharedPointer<const Hl7EncodingCharacters> encodingCharacters)
{
    QSharedPointer<Hl7Segment> result =
            QSharedPointer<Hl7Segment>(new Hl7Segment(parent,
                                                      segmentId,
                                                      QMap<qint64, QSharedPointer<Hl7Field> >(),
                                                      encodingCharacters));

    QStringList fieldStrings =
            input.split(encodingCharacters->fieldSeparator(),
                        QString::KeepEmptyParts,
                        Qt::CaseSensitive);

    qint64 fieldId = 1;

    if (segmentId == "MSH")
    {
        result->m_fields[fieldId] =
                Hl7Field::fromString(result,
                                     fieldId,
                                     QString(encodingCharacters->fieldSeparator()),
                                     encodingCharacters);
        fieldId++;
    }

    for(const QString &s : fieldStrings)
    {
        result->m_fields[fieldId] =
                Hl7Field::fromString(result,
                                     fieldId,
                                     s,
                                     encodingCharacters);
        fieldId++;
    }

    return result;
}

QSharedPointer<Hl7Component> Hl7Segment::component(qint64 fieldId, qint64 componentId) const
{
    return field(fieldId)->component(componentId);
}

QSharedPointer<Hl7Field> Hl7Segment::field(qint64 fieldId) const
{
    if (m_fields.contains(fieldId))
    {
        return m_fields[fieldId];
    }
    else
    {
        return QSharedPointer<Hl7Field>();
    }
}

bool Hl7Segment::isValid() const
{
    if (!Hl7MessagePart::isValid())
    {
        return false;
    }

    QMapIterator<qint64, QSharedPointer<Hl7Field> > i(m_fields);
    while (i.hasNext()) {
        i.next();

        if (!(*i.value()).isValid())
        {
            return false;
        }
    }

    return true;
}

const QString &Hl7Segment::segmentId() const
{
    return m_segmentId;
}

QString Hl7Segment::toString(QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) const
{
    QStringList fieldStrings;

    QMapIterator<qint64, QSharedPointer<Hl7Field> > i(m_fields);
    while (i.hasNext()) {
        i.next();

        fieldStrings.append(i.value()->toString(encodingCharacters));
    }

    return m_segmentId +
            encodingCharacters->fieldSeparator() +
            fieldStrings.join(encodingCharacters->fieldSeparator());
}

Hl7Segment::Hl7Segment() :
    Hl7MessagePart(),
    m_fields(),
    m_segmentId()
{
}

Hl7Segment::Hl7Segment(QWeakPointer<const Hl7Message> parent,
                       const QString &segmentId,
                       const QMap<qint64, QSharedPointer<Hl7Field> > &fields,
                       QSharedPointer<const Hl7EncodingCharacters> encodingCharacters) :
    Hl7MessagePart(parent, encodingCharacters),
    m_fields(fields),
    m_segmentId(segmentId)
{
}

}

