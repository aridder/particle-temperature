#include "watertemp_sensor.h"
#include "application.h"

#define TEMP_SENSOR_INPUT A7

WaterTempSensor::WaterTempSensor(struct temperatures *ptr_temperatures, struct calibrations *ptr_calibration) {
  m_ptr_temperatures = ptr_temperatures;
  m_ptr_calibrations = ptr_calibration;
  setup();
}

void WaterTempSensor::setup() { pinMode(TEMP_SENSOR_INPUT, INPUT); }

void WaterTempSensor::begin() {

}

void WaterTempSensor::readCelsiusTempFromSensor() {
  m_ptr_temperatures->currentWaterTemp = (double)analogRead(TEMP_SENSOR_INPUT) * 0.08 + m_ptr_calibrations->waterTempCalibration;
}
