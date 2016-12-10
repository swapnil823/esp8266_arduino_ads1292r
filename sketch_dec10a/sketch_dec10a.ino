#define debugecg 1
#include "ECG.cpp"
#include <SPI.h>

#include "wifihandle.cpp"

char* ssid     = "akscube :)";
char* password = "IPpower@1234";

ecg ecghandle;
ecgwifi wifi;
bool data;
void dataready()
{
  ecghandle.acquire_data(); 
}

void setup() 
{
  wifi.connect(ssid,password);
  attachInterrupt(digitalPinToInterrupt(ADS1292_DRDY_PIN), dataready, FALLING);   
  wifi.startserver();
}

void loop() 
{
 String s=ecghandle.send_data();
 wifi.serve(s);
 Serial.print(s);
} 

    
