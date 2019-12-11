#ifndef AIRTEMPANDSENSORHUMIDITY_H
#define AIRTEMPANDSENSORHUMIDITY_H

#include "Adafruit_DHT_Particle.h"
#include "calibrations.h"
#include "temperatures.h"

#define DHTPIN D2
#define DHTTYPE DHT11

class AirtempAndHumiditySensor {

public:
  AirtempAndHumiditySensor(struct temperatures *, struct calibrations *);
  void setup();
  void begin();

  void readCelsiusFromSensor();
  void readHumidityFromSensor();

private:
  temperatures *m_ptr_temperatures;
  calibrations *m_ptr_calibrations;
};

#endif