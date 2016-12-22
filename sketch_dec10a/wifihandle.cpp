
#include <Arduino.h>
#include <IPAddress.h>
#include "ESP8266WiFi.h"

class ecgwifi {
    public:
    WiFiClient clienta;
    WiFiServer *server;
    ecgwifi()
    {}
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

    void startserver()
    {
        server =  new WiFiServer(80);
        server->begin();
        
    }
    void serve(String resp)
    {
          if (!clienta | !clienta.connected() ) {
            clienta = server->available();
            if (!clienta) 
              return;
            //clienta.setNoDelay(1);
          }
          clienta.flush();
          clienta.print(resp);
    }
    void flush()
    {
        if (clienta | clienta.connected() ) 
        {
          clienta.flush();
        }
    }
    
};
