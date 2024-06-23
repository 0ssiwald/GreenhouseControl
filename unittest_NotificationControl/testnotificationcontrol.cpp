#include "testnotificationcontrol.h"
#include "date_time.h"

bool notification_is_the_same = false;

bool Notification::isNotificationTheSameForAnotherPlant(std::chrono::system_clock::time_point, int, std::string, std::string, NotificationTypes) {
    return notification_is_the_same;
}
// method to get all private attributes of Notification
std::string Notification::getNotificationMessage() {
    std::ostringstream notification_stream;
    notification_stream << DateTimeConverter::timePointToString(activation_timepoint_) << " " << week_index_ << " ";
    notification_stream << group_name_ << " " << value_as_string_ << " ";
    for (auto &it: plant_names_) {
        notification_stream << it << " ";
    }
    if (notification_type_ == NotificationTypes::LampDistanceNotification)
        notification_stream << "LampDistanceNotification";
    else if (notification_type_ == NotificationTypes::TemperatureNotification)
        notification_stream << "TemperatureNotification";
    else if (notification_type_ == NotificationTypes::HumidityNotification)
        notification_stream << "HumidityNotification";
    else if (notification_type_ == NotificationTypes::FertilizerNotification)
        notification_stream << "FertilizerNotification";
    return notification_stream.str();
}

std::vector<Plant*> PlantGroup::getPlants() {return plants_;}
std::string Condition::getFertilazersAsString() {return "test";}

void TestNotificationControl::init() {
    sut = new NotificationControl;
}
void TestNotificationControl::cleanup() {
    delete sut;
}

void TestNotificationControl::initTestCase() {
    notification1_ = new Notification;
    notification2_ = new Notification;
}

void TestNotificationControl::cleanupTestCase() {
    delete notification1_;
    delete notification2_;
}

void TestNotificationControl::testloadNotificationsFromFile() {
    // Create a temporary JSON file with notification data
    QString fileName = "test_notifications.json";
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QFAIL("Unable to create test JSON file");
    }

    QByteArray jsonContent = R"(
        [
            {
                "activation_timepoint": "20.05.2024 03:34:57",
                "week_index": 0,
                "group_name": "1",
                "plant_names": ["1", "2"],
                "value_as_string": "40",
                "notification_type": "LampDistanceNotification"
            },
            {
                "activation_timepoint": "20.05.2024 13:34:56",
                "week_index": 0,
                "group_name": "1",
                "plant_names": ["1", "2"],
                "value_as_string": "24.0",
                "notification_type": "TemperatureNotification"
            }
        ]
        )";

    file.write(jsonContent);
    file.close();

    // Load notifications from the file
    bool result = sut->loadNotificationsFromFile(fileName.toStdString());
    QVERIFY(result);  // Verify that the method returned true

    // Verify the notifications were loaded correctly
    const auto& notifications = sut->getImpendingNotifications();
    // Verify the number of notifications
    const long unsigned int size = 2;
    QCOMPARE(notifications.size(), size);

    QCOMPARE(QString::fromStdString(notifications[0]->getNotificationMessage()),
             QString("20.05.2024 03:34:57 0 1 40 1 2 LampDistanceNotification"));
    QCOMPARE(QString::fromStdString(notifications[1]->getNotificationMessage()),
             QString("20.05.2024 13:34:56 0 1 24.0 1 2 TemperatureNotification"));

    // Clean up the test JSON file
    file.remove();
}

void TestNotificationControl::testDeleteNotification() {
    sut->addToActiveNotificationList(notification1_);
    sut->addToActiveNotificationList(notification2_);
    // invalid index should not work
    QVERIFY(sut->getActiveNotificationList().size() == 2);
    QVERIFY(!sut->deleteNotification(2));
    // 2 times valid index
    QVERIFY(sut->deleteNotification(0));
    QVERIFY(sut->deleteNotification(0));
    QVERIFY(sut->getActiveNotificationList().size() == 0);
}

void TestNotificationControl::testAddNotificationToVector() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    QVERIFY(sut->getImpendingNotifications().size() == 0);
    // Add two notificaitons
    sut->addNotificationToVector(now, 0, "TestGroupName", "TestName", "Test", NotificationTypes::HumidityNotification);
    QVERIFY(sut->getImpendingNotifications().size() == 1);
    sut->addNotificationToVector(now, 0, "TestGroupName", "TestName", "Test2", NotificationTypes::HumidityNotification);
    QVERIFY(sut->getImpendingNotifications().size() == 2);
    // The same notification should not be added
    notification_is_the_same = true;
    sut->addNotificationToVector(now, 0, "TestGroupName", "TestName", "Test2", NotificationTypes::HumidityNotification);
    QVERIFY(sut->getImpendingNotifications().size() == 2);
}

void TestNotificationControl::testUpdateActiveNotificationList() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point one_minute_later = now + std::chrono::minutes(1);
    std::chrono::system_clock::time_point one_minute_earlier = now - std::chrono::minutes(1);
    std::vector<std::string> name_vector;
    Notification notification = Notification(one_minute_earlier, 0, "TestGroupName", name_vector, "Test", NotificationTypes::HumidityNotification);
    Notification notification2 = Notification(one_minute_later, 0, "TestGroupName", name_vector, "Test", NotificationTypes::HumidityNotification);
    sut->addToImpendingNotifications(&notification);
    QVERIFY(sut->getActiveNotificationList().size() == 0);
    QVERIFY(sut->getImpendingNotifications().size() == 1);
    // Adding a notification from the past should work
    sut->updateActiveNotificationList();
    QVERIFY(sut->getActiveNotificationList().size() == 1);
    QVERIFY(sut->getImpendingNotifications().size() == 0);
    // Adding a ntification from the future should not work
    sut->addToImpendingNotifications(&notification2);
    sut->updateActiveNotificationList();
    QVERIFY(sut->getActiveNotificationList().size() == 1);
    QVERIFY(sut->getImpendingNotifications().size() == 1);
}

QTEST_APPLESS_MAIN(TestNotificationControl);






