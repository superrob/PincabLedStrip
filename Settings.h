/*************   CHOOSE TYPE OF LED STRIP  *******************/

//#define LED_TYPE    WS2811
//#define LED_TYPE    WS2812
#define LED_TYPE WS2812B
//#define LED_TYPE    WS2813

/*************   CHOOSE COLOR ORDER OF LED STRIP  *******************/

//#define COLOR_ORDER RGB
#define COLOR_ORDER GRB

/*************   FIRMWARE SETTINGS  *******************/

enum SettingsEnum {
  TEST_ON_RESET,
  TEST_SWITCH,
  ACTIVITY_LED,
  COUNT
};

#define ENABLE_TEST_ON_RESET 0
#define ENABLE_TEST_SWITCH 0
#define ENABLE_ACTIVITY_LED 0

#define SERIAL_BUFFER_SIZE 2048
#define HALF_BRIGHTNESS 128  // Defines Brightness in RGB boot sequence - 16 its the minimum (1-15 strip don't iluminate at all)
#define FULL_BRIGHTNESS 255  // Defines Brightness in pin 1 (0 to 255)
#define NUMBER_LEDSTRIP 8

#define FirmwareVersionMajor 2
#define FirmwareVersionMinor 2

/*************   MICROCONTROLLER SPECIFIC SETTINGS  *******************/

#if defined(ESP8266)
    // ESP8266, such as Wemos D1 mini
    #define READ_EEPROM_SETTINGS 1
    #define MaxLedsPerStrip 1200
    //Ports in configtool vs ports in wemos
    //Configtool   =====   Wemos
    //1            =====   D5
    //4            =====   D6
    //7            =====   D7
    //10           =====   D8
    //13           =====   D1
    //16           =====   D4
    //19           =====   D2
    //22           =====   D3
    #define DATA_PIN1 D5
    #define DATA_PIN2 D6
    #define DATA_PIN3 D7
    #define DATA_PIN4 D8
    #define DATA_PIN5 D1
    #define DATA_PIN6 D4
    #define DATA_PIN7 D2
    #define DATA_PIN8 D3
    #define TestPin D0
    #define LedPin LED_BUILTIN

#elif defined(ESP32)
    // ESP32, such as Wemos S2 mini
    #define READ_EEPROM_SETTINGS 1
    #define MaxLedsPerStrip 1200

    #define DATA_PIN1 7
    #define DATA_PIN2 9
    #define DATA_PIN3 11
    #define DATA_PIN4 12
    #define DATA_PIN5 35
    #define DATA_PIN6 16
    #define DATA_PIN7 33
    #define DATA_PIN8 18
    #define TestPin 5
    #define LedPin 15

#elif defined(ARDUINO_ARCH_RP2040)
    // Pi Pico
    #define READ_EEPROM_SETTINGS 0
    #define MaxLedsPerStrip 1200

    #define DATA_PIN1 0
    #define DATA_PIN2 1
    #define DATA_PIN3 2
    #define DATA_PIN4 3
    #define DATA_PIN5 4
    #define DATA_PIN6 5
    #define DATA_PIN7 6
    #define DATA_PIN8 7
    #define TestPin 15
    #define LedPin 25

#elif (defined(__MK20DX128__) || defined(__MK20DX256__) || defined(__MK64FX512__) || defined(__MK66FX1M0__) || defined(__MKL26Z64__) || defined (__IMXRT1062__))
    // Teensy
    #define READ_EEPROM_SETTINGS 0
    #define MaxLedsPerStrip 1200

    #define DATA_PIN1 2
    #define DATA_PIN2 14
    #define DATA_PIN3 7
    #define DATA_PIN4 8
    #define DATA_PIN5 6
    #define DATA_PIN6 20
    #define DATA_PIN7 21
    #define DATA_PIN8 5
    #define TestPin 17
    #define LedPin 16

#else

    #error "Unsupported Microcontroller"

#endif