
#include "particle_communication.h"

ParticleCommunication::ParticleCommunication(struct temperatures *ptr_temperaure, struct acceleration_measurements *ptr_acceleration_measurements, struct calibrations *ptr_calibrations, SDCard *ptr_sdcard) {
  m_ptr_temperatures              = ptr_temperaure;
  m_ptr_acceleration_measurements = ptr_acceleration_measurements;
  m_ptr_calibrations              = ptr_calibrations;
  m_ptr_sdcard                    = ptr_sdcard;
}

void ParticleCommunication::begin() {
  Particle.publishVitals(600);

  Particle.variable("waterTemp", m_ptr_temperatures->currentWaterTemp);
  Particle.variable("airTemp", m_ptr_temperatures->currentOnLandTemperature);
  Particle.variable("airHumidity", m_ptr_temperatures->currentOnLandHumidity);
  Particle.variable("currentTimeZone", m_ptr_calibrations->time);
  Particle.variable("waterTempLightOnLimit", m_ptr_calibrations->lightOnLimit);

  Particle.variable("waterTempCalibrationValue", m_ptr_calibrations->waterTempCalibration);
  Particle.variable("airTempCalibrationValue", m_ptr_calibrations->airTempCalibration);
  Particle.variable("airHumidityCalibration", m_ptr_calibrations->landHumidityCalibration);

  Particle.function("calWatTmpF", &ParticleCommunication::calibrateWaterTemp, this);
  Particle.function("calAirTmpF", &ParticleCommunication::calibrateAirTemp, this);
  Particle.function("calAirHumF", &ParticleCommunication::calibrateAirHumidty, this);

  Particle.function("setTimeZone", &ParticleCommunication::setTimeZone, this);

  Particle.function("setLightOnLimit", &ParticleCommunication::setLightOnLimit, this);
}

void ParticleCommunication::publishData() {

  if (Particle.connected()) {
    String data = String::format(
        "{\"gyrometer\": {\"ax\":%d, \"ay\":%d, \"az\":%d, \"maxDiffZAxisLast10Measurements\":%d}, \"temperatures\": {\"water\": %f, \"air\":%f, \"humidity\":%f } }",
        m_ptr_acceleration_measurements->ax,
        m_ptr_acceleration_measurements->ay,
        m_ptr_acceleration_measurements->az,
        m_ptr_acceleration_measurements->diff_in_z_axis_last_ten_measurements,
        m_ptr_temperatures->currentWaterTemp,
        m_ptr_temperatures->currentOnLandTemperature,
        m_ptr_temperatures->currentOnLandHumidity);
    Particle.publish("sensorData", data, PRIVATE);
  }
}

int ParticleCommunication::calibrateWaterTemp(String body) {
  float val = body.toFloat();
  if (isnan(val)) {
    return -1;
  }
  m_ptr_calibrations->waterTempCalibration = val;
  m_ptr_sdcard->openFileToWriteAndWrite();
  return 1;
}

int ParticleCommunication::calibrateAirTemp(String body) {
  float val = body.toFloat();
  if (isnan(val)) {
    return -1;
  }
  m_ptr_calibrations->airTempCalibration = val;
  m_ptr_sdcard->openFileToWriteAndWrite();
  return 1;
}

int ParticleCommunication::calibrateAirHumidty(String body) {
  float val = body.toFloat();
  if (isnan(val)) {
    return -1;
  }
  m_ptr_calibrations->landHumidityCalibration = val;
  m_ptr_sdcard->openFileToWriteAndWrite();
  return 1;
}

int ParticleCommunication::setTimeZone(String body) {
  int val = body.toInt();
 
  Time.zone(val);
  m_ptr_calibrations->time = val;
  m_ptr_sdcard->openFileToWriteAndWrite();
  return 1;
}

int ParticleCommunication::setLightOnLimit(String body) {
  float val = body.toFloat();
  if (isnan(val)) {
    return -1;
  }
  m_ptr_calibrations->lightOnLimit = val;
  Serial.println("hei");
  Serial.println(val);
  m_ptr_sdcard->openFileToWriteAndWrite();
  return 1;
}
