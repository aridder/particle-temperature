#ifndef LIGHT_H
#define LIGHT_H
#include "temperatures.h"

class Light
{
    
    public:
        Light(struct temperatures *);
        void setup();
        void begin();

        void setRedLight();

      
    private:
        int redLightStatus;
        bool newSetLightBool;
        bool lastSetLightBool;
        temperatures *m_ptr_temperatures;

};

#endif