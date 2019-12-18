#ifndef SD_CARD_H
#define SD_CARD_H

#include <SPI.h>
#include "SdFat.h"
#include "calibrations.h"


class SDCard
{ 
    public:
        SDCard(struct calibrations *);
        void begin();

        void openFileToReadAndRead();
        void openFileToWriteAndWrite();
    
    private:
        calibrations *m_ptr_calibrations;
        SdFat *SD;
};

#endif