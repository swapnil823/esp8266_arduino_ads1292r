
#include <Arduino.h>
#include <IPAddress.h>
#include "ESP8266WiFi.h"

class ecgwifi {
    public:
    void connect(char* ssid,char* pass) {
        delay(10);
        WiFi.begin(ssid, pass);
        while (WiFi.status() != WL_CONNECTED) {
          delay(500);
          #ifdef debugecg 
            Serial.print("connecting");
          #endif
        }
        #ifdef debugecg 
          Serial.println("");
          Serial.println("WiFi connected");  
          Serial.println("IP address: ");
          Serial.println(WiFi.localIP());
        #endif
    }
    void sta_mode()
    {
      WiFi.mode(WIFI_STA);
    }
    void disconnect()
    {
      WiFi.disconnect(); 
    }

    void scan()
    {
    }

    void server()
    {
        WiFiServer server(80);
          
    }
};
