#pragma once
#include "config/config_secrets.h"

#define WEB_SERVER_NAME "pot-warden"

//=====SPIFFS DATA LOGGING SECTION=====
//define for writing data to spiffs, not only writing to console
//#define ENABLE_READINGS_LOGGING
#define READINGS_DIR "/readings"

//=====TIME CONTROL SECTION=====
#define INTERVAL_SECOND   1000
#define INTERVAL_MINUTE   60000
#define INTERVAL_HOUR     360000

#define INTERVAL_STATUS_LED 2 * INTERVAL_SECOND
#define INTERVAL_READ_SENSORS 30 * INTERVAL_SECOND

#define DATETIME_FORMAT_DEFAULT ISO8601
#define DATETIME_FORMAT_DATEONLY "Y-m-d"

//=====GENERAL SECTION=====
#define LIMIT_POUR_DURATION 30 * INTERVAL_SECOND //30 seconds max pour duration via API
