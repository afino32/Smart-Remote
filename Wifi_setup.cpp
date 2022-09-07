#include "Wifi_setup.h"

//opens an access point (AP) and sets up a routes to allow for wifi credentials to come in
void get_credentials(AsyncWebServer &server, Preferences &preferences, String &connectPage) {
  //opens access point and prints IP
  WiFi.softAP("smart-remote", "0825");
  Serial.println(WiFi.softAPIP());

  //page to type wifi credentials on
  server.on("/", HTTP_GET, [&connectPage] (AsyncWebServerRequest * request){
    request->send(200, "text/html", connectPage);
  });

  //sets up route at /connect to receive credentials at
  server.on("/connect", HTTP_GET, [&server, &preferences] (AsyncWebServerRequest * request) {
    delay(100);
    //if ssid and password parameters are defined
    if (request->hasParam("ssid") & request->hasParam("password")) {
      //get ssid and password
      const String ssid = request->getParam("ssid")->value();
      const String password = request->getParam("password")->value();
    
      //save ssid and password
      preferences.begin("credentials", false);
      preferences.putString("ssid", ssid);
      preferences.putString("password", password);
      
      //close preferences and server
      preferences.end();
      
      //ok
      request->send(200, "text/plain", "OK");
      
      //close server and restart ESP
      server.end();
      ESP.restart();
    }
    //otherwise return a error
    else {
      request->send(404);
    }
  });
  server.begin();
}

//connect to wifi and set up routes to get commands at
int wifi_connect(AsyncWebServer &server, Preferences &preferences, String &connectPage) {
  //timer to timeout wifi connection if taking too long
  unsigned long timer = 0;

  //load wifi credentials
  preferences.begin("credentials", true);
  String ssid = preferences.getString("ssid", "");
  String password = preferences.getString("password", "");
  preferences.end();

  //connect to wifi
  WiFi.begin(ssid.c_str(), password.c_str());

  //wait for wifi to connect or to timeout
  timer = millis();
  while ((WiFi.status() != WL_CONNECTED) && ((millis()-timer) <= (30*1000))) {
    //wait for connection
    Serial.println("Waiting for connection");
    delay(1500);
  }
  
  //if timeout then ask for credentials again
  if((millis()-timer) >= (30*1000)){
    get_credentials(server, preferences, connectPage);
  }

  //print ip address once connected
  Serial.println(WiFi.localIP());

  //setup mdns so one can use smart-remote.local in their browser instead of the ip
  //Not supported on android
  if (MDNS.begin("smart-remote")) {
    Serial.println("smart-remote.local");
  }

  Serial.println("Done!");
  return 1;
}

//reset wifi credentials
void resetWifiCredentials(Preferences &preferences) {
  preferences.begin("credentials", false);
  preferences.clear();
  preferences.end();
  ESP.restart();
}
