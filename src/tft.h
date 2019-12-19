

#ifndef TFT_H
#define TFT_H

#include "Adafruit_ST7735.h"
#include "temperatures.h"
#include "acceleration_measurements.h"
#include "calibrations.h"


class TFT
{
    
    public:

        TFT(struct temperatures *, struct acceleration_measurements *, struct calibrations *);
        void setup();
        void begin();

        void drawTime();
        void drawTempAndHumidity();
        void drawAcc();
        void drawWaveIndicationColor();
        void clearScreen();

    
    private:
        Adafruit_ST7735* adafruit;
        temperatures *m_ptr_temperatures;
        acceleration_measurements *m_ptr_acceleration_measurements;
        calibrations *m_ptr_calibration;
        char buffer [7];

};

#endif