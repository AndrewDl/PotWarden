#pragma once
#include "config_secrets.h"

#define WEB_SERVER_NAME "pot-warden-test"

//=====SPIFFS DATA LOGGING SECTION=====
//define for writing data to spiffs, not only writing to console
//#define ENABLE_READINGS_LOGGING
#define READINGS_DIR "/readings"

//=====TIME CONTROL SECTION=====
#define INTERVAL_SECOND   1000
#define INTERVAL_MINUTE   60000
#define INTERVAL_HOUR     360000

#define INTERVAL_STATUS_LED 2 * INTERVAL_SECOND
#define INTERVAL_READ_SENSORS 5 * INTERVAL_SECOND
#define INTERVAL_LOG_SENSOR_DATA 10 * INTERVAL_MINUTE
#define INTERVAL_CHECK_ACTIONS 500

#define DATETIME_FORMAT_DEFAULT ISO8601
#define DATETIME_FORMAT_DATEONLY "Y-m-d"

//=====AUTOMATION SECTION=====
#define ENABLE_ACTIONS_EXECUTION
#define ENABLE_AUTO_POUR
#define LIMIT_POUR_DURATION 30 * INTERVAL_SECOND //30 seconds max pour duration via API
#define AUTO_POUR_DURATION 10 * INTERVAL_SECOND

#define MOISTURE_THRESHOLD_DRY 2400
#define MOISTURE_THRESHOLD_WET 2000 //Value below which soil is considered sufficiently wet
#define MOISTURE_THRESHOLD_ERROR 4000 //If sensor reading is above this value, consider it an error
//====================================
