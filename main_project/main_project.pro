TEMPLATE = subdirs

# Using subdirs to separate the application and two unit test
# Qt recommends putting each unit test class in it's own project
SUBDIRS += \
    ../app \
    ../unittest_SensorControl \
    ../unittest_Greenhouse \
    ../unittest_NotificationControl \
    ../unittest_Notification \
    ../unittest_Log \
    ../unittest_WaterControl \
    ../unittest_Clock \
    ../unittest_PlantGroup \
    ../unittest_Plant \
    ../unittest_GreenhouseCreate \
    ../unittest_Condition \
    ../unittest_FireAlarm \
    ../unittest_FlowSensor \
    ../integrationstest_Sensor_SensorControl \
    ../integrationstest_WaterValve_WaterControl \
    ../systemtest_Greenhousecontrol

