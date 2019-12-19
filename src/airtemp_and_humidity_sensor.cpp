#include "airtemp_and_humidity_sensor.h"

#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

AirtempAndHumiditySensor::AirtempAndHumiditySensor(struct temperatures *ptr_temperatures, struct calibrations *ptr_calibrations) {
  m_ptr_temperatures = ptr_temperatures;
  m_ptr_calibrations = ptr_calibrations;
  setup();
}

void AirtempAndHumiditySensor::setup() { dht.begin(); }

void AirtempAndHumiditySensor::begin() {
}

void AirtempAndHumiditySensor::readCelsiusFromSensor() {
  float tmp = dht.getTempCelcius();
  if (isnan(tmp)) {
    return;
  }
  m_ptr_temperatures->currentOnLandTemperature = (double)tmp + m_ptr_calibrations->airTempCalibration;
}

void AirtempAndHumiditySensor::readHumidityFromSensor() {
  float hum = dht.getHumidity();
  if (isnan(hum)) {
    return;
  }
  m_ptr_temperatures->currentOnLandHumidity = (double)hum + m_ptr_calibrations->landHumidityCalibration;
}
