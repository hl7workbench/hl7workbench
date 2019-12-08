/*
 * This file is part of the HL7 Workbench project.
 *
 * Copyright (C) 2019  Individual HL7 Workbench contributors.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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

    void testCase_Hl7Message_fromString_V24_3_5_1_AdtA01();
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

void UnitTests::testCase_Hl7Message_fromString_V24_3_5_1_AdtA01()
{
    QString messageString = "MSH|^~\\&|ADT1|MCM|LABADT|MCM|198808181126|SECURITY|ADT^A01|MSG00001|P|2.4|\r"
                            "EVN|A01|198808181123||\r"
                            "PID|1||PATID1234^5^M11^ADT1^MR^MCM~123456789^^^USSSA^SS||JONES^WILLIAM^A^III||19610615|M||C|1200 N ELM STREET^^GREENSBORO^NC^27401-1020|GL|(91-PATID12345001^2^M10^ADT1^AN^A|123456789|987654^NC|\r"
                            "NK1|1|JONES^BARBARA^K|WI^WIFE||||NK^NEXT OF KIN\r"
                            "PV1|1|I|2000^2012^01||||004777^LEBAUER^SIDNEY^J.|||SUR||||ADM|A0|";

    QSharedPointer<HL7WB::Hl7Message> message = HL7WB::Hl7Message::fromString(messageString);

    QVERIFY(!message.isNull());
    QVERIFY(message->isValid());

    // test MSH-1 and MSH-2 which are a little bit special
    QCOMPARE(message->field("MSH", 1)->toString(), QString("|"));
    QCOMPARE(message->field("MSH", 2)->toString(), QString("^~\\&"));

    // field with data
    QVERIFY(!message->field("EVN", 1).isNull());
    QCOMPARE(message->field("EVN", 1)->toString(), QString("A01"));
    QVERIFY(!message->segment("EVN")->field(1).isNull());
    QCOMPARE(message->segment("EVN")->field(1)->toString(), QString("A01"));

    // field with no data
    QVERIFY(!message->field("EVN", 3).isNull());
    QVERIFY(message->field("EVN", 3)->toString().isEmpty());
    QVERIFY(!message->segment("EVN")->field(3).isNull());
    QVERIFY(message->segment("EVN")->field(3)->toString().isEmpty());

    // empty at end of segment
    QVERIFY(!message->field("EVN", 4).isNull());
    QVERIFY(message->field("EVN", 4)->toString().isEmpty());
    QVERIFY(!message->segment("EVN")->field(4).isNull());
    QVERIFY(message->segment("EVN")->field(4)->toString().isEmpty());

    // valid segment, invalid field
    QVERIFY(!message->segment("EVN").isNull());
    QVERIFY(message->field("EVN", 5).isNull());
    QVERIFY(message->segment("EVN")->field(5).isNull());

    // invalid segment, invalid field
    QVERIFY(message->segment("AIL").isNull());
    QVERIFY(message->field("AIL", 1).isNull());

    // component with data
    QVERIFY(!message->component("PID", 11, 1).isNull());
    QCOMPARE(message->component("PID", 11, 1)->toString(), QString("1200 N ELM STREET"));
    QVERIFY(!message->segment("PID")->component(11, 1).isNull());
    QCOMPARE(message->segment("PID")->component(11, 1)->toString(), QString("1200 N ELM STREET"));
    QVERIFY(!message->segment("PID")->field(11)->component(1).isNull());
    QCOMPARE(message->segment("PID")->field(11)->component(1)->toString(), QString("1200 N ELM STREET"));
    QVERIFY(!message->field("PID", 11)->component(1).isNull());
    QCOMPARE(message->field("PID", 11)->component(1)->toString(), QString("1200 N ELM STREET"));

    // component with no data
    QVERIFY(!message->component("PID", 11, 2).isNull());
    QVERIFY(message->component("PID", 11, 2)->toString().isEmpty());
    QVERIFY(!message->segment("PID")->component(11, 2).isNull());
    QVERIFY(message->segment("PID")->component(11, 2)->toString().isEmpty());
    QVERIFY(!message->segment("PID")->field(11)->component(2).isNull());
    QVERIFY(message->segment("PID")->field(11)->component(2)->toString().isEmpty());
    QVERIFY(!message->field("PID", 11)->component(2).isNull());
    QVERIFY(message->field("PID", 11)->component(2)->toString().isEmpty());

    // valid field, invalid component
    QVERIFY(message->component("PID", 11, 6).isNull());
    QVERIFY(message->segment("PID")->component(11, 6).isNull());
    QVERIFY(message->segment("PID")->field(11)->component(6).isNull());
    QVERIFY(message->field("PID", 11)->component(6).isNull());

    // valid segment, invalid field
    QVERIFY(message->component("EVN", 5, 1).isNull());
    QVERIFY(message->segment("EVN")->component(5, 1).isNull());

    // test the MSH-9 field, reading components and combined as a field
    QCOMPARE(message->field("MSH", 9)->toString(), QString("ADT^A01"));
    QCOMPARE(message->component("MSH", 9, 1)->toString(), QString("ADT"));
    QCOMPARE(message->component("MSH", 9, 2)->toString(), QString("A01"));

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
