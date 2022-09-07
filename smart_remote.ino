#include <ESPAsyncWebServer.h>
#include <IRremote.hpp>
#include <Preferences.h>
#include "Codes.h"
#include "Wifi_setup.h"
#include "HTML.h"

//server object
AsyncWebServer server(80);

//preferences object
Preferences preferences;

//pin to reset wifi credentials
const int resetButton = 2;

//pin for IR LED
const int IRLED = 18;

//pins for wifi status LEDs
const int wifiConnectedLED = 32;
const int wifiDisconnectedLED = 33;

//state to determine if reset button has been pressed
int state = 0;

//time at which the reset button was pressed
unsigned long buttonTimer = 0;

void setup() {
  
  //initalize pins
  pinMode(resetButton, INPUT);
  pinMode(IRLED, OUTPUT);
  pinMode(wifiConnectedLED, OUTPUT);
  pinMode(wifiDisconnectedLED, OUTPUT);

  //wifi not connected
  digitalWrite(wifiConnectedLED, LOW);
  digitalWrite(wifiDisconnectedLED, HIGH);

  //begin serial, irsender, and preferences (for wifi credentials)
  Serial.begin(115200);
  IrSender.begin(IRLED);
  
  preferences.begin("credentials", true);
  //if there is no ssid and credentials saved, then get the credentials
  if (preferences.getString("ssid", "") == "" & preferences.getString("password", "") == "") {
    preferences.end();
    get_credentials(server, preferences, connectPage);
  }

  //otherwise connect to wifi
  else {
    preferences.end();
    wifi_connect(server, preferences, connectPage);
  }

  //wait for wifi to connect
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    if (digitalRead(resetButton) == HIGH) {
      resetWifiCredentials(preferences);
    }
  }

  //wifi connected
  digitalWrite(wifiConnectedLED, HIGH);
  digitalWrite(wifiDisconnectedLED, LOW);
  
  //store IR Codes using preferences
  get_codes(preferences);

  //route for index page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", indexPage);
  });

  //setup route to receive NEC commands at (LSB first)
  server.on("/send", HTTP_GET, [] (AsyncWebServerRequest * request) {

    //send a specific code
    if (request->hasParam("code")) {
      //get code
      String code = request->getParam("code")->value();
      
      //cast as unsigned long
      unsigned long code2 = strtoul(code.c_str(), NULL, 16);

      //print
      Serial.println("");
      Serial.print("Sent code: ");
      Serial.println(code);

      //send
      IrSender.sendNECRaw(code2, 0);

      //ok
      request->send(200, "text/plain", "OK");
    }

    //send a code from a list of codes (work in progress)
    else if (request->hasParam("type") & request->hasParam("brand") & request->hasParam("model") & request->hasParam("command")) {
      //get type, brand, model, and command
      String type = request->getParam("type")->value();
      String brand = request->getParam("brand")->value();
      String model = request->getParam("model")->value();
      String command = request->getParam("command")->value();

      //create query
      String query = type + "_" + brand + "_" + model + "_" + command;

      //retrieve code
      preferences.begin("IR_CODES", true);
      String string_hex_code = preferences.getString(query.c_str(), "Not found");
      preferences.end();

      //print
      Serial.println("");
      Serial.print("Sent: ");
      Serial.println(string_hex_code);

      //send with appropriate protocol
      //lg (using NEC)
      if (brand == "lg") {
        //cast code as unsigned long
        unsigned long hex_code = strtoul(string_hex_code.c_str(), NULL, 16);

        //send
        IrSender.sendNECRaw(hex_code, 0);

        //ok
        request->send(200, "text/plain", "OK");
      }
      //samsung
      else if (brand == "ss") {
        //get address and command
        //length of hex code string
        int len = string_hex_code.length() - 1;

        //store address and command
        char address_char [] = {string_hex_code[len - 3], string_hex_code[len - 2], string_hex_code[len - 1], string_hex_code[len], '\0'};
        char command_char [] = {string_hex_code[4], string_hex_code[5], '\0'};

        String address_string = String(address_char);
        String command_string = String(command_char);

        //convert to unsigned long int
        uint16_t address_code = strtol(address_string.c_str(), NULL, 16);
        uint8_t command_code = strtol(command_string.c_str(), NULL, 16);

        //send
        IrSender.sendSamsung(address_code, command_code, 0);

        //ok
        request->send(200, "text/plain", "OK");
      }
      else {
        //error
        request->send(404);
      }


    }
    //otherwise send an error back
    else {
      //error
      request->send(404);
    }
  });

  //begin server
  server.begin();

}

void loop() {
  //Check if wifi is still connected
  if(WiFi.status() != WL_CONNECTED){
    //wifi disconnected
    digitalWrite(wifiConnectedLED, LOW);
    digitalWrite(wifiDisconnectedLED, HIGH);
  }
  
  //if reset button is initally pressed, set buttonTimer to the current time and set the state=1 so this portion doesnt rerun
  if (digitalRead(resetButton) == HIGH && state == 0) {
    buttonTimer = millis();
    state = 1;
  }

  //if reset button is held for 5 seconds, then reset state and erase wifi credentials
  if (digitalRead(resetButton) == HIGH & ((millis() - buttonTimer) > (5 * 1000)) & state == 1) {
    state = 0;
    resetWifiCredentials(preferences);
  }

  //otherwise just reset state so user can restart this process
  else if (((millis() - buttonTimer) > (5 * 1000)) & state == 1) {
    state = 0;
  }
}
