#define debugecg 1
#include "ECG.cpp"
#include <SPI.h>

#include "wifihandle.cpp"

char* ssid     = "akscube :)";
char* password = "IPpower@1234";\


    
ecg ecghandle;
ecgwifi wifi;

void dataready()
{
  ecghandle.acquire_data();
}

void setup() 
{
  wifi.connect(ssid,password);
  attachInterrupt(digitalPinToInterrupt(ADS1292_DRDY_PIN), dataready, FALLING);   
}

void loop() 
{
  Serial.print(ecghandle.send_data());
} 

    
