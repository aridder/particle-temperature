#include "tft.h"
#include "Adafruit_ST7735.h"
#include "application.h"

#define TFT_CS A2
#define TFT_DC A1
#define TFT_RST A0

#define ACC_TEXT_SIZE 1
#define TEMP_TEXT_SIZE 2
#define TIME_TEXT_SIZE 1
#define STARTUP_TEXT_SIZE 2

#define Y_OFFSET_SIZE_1 48
#define Y_OFFSET_SIZE_2 32

#define LINE_HEIGHT_TEXT_SIZE_1 10
#define LINE_HEIGHT_TEXT_SIZE_2 20

TFT::TFT(struct temperatures *ptr_temperaure, struct acceleration_measurements *ptr_acceleration_measurements) {
  adafruit                        = new Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
  m_ptr_temperatures              = ptr_temperaure;
  m_ptr_acceleration_measurements = ptr_acceleration_measurements;
  setup();
}

void TFT::setup() {
  Time.zone(1);
  adafruit->initG();
  adafruit->setRotation(3);
  adafruit->invertDisplay(1);
  adafruit->fillScreen(ST7735_BLUE);
  adafruit->setTextSize(2);
  adafruit->setCursor(35, 35);
  adafruit->setTextColor(ST7735_YELLOW);
  adafruit->setTextWrap(true);
  adafruit->print("STARTING");
}

void TFT::begin() {
  delay(50);
  Serial.println("-------------------------");
  Serial.println("Serial tft is ready");
  Serial.println("-------------------------");
}

void TFT::drawTime() {
  adafruit->setTextSize(TIME_TEXT_SIZE);
  adafruit->setCursor(45, 30);
  adafruit->setTextColor(ST7735_WHITE, ST7735_BLACK);
  adafruit->setTextWrap(true);
  adafruit->print(Time.format(Time.now(), "%H:%M %Y"));
}

void TFT::clearScreen() { adafruit->fillScreen(ST7735_BLACK); }

void TFT::drawAcc() {
  adafruit->setTextSize(ACC_TEXT_SIZE);
  adafruit->setTextColor(ST7735_WHITE, ST7735_BLACK);
  adafruit->setTextWrap(true);

  const char *key;
  int         current;

  for (int i = 0; i < 3; i++) {
    switch (i) {
    case 0:
      key     = "ax:";
      current = m_ptr_acceleration_measurements->ax;
      break;
    case 1:
      key     = "ay:";
      current = m_ptr_acceleration_measurements->ay;
      break;
    case 2:
      key     = "az:";
      current = m_ptr_acceleration_measurements->az;
      break;
    default:
      key = "error";
      break;
    }
    sprintf(buffer, "%6d", current);

    adafruit->setCursor(8, Y_OFFSET_SIZE_1 + (i + 1) * LINE_HEIGHT_TEXT_SIZE_1);
    adafruit->print(key);

    adafruit->setCursor(32, Y_OFFSET_SIZE_1 + (i + 1) * LINE_HEIGHT_TEXT_SIZE_1);
    adafruit->print(buffer);
  }
}

void TFT::drawWaveIndicationColor() {
  uint16_t colorBasedOnDiffInAcc;

  adafruit->setTextSize(1);
  adafruit->setTextColor(ST7735_WHITE, ST7735_BLACK);
  adafruit->setCursor(95, 45);
  adafruit->print("Waves");

  /*
  Calm water: green indication
  Middle calm water: yellow indication
  Messy water: red indication
  */

  if (m_ptr_acceleration_measurements->diff_in_z_axis_last_ten_measurements > 5000) {
    colorBasedOnDiffInAcc = ST7735_RED;
  } else if (m_ptr_acceleration_measurements->diff_in_z_axis_last_ten_measurements > 1500) {
    colorBasedOnDiffInAcc = ST7735_YELLOW;
  } else {
    colorBasedOnDiffInAcc = ST7735_GREEN;
  }
  adafruit->fillRect(78, 60, 70, 40, colorBasedOnDiffInAcc);
}

void TFT::drawTempAndHumidity() {
  adafruit->setTextSize(TEMP_TEXT_SIZE);
  adafruit->setTextColor(ST7735_WHITE, ST7735_BLACK);
  adafruit->setTextWrap(true);

  const char *key;
  double      current;

  for (int i = 0; i < 3; i++) {
    switch (i) {
    case 0:
      key     = "Water:";
      current = m_ptr_temperatures->currentWaterTemp;
      break;
    case 1:
      key     = "Air:";
      current = m_ptr_temperatures->currentOnLandTemperature;
      break;
    case 2:
      key     = "Humid:";
      current = m_ptr_temperatures->currentOnLandHumidity;
      break;
    default:
      key = "error";
      break;
    }

    sprintf(buffer, "%0.1f", current);

    adafruit->setCursor(8, Y_OFFSET_SIZE_2 + (i + 1) * LINE_HEIGHT_TEXT_SIZE_2);
    adafruit->print(key);

    adafruit->setCursor(100, Y_OFFSET_SIZE_2 + (i + 1) * LINE_HEIGHT_TEXT_SIZE_2);
    adafruit->print(buffer);
  }
}