#include "Hl7Component.h"
#include "Hl7Field.h"
#include "Hl7Message.h"

#include <QString>
#include <QtTest>

namespace HL7WB
{

class UnitTests : public QObject
{
    Q_OBJECT

public:
    UnitTests();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testCase_Parser_V24_3_5_1_AdtA01();
};

UnitTests::UnitTests()
{
}

void UnitTests::initTestCase()
{
}

void UnitTests::cleanupTestCase()
{
}

void UnitTests::testCase_Parser_V24_3_5_1_AdtA01()
{
    QString messageString = "MSH|^~\\&|ADT1|MCM|LABADT|MCM|198808181126|SECURITY|ADT^A01|MSG00001|P|2.4|\r"
                            "EVN|A01|198808181123||\r"
                            "PID|1||PATID1234^5^M11^ADT1^MR^MCM~123456789^^^USSSA^SS||JONES^WILLIAM^A^III||19610615|M||C|1200 N ELM STREET^^GREENSBORO^NC^27401-1020|GL|(91-PATID12345001^2^M10^ADT1^AN^A|123456789|987654^NC|\r"
                            "NK1|1|JONES^BARBARA^K|WI^WIFE||||NK^NEXT OF KIN\r"
                            "PV1|1|I|2000^2012^01||||004777^LEBAUER^SIDNEY^J.|||SUR||||ADM|A0|";

    QSharedPointer<HL7WB::Hl7Message> message = HL7WB::Hl7Message::fromString(messageString);

    QVERIFY(!message.isNull());
    QVERIFY(message->isValid());

    QCOMPARE(message->field("MSH", 1)->toString(), QString("|"));
    QCOMPARE(message->field("MSH", 2)->toString(), QString("^~\\&"));

    // Patient William A. Jones, III
    QCOMPARE(message->component("PID", 5, 2)->toString(), QString("WILLIAM"));
    QCOMPARE(message->component("PID", 5, 3)->toString(), QString("A"));
    QCOMPARE(message->component("PID", 5, 1)->toString(), QString("JONES"));
    QCOMPARE(message->component("PID", 5, 4)->toString(), QString("III"));

    // was admitted on July [sic.] 18, 1988 at 11:23 a.m.
    QCOMPARE(message->field("EVN", 2)->toDateTime(),
             QDateTime(QDate(1988, 8, 18), QTime(11, 23)));

    // by doctor Sidney J. Lebauer (#004777)
    QCOMPARE(message->component("PV1", 7, 3)->toString(), QString("SIDNEY"));
    QCOMPARE(message->component("PV1", 7, 4)->toString(), QString("J."));
    QCOMPARE(message->component("PV1", 7, 2)->toString(), QString("LEBAUER"));
    QCOMPARE(message->component("PV1", 7, 1)->toString(), QString("004777"));

    // for surgery (SUR).
    QCOMPARE(message->field("PV1", 10)->toString(), QString("SUR"));

    // He has been assigned to room 2012, bed 01 on nursing unit 2000.
    QCOMPARE(message->component("PV1", 3, 2)->toString(), QString("2012"));
    QCOMPARE(message->component("PV1", 3, 3)->toString(), QString("01"));
    QCOMPARE(message->component("PV1", 3, 1)->toString(), QString("2000"));

    // The message was sent from system ADT1 at the MCM site to system LABADT,
    // also at the MCM site, on
    QCOMPARE(message->field("MSH", 3)->toString(), QString("ADT1"));
    QCOMPARE(message->field("MSH", 4)->toString(), QString("MCM"));
    QCOMPARE(message->field("MSH", 5)->toString(), QString("LABADT"));
    QCOMPARE(message->field("MSH", 6)->toString(), QString("MCM"));

    // the same date as the admission took place, but three minutes after the
    // admit.
    QCOMPARE(message->field("MSH", 7)->toDateTime(),
             QDateTime(QDate(1988, 8, 18), QTime(11, 26)));
}

} // namespace

QTEST_APPLESS_MAIN(HL7WB::UnitTests)

#include "UnitTests.moc"
