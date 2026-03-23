#include <string.h>
#include "Settings.h"
#include "LedStrip.h"


uint16_t LedStrip::stripTotalLen;
uint16_t LedStrip::stripLen[NUMBER_LEDSTRIP];
uint16_t LedStrip::stripStartOffset[NUMBER_LEDSTRIP];
uint8_t LedStrip::stripIndex[NUMBER_LEDSTRIP * MaxLedsPerStrip];

CRGB leds[NUMBER_LEDSTRIP][MaxLedsPerStrip];

LedStrip::LedStrip(uint32_t numPerStrip) {
  stripTotalLen = numPerStrip;
  int offset = 0;
  for (int j = 0; j < NUMBER_LEDSTRIP; j++) {
    stripStartOffset[j] = offset;
    for (int i = 0; i < stripTotalLen; i++) stripIndex[offset++] = j;
  }
}

void LedStrip::begin(void) {
  int offset = 0;
  for (int j = 0; j < NUMBER_LEDSTRIP; j++) {
    stripLen[j] = MaxLedsPerStrip;
    stripStartOffset[j] = offset;
    for (int i = 0; i < stripTotalLen; i++) stripIndex[offset++] = j;
  }
  //8 led strips, hardcoded
  CRGB FullWhite(FULL_BRIGHTNESS, FULL_BRIGHTNESS, FULL_BRIGHTNESS);
  FastLED.addLeds<LED_TYPE, DATA_PIN1, COLOR_ORDER>(leds[0], MaxLedsPerStrip).setCorrection(FullWhite);
  FastLED.addLeds<LED_TYPE, DATA_PIN2, COLOR_ORDER>(leds[1], MaxLedsPerStrip).setCorrection(FullWhite);
  FastLED.addLeds<LED_TYPE, DATA_PIN3, COLOR_ORDER>(leds[2], MaxLedsPerStrip).setCorrection(FullWhite);
  FastLED.addLeds<LED_TYPE, DATA_PIN4, COLOR_ORDER>(leds[3], MaxLedsPerStrip).setCorrection(FullWhite);
  FastLED.addLeds<LED_TYPE, DATA_PIN5, COLOR_ORDER>(leds[4], MaxLedsPerStrip).setCorrection(FullWhite);
  FastLED.addLeds<LED_TYPE, DATA_PIN6, COLOR_ORDER>(leds[5], MaxLedsPerStrip).setCorrection(FullWhite);
  FastLED.addLeds<LED_TYPE, DATA_PIN7, COLOR_ORDER>(leds[6], MaxLedsPerStrip).setCorrection(FullWhite);
  FastLED.addLeds<LED_TYPE, DATA_PIN8, COLOR_ORDER>(leds[7], MaxLedsPerStrip).setCorrection(FullWhite);

  //FastLED.setBrightness( BRIGHTNESS );
  FastLED.setDither(0);
}

void LedStrip::addNewStrip(uint8_t index, uint16_t length) {
  if ((index >= 0) && (index < NUMBER_LEDSTRIP)) {
    if (length >= MaxLedsPerStrip) length = MaxLedsPerStrip - 1;
    if (!length) length = 1;  //to confirm if really required or not
    stripLen[index] = length;
    FastLED[index].setLeds(leds[index], length);
  }
}

void LedStrip::setStripBrightness(uint8_t index, uint8_t brightness) {
  if ((index >= 0) && (index < NUMBER_LEDSTRIP)) {
    FastLED[index].setCorrection(CRGB(brightness, brightness, brightness));
  }
}

void LedStrip::show(void) {
  FastLED.show();
}

void LedStrip::setStripLength(uint16_t length) {
  stripTotalLen = length;
  int offset = 0;
  for (int j = 0; j < NUMBER_LEDSTRIP; j++) {
    stripStartOffset[j] = offset;
    for (int i = 0; i < stripTotalLen; i++) stripIndex[offset++] = j;
  }
}

void LedStrip::clearAll() {
  FastLED.clear();
}

void LedStrip::reset() {
  for (int i = 0; i < NUMBER_LEDSTRIP; i++) {
    FastLED[i].setLeds(leds[i], 0);
  }
}

void LedStrip::setPixels(uint32_t start_num, uint16_t len, int color) {
  uint32_t strip, offset;
  char r = ((color >> 16) & 0xFF);
  char g = ((color >> 8) & 0xFF);
  char b = (color & 0xFF);

  strip = stripIndex[start_num];                 //start_num / stripLen;
  offset = start_num - stripStartOffset[strip];  // % stripLen;

  if (offset + len > stripLen[strip]) return;

  for (uint16_t i = len; i; i--) {
    leds[strip][offset].b = b;
    leds[strip][offset].g = g;
    leds[strip][offset].r = r;
    offset++;
    /*if (offset==stripLen) { //should never happen
      offset=0;
      strip++;
    }*/
  }
}

void LedStrip::setPixel(uint32_t num, int color) {
  uint32_t strip, offset;

  strip = stripIndex[num];                 //start_num / stripLen;
  offset = num - stripStartOffset[strip];  // % stripLen;

  if (offset >= stripLen[strip]) return;

  leds[strip][offset].b = (color & 0xFF);          // Take just the lowest 8 bits.
  leds[strip][offset].g = ((color >> 8) & 0xFF);   // Shift the integer right 8 bits.
  leds[strip][offset].r = ((color >> 16) & 0xFF);  // Shift the integer right 8 bits.
}

CRGB blackpixel(0);

CRGB& LedStrip::getPixel(uint32_t num) {
  uint32_t strip, offset;

  strip = stripIndex[num];                 //start_num / stripLen;
  offset = num - stripStartOffset[strip];  // % stripLen;

  if (offset >= stripLen[strip]) return blackpixel;

  return leds[strip][offset];
}
