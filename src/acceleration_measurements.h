#ifndef ACCELERATION_MEASUREMENTS_H
#define ACCELERATION_MEASUREMENTS_H

struct acceleration_measurements {
  int ax;
  int ay;
  int az;
  int number_of_wave_measurments;
  int diff_in_z_axis_last_ten_measurements;
};

#endif