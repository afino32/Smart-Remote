#include "Arduino.h"
#include <Preferences.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>

#ifndef Wifi_setup_h
#define Wifi_setup_h

void get_credentials(AsyncWebServer &server, Preferences &preferences, String &connectPage);
int wifi_connect(AsyncWebServer &server, Preferences &preferences, String &connectPage);
void resetWifiCredentials(Preferences &preferences);

#endif
