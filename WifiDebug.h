#ifndef WifiDebug_h
#define WifiDebug_h

#if defined(ESP8266)

#include <String.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>

class WifiDebug {
public:
  WifiDebug();
  void begin(void);
  void debug_send_msg(char* message);
  void debug_send_byte(byte b);
  void debug_send_int(int c);
  void debug_send_word(word w);

private:
};
#endif

#endif
