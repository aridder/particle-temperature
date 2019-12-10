#include "watertemp_sensor.h"
#include "application.h"

#define TEMP_SENSOR_INPUT A4

WaterTempSensor::WaterTempSensor(struct temperatures *ptr_temperatures) {
  m_ptr_temperatures = ptr_temperatures;
  setup();
}

void WaterTempSensor::setup() { pinMode(TEMP_SENSOR_INPUT, INPUT); }

void WaterTempSensor::begin() {
  delay(50);
  Serial.println("-------------------------");
  Serial.println("Temp sensor water is ready. Temp is:");
  Serial.println(analogRead(TEMP_SENSOR_INPUT));
  Serial.println("-------------------------");
}

void WaterTempSensor::readCelsiusTempFromSensor() {
  m_ptr_temperatures->currentWaterTemp = analogRead(TEMP_SENSOR_INPUT) * 0.08;
}
