#ifndef PARTICLE_COMMUNICATION_H
#define PARTICLE_COMMUNICATION_H
#include "acceleration_measurements.h"
#include "calibrations.h"
#include "sd_card.h"
#include "temperatures.h"
#include "Particle.h"

class ParticleCommunication {

public:
  ParticleCommunication(struct temperatures *, struct acceleration_measurements *, struct calibrations *, SDCard *sdCard);
  int calibrateWaterTemp(String body);
  int calibrateAirTemp(String body);
  int calibrateAirHumidty(String body);
  int setTimeZone(String body);
  int setLightOnLimit(String body);

  void publishData();
  void begin();

private:
  temperatures *             m_ptr_temperatures;
  acceleration_measurements *m_ptr_acceleration_measurements;
  calibrations *             m_ptr_calibrations;
  SDCard *                   m_ptr_sdcard;
};

#endif