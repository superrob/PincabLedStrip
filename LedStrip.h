#ifndef LedStrip_h
#define LedStrip_h

#include <Arduino.h>

#ifndef DEBUG_ON_WIFI
#define FASTLED_ALLOW_INTERRUPTS 0
#endif

#include <FastLED.h>
FASTLED_USING_NAMESPACE

/*************   END VALUE TO CHANGE  *******************/

class LedStrip {
public:
  LedStrip(uint32_t numPerStrip);
  void begin(void);

  void reset();
  void addNewStrip(uint8_t index, uint16_t length);
  void setStripLength(uint16_t length);
  void setStripBrightness(uint8_t index, uint8_t brightness);
  void clearAll();
  void setPixels(uint32_t start_num, uint16_t len, int color);
  void setPixel(uint32_t num, int color);
  void setPixel(uint32_t num, uint8_t red, uint8_t green, uint8_t blue) {
    setPixel(num, color(red, green, blue));
  }
  CRGB& getPixel(uint32_t num);

  void show(void);
  int busy(void);

  int numPixels(void) {
    return stripTotalLen * 8;
  }
  int color(uint8_t red, uint8_t green, uint8_t blue) {
    return (red << 16) | (green << 8) | blue;
  }


private:
  static uint16_t stripTotalLen;
  static uint16_t stripLen[NUMBER_LEDSTRIP];
  static uint16_t stripStartOffset[NUMBER_LEDSTRIP];
  static uint8_t stripIndex[NUMBER_LEDSTRIP * MaxLedsPerStrip];
};

#endif
