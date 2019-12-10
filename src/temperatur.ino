#include "airtemp_and_humidity_sensor.h"
#include "gyroscope.h"
#include "light.h"
#include "tft.h"
#include "watertemp_sensor.h"

SerialDebugOutput debugOutput;

struct update_intervals {
  const unsigned long UPDATE_INTERVAL_GYROSCOPE = 100;
  const unsigned long UPDATE_INTERVAL_TEMP_HUM = 2000;
  const unsigned long UPDATE_INTERVAL_BUTTON = 500;
  unsigned long lastUpdateGyroscope = 0;
  unsigned long lastUpdateTempHum = 0;
  unsigned long lastUpdateButton = 0;

} update_intervals;

struct temperatures temperature = {.currentWaterTemp = -1.00f,
                                   .currentOnLandHumidity = -1.00f,
                                   .currentOnLandTemperature = -1.00f,
                                   .number_of_wave_measurments = 0};

struct acceleration_measurements acceleration_measurement = {
    .ax = -1, .ay = -1, .az = -1, .number_of_wave_measurments = 0};

TFT tft(&temperature, &acceleration_measurement);
WaterTempSensor waterTempSensor(&temperature);
AirtempAndHumiditySensor airtempAndHumiditySensor(&temperature);
Light light(&temperature);
Gyroscope gyroscope(&acceleration_measurement);

const int BUTTON_PIN = D5;
int buttonState = 0;
bool shouldShowTempPage = 1;

void setup() {
  setupSerial();
  Particle.publishVitals(20);

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
  readFromTempAndHumiditySensors(currentMillis);
  readFromGyrometerAndDrawTheAccelerationDataOnTFT(currentMillis);

  if (currentMillis - update_intervals.lastUpdateButton >=
      update_intervals.UPDATE_INTERVAL_BUTTON) {
    buttonState = digitalRead(BUTTON_PIN);
    if (buttonState == HIGH) {
      update_intervals.lastUpdateButton = currentMillis;
      shouldShowTempPage = !shouldShowTempPage;
      tft.clearScreen();
    }
  }

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