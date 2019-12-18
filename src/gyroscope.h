#ifndef GYROSCOPE_H
#define GYROSCOPE_H
#include "MPU6050.h"
#include "acceleration_measurements.h"
#include <queue>

class Gyroscope {

public:
  Gyroscope(struct acceleration_measurements *);
  void setup();
  void begin();

  void readValuesFromSensor();
  void set_wave_color_indicatior_from_z_axis_measurements();
  void readAxAyAz();

private:
  MPU6050 *                  gyrometer;
  std::queue<int>            last_ten_z_axis_measurements_queue;
  acceleration_measurements *m_ptr_acceleration_measurements;

  void push_z_axis_value_to_queue(int az);
};

#endif