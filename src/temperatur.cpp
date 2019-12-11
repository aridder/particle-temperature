/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "application.h"
#line 1 "/home/aridder/Particle/temperatur/src/temperatur.ino"
#include "airtemp_and_humidity_sensor.h"
#include "gyroscope.h"
#include "light.h"
#include "tft.h"
#include "watertemp_sensor.h"
#include "particle_communication.h"
#include "calibrations.h"

void setup();
void loop();
void setupSerial();
void readFromTempAndHumiditySensors(unsigned long currentMillis);
void readFromGyrometerAndDrawTheAccelerationDataOnTFT(
    unsigned long currentMillis);
void readChangeTFTScreenPage(unsigned long currentMillis);
#line 9 "/home/aridder/Particle/temperatur/src/temperatur.ino"
SerialDebugOutput debugOutput;

struct update_intervals {
  const unsigned long UPDATE_INTERVAL_GYROSCOPE = 100;
  const unsigned long UPDATE_INTERVAL_TEMP_HUM = 2000;
  const unsigned long UPDATE_INTERVAL_BUTTON = 500;
  unsigned long lastUpdateGyroscope = 0;
  unsigned long lastUpdateTempHum = 0;
  unsigned long lastUpdateButton = 0;

} update_intervals;

struct temperatures temperature = {.currentWaterTemp = -1000.00,
                                   .currentOnLandHumidity = -1000.00,
                                   .currentOnLandTemperature = -1000.00,
                                   .number_of_wave_measurments = 0};

struct calibrations calibration = {
  .waterTempCalibration = 0.00,
  .airTempCalibration = 0.00,
  .landHumidityCalibration = 0.00,
};

struct acceleration_measurements acceleration_measurement = {
    .ax = -1000, .ay = -1000, .az = -1000, .number_of_wave_measurments = 0};

TFT tft(&temperature, &acceleration_measurement);
WaterTempSensor waterTempSensor(&temperature, &calibration);
AirtempAndHumiditySensor airtempAndHumiditySensor(&temperature, &calibration);
Light light(&temperature);
Gyroscope gyroscope(&acceleration_measurement);
ParticleCommunication particleCommunication(&temperature, &acceleration_measurement, &calibration);

const int BUTTON_PIN = D5;
int buttonState = 0;
bool shouldShowTempPage = 1;

void setup() {
  setupSerial();
  particleCommunication.begin();

  pinMode(BUTTON_PIN, INPUT);
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
  

  tft.drawTime();

  if (shouldShowTempPage) {
    tft.drawTempAndHumidity();
  } else {
    tft.drawWaveIndicationColor();
    tft.drawAcc();
  }

  light.setRedLight();
}

void setupSerial() {
  Serial.begin(9600);

  while (Serial.available() && Serial.read());
  while (!Serial.available()) {
    delay(1500);
  }
  while (Serial.available() && Serial.read());
}

void readFromTempAndHumiditySensors(unsigned long currentMillis) {
  if (currentMillis - update_intervals.lastUpdateTempHum >=
      update_intervals.UPDATE_INTERVAL_TEMP_HUM) {
    update_intervals.lastUpdateTempHum = millis();

    waterTempSensor.readCelsiusTempFromSensor();
    airtempAndHumiditySensor.readHumidityFromSensor();
    airtempAndHumiditySensor.readCelsiusFromSensor();
  }
}

void readFromGyrometerAndDrawTheAccelerationDataOnTFT(
    unsigned long currentMillis) {
  if (currentMillis - update_intervals.lastUpdateGyroscope >=
      update_intervals.UPDATE_INTERVAL_GYROSCOPE) {
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
      update_intervals.lastUpdateButton = currentMillis;
      shouldShowTempPage = !shouldShowTempPage;
      tft.clearScreen();
    }
  }
}