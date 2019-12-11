#include "light.h"
#include "application.h"

#define RED_LIGHT_OUTPUT D6

Light::Light(struct temperatures *ptr_temperatures, struct calibrations *ptr_calibration) {
  m_ptr_temperatures = ptr_temperatures;
  m_ptr_calibrations = ptr_calibration;
  setup();
}

void Light::begin() {
  delay(50);
  Serial.println("-------------------------");
  Serial.println("Light is ready");
  Serial.println("-------------------------");
}

void Light::setup() {
  pinMode(RED_LIGHT_OUTPUT, OUTPUT);
  redLightStatus = LOW;
}

void Light::setRedLight() {
  if ((m_ptr_temperatures->currentWaterTemp) > m_ptr_calibrations->lightOnLimit) {
    newSetLightBool = true;
  } else {
    newSetLightBool = false;
  }

  if (newSetLightBool != lastSetLightBool) {
    digitalWrite(RED_LIGHT_OUTPUT, newSetLightBool);
  }

  lastSetLightBool = newSetLightBool;
}
