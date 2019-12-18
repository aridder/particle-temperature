#include "algorithm_animation.h"

AlgorithmAnimation::AlgorithmAnimation(Adafruit_ST7735 *adafruit, uint8_t size) {
  m_ptr_adafruit = adafruit;
  m_size         = size;
  Serial.println("in constructor");
  numbersToSort = new int[m_size];
  Serial.println("in constructor after");
}

void AlgorithmAnimation::begin() {
  m_ptr_adafruit->fillScreen(ST7735_BLACK);
  Serial.println("in algo begin");
  getRandomNumbersToSort();
  quickSort();
}

void AlgorithmAnimation::quickSort() {
  int key;
  int j;

  for (int i = 1; i < m_size; i++) {
    key = numbersToSort[i];

    j = i - 1;
    
    while (j >= 0 && numbersToSort[j] > key) {
      numbersToSort[j + 1] = numbersToSort[j];
      j                    = j - 1;
      drawNumbers(j, i);
    }
    numbersToSort[j + 1] = key;
  }
  delay(200);
}

void AlgorithmAnimation::drawNumbers(int curr, int keyIndex) {
  int width  = 120 / m_size;

  m_ptr_adafruit->fillScreen(ST7735_BLACK);

  for (int i = 0; i < m_size; i++) {
    int x = 5 + i * width;
    int y = 100 - numbersToSort[i];
    int height = numbersToSort[i];
    if (i == curr) {
      m_ptr_adafruit->fillRect(x, y, width, height, ST7735_GREEN);
    }else if(i == keyIndex){
      m_ptr_adafruit->fillRect(x, y, width, height, ST7735_BLUE);
    } else {
      m_ptr_adafruit->fillRect(x, y, width, height, ST7735_MAGENTA);
    }
  }
  delay(100);
}
void AlgorithmAnimation::getRandomNumbersToSort() {
  for (int i = 0; i < m_size; i++) {
    numbersToSort[i] = 10 + (rand() % 70);
  }
}
