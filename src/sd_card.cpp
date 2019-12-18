#include "sd_card.h"
#include "application.h"
#include <string>

#define LOCK() SINGLE_THREADED_SECTION()
#define UNLOCK()

#define SD_CS_PIN D4
#define SPI_SPEED SD_SCK_MHZ(4)

using namespace std;

SDCard::SDCard(struct calibrations *ptr_calibrations) {
  m_ptr_calibrations = ptr_calibrations;
  SD                 = new SdFat();
}

void SDCard::begin() {
  if (!SD->begin(SD_CS_PIN, SPI_SPEED)) {
    Serial.println("Error code");
    Serial.println(SD->card()->errorCode());
    Serial.println(SD->card()->errorData());
    m_ptr_calibrations->waterTempCalibration    = 0.00;
    m_ptr_calibrations->airTempCalibration      = 0.00;
    m_ptr_calibrations->landHumidityCalibration = 0.00;
    m_ptr_calibrations->time                    = 0;
    m_ptr_calibrations->lightOnLimit            = 24.00;
    return;
  } else {
  }

  Serial.println("-------------------------");
  Serial.println("Serial SDCard is ready");
  Serial.println("-------------------------");
  openFileToReadAndRead();
}

void SDCard::openFileToReadAndRead() {
  char   line[30];
  int    n;
  string key;
  string value;
  SdFile calibrationsFile("calibrations-file.txt", O_RDONLY);

  if (!calibrationsFile.isOpen()) {
    Serial.println("Couldnt open file");
    return;
  }

  Serial.println("Reading from sd:");

  while ((n = calibrationsFile.fgets(line, sizeof(line))) > 0) {
    if (line[n - 1] == '\n') {
      string s          = string(line);
      int    delimitter = s.find('=');
      int    end        = s.find('\n');
      key               = s.substr(0, delimitter);
      value             = s.substr(delimitter + 1, end);

      if (key == "AIR") {
        m_ptr_calibrations->airTempCalibration = ::atof(value.c_str());
      } else if (key == "WATER") {
        m_ptr_calibrations->waterTempCalibration = ::atof(value.c_str());
      } else if (key == "HUMIDITY") {
        m_ptr_calibrations->landHumidityCalibration = ::atof(value.c_str());
      } else if (key == "TIME") {
        m_ptr_calibrations->time = ::atoi(value.c_str());
      } else if (key == "LIGHTLIMIT") {
        m_ptr_calibrations->lightOnLimit = ::atof(value.c_str());
      }
    } else {
    }
  }
}

void SDCard::openFileToWriteAndWrite() {
  //calibrationsFile = SD->open("calibration-file.txt", FILE_WRITE);
  SD->remove("calibrations-file.txt");

  SdFile wrfile("calibrations-file.txt", O_WRONLY | O_CREAT | O_TRUNC);

  if (!wrfile.isOpen()) {
    Serial.println("Cannot open file to write");
    return;
  }

  String toWrite = String::format("AIR=%0.2f\nWATER=%0.2f\nHUMIDITY=%0.2f\nTIME=%d\nLIGHTLIMIT=%0.2f\n",
                                  m_ptr_calibrations->airTempCalibration,
                                  m_ptr_calibrations->waterTempCalibration,
                                  m_ptr_calibrations->landHumidityCalibration,
                                  m_ptr_calibrations->time,
                                  m_ptr_calibrations->lightOnLimit);

  Serial.println(toWrite.c_str());

  wrfile.print(toWrite);
  wrfile.close();
}
