#include "airtemp_and_humidity_sensor.h"
#include "application.h"

#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

AirtempAndHumiditySensor::AirtempAndHumiditySensor(struct temperatures *ptr_temperatures, struct calibrations *ptr_calibrations) {
  Serial.println("In setup temp and humidity");
  m_ptr_temperatures = ptr_temperatures;
  m_ptr_calibrations = ptr_calibrations;
  setup();
}

void AirtempAndHumiditySensor::setup() { dht.begin(); }

void AirtempAndHumiditySensor::begin() {
  delay(50);
  Serial.println("-------------------------");
  Serial.println("Temp and humidity sensor ready. Temp is:");
  Serial.println(dht.getTempCelcius());
  Serial.println("-------------------------");
}

void AirtempAndHumiditySensor::readCelsiusFromSensor() {
  m_ptr_temperatures->currentOnLandTemperature = (double)dht.getTempCelcius() + m_ptr_calibrations->airTempCalibration;
}

void AirtempAndHumiditySensor::readHumidityFromSensor() {
  m_ptr_temperatures->currentOnLandHumidity = (double)dht.getHumidity() + m_ptr_calibrations->landHumidityCalibration;
}
