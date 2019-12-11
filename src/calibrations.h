#ifndef CALIBRATIONS_H
#define CALIBRATIONS_H

struct calibrations {
  double waterTempCalibration;
  double airTempCalibration;
  double landHumidityCalibration;
  int    time;
  double lightOnLimit;
};

#endif