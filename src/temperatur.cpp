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

void setup();
void loop();
void setupSerial();
void readFromTempAndHumiditySensors(unsigned long currentMillis);
void readFromGyrometerAndDrawTheAccelerationDataOnTFT(
    unsigned long currentMillis);
#line 7 "/home/aridder/Particle/temperatur/src/temperatur.ino"
SerialDebugOutput debugOutput;

struct update_intervals {
  const unsigned long UPDATE_INTERVAL_GYROSCOPE = 100;
  const unsigned long UPDATE_INTERVAL_TEMP_HUM = 2000;
  unsigned long lastUpdateGyroscope = 0;
  unsigned long lastUpdateTempHum = 0;
} update_intervals;

struct temperatures temperature = {.currentWaterTemp = -1,
                                   .currentOnLandHumidity = -1,
                                   .currentOnLandTemperature = -1,
                                   .number_of_wave_measurments = 0};

struct acceleration_measurements acceleration_measurement = {
    .ax = -1, .ay = -1, .az = -1, .number_of_wave_measurments = 0};

TFT tft(&temperature, &acceleration_measurement);
WaterTempSensor waterTempSensor(&temperature);
AirtempAndHumiditySensor airtempAndHumiditySensor(&temperature);
Light light(&temperature);
Gyroscope gyroscope(&acceleration_measurement);

void setup() {
  setupSerial();
  Particle.publishVitals(20);

  tft.begin();
  light.begin();
  gyroscope.begin();
  waterTempSensor.begin();
  airtempAndHumiditySensor.begin();

  tft.clearScreen();
}

void loop() {
  unsigned long currentMillis = millis();
  readFromTempAndHumiditySensors(currentMillis);
  readFromGyrometerAndDrawTheAccelerationDataOnTFT(currentMillis);

  tft.drawTime();
  tft.drawWaveIndicationColor();
  tft.drawAcc();

  // tft.drawWaterTemp(currentWaterTemp, ST7735_WHITE);
  // tft.drawOnLandTemp(currentOnLandTemperature, ST7735_WHITE);

  light.setRedLight();
}

void setupSerial() {
  Serial.begin(9600);

  while (Serial.available() && Serial.read())
    ;

  while (!Serial.available()) {
    delay(1500);
  }
  while (Serial.available() && Serial.read())
    ;
}

void readFromTempAndHumiditySensors(unsigned long currentMillis) {
  if (currentMillis - update_intervals.lastUpdateTempHum >=
      update_intervals.UPDATE_INTERVAL_TEMP_HUM) {
    update_intervals.lastUpdateTempHum = millis();

    waterTempSensor.readCelsiusTempFromSensor();
    // temperature.currentWaterTemp =
    // waterTempSensor.getCelsiusTempFromSensor();
    airtempAndHumiditySensor.readHumidityFromSensor();
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