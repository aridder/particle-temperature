#include "gyroscope.h"
#include "MPU6050.h"
#include "application.h"

Gyroscope::Gyroscope(struct acceleration_measurements *acceleration_measurements) {
  m_ptr_acceleration_measurements = acceleration_measurements;
  gyrometer                       = new MPU6050();
  setup();
}

void Gyroscope::setup() {
  Wire.begin();
  gyrometer->initialize();
  gyrometer->setXAccelOffset(0);
  gyrometer->setYAccelOffset(0);
  gyrometer->setZAccelOffset(0);
  gyrometer->setXGyroOffset(0);
  gyrometer->setYGyroOffset(0);
  gyrometer->setZGyroOffset(0);
}

void Gyroscope::begin() {
}

void Gyroscope::push_z_axis_value_to_queue(int az) {
  last_ten_z_axis_measurements_queue.push(az);
}

void Gyroscope::readValuesFromSensor() {
  m_ptr_acceleration_measurements->ax = gyrometer->getAccelerationX();
  m_ptr_acceleration_measurements->ay = gyrometer->getAccelerationY();
  m_ptr_acceleration_measurements->az = gyrometer->getAccelerationZ();
  push_z_axis_value_to_queue(m_ptr_acceleration_measurements->az);
}

void Gyroscope::set_wave_color_indicatior_from_z_axis_measurements() {
  bool is_first = true;
  int  current  = 0;
  int  min      = -1;
  int  max      = -1;

  while (!last_ten_z_axis_measurements_queue.empty()) {
    current = last_ten_z_axis_measurements_queue.front();
    if (is_first) {
      min      = current;
      max      = current;
      is_first = false;
    }

    if (current > max) {
      max = current;
    } else if (current < min) {
      min = current;
    }
    last_ten_z_axis_measurements_queue.pop();
  }
  m_ptr_acceleration_measurements->diff_in_z_axis_last_ten_measurements = max - min;
}
