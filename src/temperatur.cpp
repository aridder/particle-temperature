/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "/home/aridder/Particle/temperatur/src/temperatur.ino"
#include "airtemp_and_humidity_sensor.h"
#include "calibrations.h"
#include "gyroscope.h"
#include "light.h"
#include "particle_communication.h"
#include "sd_card.h"
#include "tft.h"
#include "watertemp_sensor.h"

void setup();
void loop();
void readFromTempAndHumiditySensors(unsigned long currentMillis);
void readFromGyrometerAndDrawTheAccelerationDataOnTFT(unsigned long currentMillis);
void readChangeTFTScreenPage(unsigned long currentMillis);
void publishEvents(unsigned long currentMillis);
void setupSerial();
#line 10 "/home/aridder/Particle/temperatur/src/temperatur.ino"
SerialDebugOutput debugOutput;

struct update_intervals {
  const unsigned long UPDATE_INTERVAL_GYROSCOPE = 100;
  const unsigned long UPDATE_INTERVAL_TEMP_HUM  = 2000;
  const unsigned long UPDATE_INTERVAL_BUTTON    = 100;
  const unsigned long UPDATE_INTERVAL_PUBLISH   = 60000;
  unsigned long       lastUpdateGyroscope       = 0;
  unsigned long       lastUpdateTempHum         = 0;
  unsigned long       lastUpdateButton          = 0;
  unsigned long       lastPublishData           = 0;
} update_intervals;

struct temperatures temperature = {
    .currentWaterTemp           = -1000.00,
    .currentOnLandHumidity      = -1000.00,
    .currentOnLandTemperature   = -1000.00,
    .number_of_wave_measurments = 0};

struct calibrations calibration = {
    .waterTempCalibration    = 0.00,
    .airTempCalibration      = 0.00,
    .landHumidityCalibration = 0.00,
    .time                    = 0,
    .lightOnLimit            = 24.00};

struct acceleration_measurements acceleration_measurement = {
    .ax                                   = -1000,
    .ay                                   = -1000,
    .az                                   = -1000,
    .number_of_wave_measurments           = 0,
    .diff_in_z_axis_last_ten_measurements = -10000,
};

SDCard                   sdCard(&calibration);
TFT                      tft(&temperature, &acceleration_measurement, &calibration);
WaterTempSensor          waterTempSensor(&temperature, &calibration);
AirtempAndHumiditySensor airtempAndHumiditySensor(&temperature, &calibration);
Light                    light(&temperature, &calibration);
Gyroscope                gyroscope(&acceleration_measurement);
ParticleCommunication    particleCommunication(&temperature, &acceleration_measurement, &calibration, &sdCard);

const int     BUTTON_PIN         = D5;
int           buttonState        = 0;
volatile bool shouldShowTempPage = FALSE;

void setup() {
  setupSerial();

  pinMode(BUTTON_PIN, INPUT);
  delay(2000);

  sdCard.begin();
  particleCommunication.begin();
  tft.begin();
  light.begin();
  gyroscope.begin();
  waterTempSensor.begin();
  airtempAndHumiditySensor.begin();

  tft.clearScreen();
}

void loop() {
  unsigned long currentMillis = millis();

  readChangeTFTScreenPage(currentMillis);
  readFromTempAndHumiditySensors(currentMillis);
  readFromGyrometerAndDrawTheAccelerationDataOnTFT(currentMillis);
  publishEvents(currentMillis);

  tft.drawTime();

  if (shouldShowTempPage) {
    tft.drawTempAndHumidity();
  } else {
    tft.drawWaveIndicationColor();
    tft.drawAcc();
  }
  light.setRedLight();
}

void readFromTempAndHumiditySensors(unsigned long currentMillis) {
  if (currentMillis - update_intervals.lastUpdateTempHum >= update_intervals.UPDATE_INTERVAL_TEMP_HUM) {
    update_intervals.lastUpdateTempHum = millis();

    waterTempSensor.readCelsiusTempFromSensor();
    airtempAndHumiditySensor.readHumidityFromSensor();
    airtempAndHumiditySensor.readCelsiusFromSensor();
  }
}

void readFromGyrometerAndDrawTheAccelerationDataOnTFT(unsigned long currentMillis) {
  if (currentMillis - update_intervals.lastUpdateGyroscope >= update_intervals.UPDATE_INTERVAL_GYROSCOPE) {
    update_intervals.lastUpdateGyroscope = millis();

    gyroscope.readValuesFromSensor();

    acceleration_measurement.number_of_wave_measurments++;
    if (acceleration_measurement.number_of_wave_measurments == 10) {
      gyroscope.set_wave_color_indicatior_from_z_axis_measurements();
      acceleration_measurement.number_of_wave_measurments = 0;
    }
  }
}

void readChangeTFTScreenPage(unsigned long currentMillis) {
  if (currentMillis - update_intervals.lastUpdateButton >= update_intervals.UPDATE_INTERVAL_BUTTON) {
    buttonState = digitalRead(BUTTON_PIN);
    

    if (buttonState == HIGH) {
      sdCard.openFileToReadAndRead();
      update_intervals.lastUpdateButton = currentMillis;
      shouldShowTempPage                = !shouldShowTempPage;
      tft.clearScreen();
    }
  }
}

void publishEvents(unsigned long currentMillis) {
  if (currentMillis - update_intervals.lastPublishData >= update_intervals.UPDATE_INTERVAL_PUBLISH) {
    update_intervals.lastPublishData = millis();
    particleCommunication.publishData();
  }
}

void setupSerial() {
  while (!Serial) {
    SysCall::yield();
  }
}