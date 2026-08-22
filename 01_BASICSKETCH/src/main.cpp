#include <Arduino.h>
#include <ArduinoJson.h>
#include "wifimqtt.h"

byte led = LED_BUILTIN;

//millis() : returns the number of milliseconds elapsed since the board started running its current program
unsigned long previousMillis = millis();

void sendMQTTvalues(){
  // Stream& output;

  JsonDocument doc;

  doc["device"] = "DO IT ESP32 DEV KIT V1";
  doc["temperature"] = 33;
  doc["humidity"] = 90;
  doc["lux"] = 643;

  JsonArray data = doc["data"].to<JsonArray>();
  data.add(48.75608);
  data.add(2.302038);

  doc.shrinkToFit();  // optional

  char buff[256];
  serializeJson(doc, buff);

  client.publish("ESPValues",buff);

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  connectAP();                          // Connect to WIFI 
  client.setServer(mqtt_server,1883);   //class configures the MQTT server by specifying its domain and port
  client.setCallback(callback);         //allows users to set a callback function that will be invoked when a message is received

}

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
    reconnect();
  }

  if(client.loop()){
    client.connect("ESP32-");
  }

  unsigned long currentmillis = millis();

  if (currentmillis - previousMillis >= 10000){
    previousMillis = currentmillis;
    //digitalWrite(led, !digitalRead(led));
    //Serial.println("terminal statement \n");

    //sent to Node Red
    //client.publish("toNodeRed","Hello from ESP32");
    //client.subscribe("fromNodeRed",0);
    sendMQTTvalues();
  }
}

