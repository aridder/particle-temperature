#ifndef AIRTEMPANDSENSORHUMIDITY_H
#define AIRTEMPANDSENSORHUMIDITY_H

#include "Adafruit_DHT_Particle.h"
#include "temperatures.h"
#define DHTPIN D2
#define DHTTYPE DHT11

class AirtempAndHumiditySensor
{
    
    public:
        AirtempAndHumiditySensor(struct temperatures *);
        void setup();
        void begin();

        void readCelsiusFromSensor();
        void readHumidityFromSensor();
    
    private:
        temperatures* m_ptr_temperatures;
};

#endif