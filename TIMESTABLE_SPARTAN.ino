#include "TIMESTABLE_SPARTAN.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>

TIMESTABLE_SPARTAN TIMESTABLE_SPARTAN;

int i = 0;

void setup() {

  Serial.begin(115200);
  Serial.println(" ");
  Serial.println("Starting_System...");

  WiFi.mode(WIFI_STA);
  WiFi.hostname("SPARTAN_TEST_TIMESTABLE");
  ESP8266WiFiMulti wifiMultiSSID;

  wifiMultiSSID.addAP("1st_Wifi_Network", "wifi_password");
  wifiMultiSSID.addAP("2nd_Wifi_Network", "wifi_password"); 
  
  if (wifiMultiSSID.run() == WL_CONNECTED)
      {

      Serial.print("Connected to ");
      Serial.println(WiFi.SSID());
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      
      if(TIMESTABLE_SPARTAN.begin()){

        Serial.println("Started_Succesfully!");

      }
   }
}

void loop() {
  
  TIMESTABLE_SPARTAN.update();  
    
    if (i == 5000){ // merely for demonstration porpuses;
        Serial.println("\n\nSystem Time:");
        Serial.println(TIMESTABLE_SPARTAN.GetRunningTime());

        Serial.println("Current Time:");
        Serial.println(TIMESTABLE_SPARTAN.GetFormatedTIME());
        
        Serial.println("Current Date:");
        Serial.println(TIMESTABLE_SPARTAN.GetFormatedDATE());
        
    i=0;
    }
  i++;
  delay (1);

}
