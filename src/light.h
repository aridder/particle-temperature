#ifndef LIGHT_H
#define LIGHT_H
#include "temperatures.h"
#include "calibrations.h"

class Light
{
    
    public:
        Light(struct temperatures *, struct calibrations *);
        void setup();
        void begin();

        void setRedLight();

      
    private:
        int redLightStatus;
        bool newSetLightBool;
        bool lastSetLightBool;
        temperatures *m_ptr_temperatures;
        calibrations *m_ptr_calibrations;

};

#endif