#ifndef WATERTEMPSENSOR_H
#define WATERTEMPSENSOR_H
#include "temperatures.h"
#include "calibrations.h"

class WaterTempSensor {
 public:
  WaterTempSensor(struct temperatures *, struct calibrations *);
  void setup();
  void begin();

  void readCelsiusTempFromSensor();

 private:
  temperatures* m_ptr_temperatures;
  calibrations* m_ptr_calibrations;
};

#endif