#ifndef WATERTEMPSENSOR_H
#define WATERTEMPSENSOR_H
#include "temperatures.h"

class WaterTempSensor {
 public:
  WaterTempSensor(struct temperatures *);
  void setup();
  void begin();

  void readCelsiusTempFromSensor();

 private:
  temperatures* m_ptr_temperatures;
};

#endif