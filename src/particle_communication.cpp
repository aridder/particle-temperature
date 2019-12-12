
#include "particle_communication.h"

ParticleCommunication::ParticleCommunication(struct temperatures *ptr_temperaure, struct acceleration_measurements *ptr_acceleration_measurements, struct calibrations *ptr_calibrations) {
  m_ptr_temperatures              = ptr_temperaure;
  m_ptr_acceleration_measurements = ptr_acceleration_measurements;
  m_ptr_calibrations              = ptr_calibrations;
}

void ParticleCommunication::begin() {
  Particle.publishVitals(20);

  Particle.variable("waterTemp", m_ptr_temperatures->currentWaterTemp);
  Particle.variable("airTemp", m_ptr_temperatures->currentOnLandTemperature);
  Particle.variable("airHumidity", m_ptr_temperatures->currentOnLandHumidity);
  Particle.variable("waterTemp", m_ptr_temperatures->currentWaterTemp);

  Particle.variable("waterTempCalibrationValue", m_ptr_calibrations->waterTempCalibration);
  Particle.variable("airTempCalibrationValue", m_ptr_calibrations->airTempCalibration);
  Particle.variable("airHumidityCalibration", m_ptr_calibrations->landHumidityCalibration);

  Particle.function("calibrateWaterTempFunction", &ParticleCommunication::calibrateWaterTemp, this);
  Particle.function("calibrateAirTempFunction", &ParticleCommunication::calibrateAirTemp, this);
  Particle.function("calibrateAirHumidityFunction", &ParticleCommunication::calibrateAirHumidty, this);

  Particle.function("setTimeZone", &ParticleCommunication::setTimeZone, this);

  Particle.function("setLightOnLimit", &ParticleCommunication::setLightOnLimit, this);
}

void ParticleCommunication::publishData(){

  String data = String::format(
    "{\"gyrometer\": {\"ax\":%d, \"ay\":%d, \"az\":%d, \"maxDiffZAxisLast10Measurements\":%d}, \"temperatures\": {\"water\": %f, \"air\":%f, \"humidity\":%f } }",
    m_ptr_acceleration_measurements->ax,
    m_ptr_acceleration_measurements->ay,
    m_ptr_acceleration_measurements->az,
    m_ptr_acceleration_measurements->diff_in_z_axis_last_ten_measurements,
    m_ptr_temperatures->currentWaterTemp,
    m_ptr_temperatures->currentOnLandTemperature,
    m_ptr_temperatures->currentOnLandHumidity  
  );

  Particle.publish("sensorData", data);
}

int ParticleCommunication::calibrateWaterTemp(String body) {
  float val = body.toFloat();
  m_ptr_calibrations->waterTempCalibration += val;
  return 1;
}

int ParticleCommunication::calibrateAirTemp(String body) {
  float val = body.toFloat();
  m_ptr_calibrations->airTempCalibration += val;
  return 1;
}

int ParticleCommunication::calibrateAirHumidty(String body) {
  float val = body.toFloat();
  m_ptr_calibrations->landHumidityCalibration += val;
  return 1;
}

int ParticleCommunication::setTimeZone(String body) {
  int val = body.toInt();
  Time.zone(val);
  return 1;
}

int ParticleCommunication::setLightOnLimit(String body) {
  float val = body.toFloat();
  m_ptr_calibrations->lightOnLimit = val;
  return 1;
}
