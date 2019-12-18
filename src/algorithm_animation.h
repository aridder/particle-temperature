#ifndef ALGORITHM_ANIMATION_H
#define ALGORITHM_ANIMATION_H
#include "Adafruit_ST7735.h"
#include "Particle.h"
#include "application.h"

class AlgorithmAnimation {
  int *   numbersToSort;
  uint8_t m_size;

public:
  AlgorithmAnimation(Adafruit_ST7735 *adafruit, uint8_t size);
  void begin();

private:
  Adafruit_ST7735 *m_ptr_adafruit;
  void             getRandomNumbersToSort();
  void             quickSort();
  void             drawNumbers(int curr, int keyIndex);
};

#endif