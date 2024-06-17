#include "testnotification.h"
#include "date_time.h"

#include <QDebug>

std::chrono::system_clock::time_point time_point = DateTimeConverter::stringToTimePoint("22.05.2024 16:00:00");
int week_index = 0;
std::string group_name = "test_group";
std::vector<std::string> plant_names = {"name1"};
std::string value_as_string = "test_value";
NotificationTypes notification_type = NotificationTypes::FertilizerNotification;

void TestNotification::initTestCase() {
    sut = new Notification(time_point, week_index, group_name, plant_names, value_as_string, notification_type);
}

void TestNotification::cleanupTestCase() {
    delete sut;
}
void TestNotification::testIsNotificationTheSameForAnotherPlant() {
    // same should return true
    QVERIFY(sut->isNotificationTheSameForAnotherPlant(time_point, week_index, group_name, value_as_string, notification_type));
    // with diffrent values should return false
    QVERIFY(!sut->isNotificationTheSameForAnotherPlant(time_point, week_index+1, group_name, value_as_string, notification_type));
    // on the same day one hour later should still be the same
    QVERIFY(sut->isNotificationTheSameForAnotherPlant(DateTimeConverter::stringToTimePoint("22.05.2024 19:00:00"), week_index, group_name, value_as_string, notification_type));
    // on the next day not
    QVERIFY(!sut->isNotificationTheSameForAnotherPlant(DateTimeConverter::stringToTimePoint("23.05.2024 19:00:00"), week_index, group_name, value_as_string, notification_type));
}
void TestNotification::testGetNotificationMessage() {
    // Test the output string for one plant
    std::string compare_string = "Woche 1 Gruppe test_group:\nDie Pflanze name1 muss gedüngt werden mit:\ntest_value";
    QVERIFY(compare_string == sut->getNotificationMessage());
    // Test the string for more than one plant
    sut->addPlant("name2");
    compare_string = "Woche 1 Gruppe test_group:\nDie Pflanzen name1, name2 müssen gedüngt werden mit:\ntest_value";
    QVERIFY(compare_string == sut->getNotificationMessage());
}


QTEST_APPLESS_MAIN(TestNotification);

