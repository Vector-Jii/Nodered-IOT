#include <Arduino.h>
#include <ArduinoJson.h>
#include "wifimqtt.h"


//millis() : returns the number of milliseconds elapsed since the board started running its current program
unsigned long previousMillis = millis();

void setup(){
    Serial.begin(115200);

    connectAP();                          // Connect to WIFI 
    client.setServer(mqtt_server,1883);   //class configures the MQTT server by specifying its domain and port
    client.setCallback(callback);         //allows users to set a callback function that will be invoked when a message is received
}

void loop(){
    // put your main code here, to run repeatedly:
  if(!client.connected()){
    reconnect();
  }

  if(client.loop()){
    //client.connect("ESP32-");
    client.connect("ESP32weather");
  }

   unsigned long currentmillis = millis();

   if (currentmillis - previousMillis >= 5000){

    previousMillis = currentmillis;
    Serial.println("blink");
   }
}