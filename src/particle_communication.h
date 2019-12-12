#ifndef PARTICLE_COMMUNICATION_H
#define PARTICLE_COMMUNICATION_H
#include "Particle.h"
#include "acceleration_measurements.h"
#include "calibrations.h"
#include "temperatures.h"

class ParticleCommunication {

public:
  ParticleCommunication(struct temperatures *, struct acceleration_measurements *, struct calibrations *);
  int  calibrateWaterTemp(String body);
  int  calibrateAirTemp(String body);
  int  calibrateAirHumidty(String body);
  int  setTimeZone(String body);
  int  setLightOnLimit(String body);
  
  void publishData();
  void begin();

private:
  temperatures *             m_ptr_temperatures;
  acceleration_measurements *m_ptr_acceleration_measurements;
  calibrations *             m_ptr_calibrations;
};

#endif