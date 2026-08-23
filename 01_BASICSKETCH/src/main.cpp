#include <Arduino.h>
#include <ArduinoJson.h>
#include "wifimqtt.h"

#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <SPI.h>

#include <BH1750.h>

byte led = LED_BUILTIN;
Adafruit_BMP085 bmp;
float temp;
float pressure;
float altitude;

BH1750 lightmeter;
float lux;

//millis() : returns the number of milliseconds elapsed since the board started running its current program
unsigned long previousMillis = millis();

void sendMQTTvalues(){   // Not called here in this program 
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

void printSensorValue(){
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("C");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println("Rh");

  Serial.print("Altitude: ");
  Serial.print(altitude);
  Serial.println("m");

  Serial.print(" Limunation: ");
  Serial.print(lux);
  Serial.println(" lux");

  Serial.println("=====================================================");
}

void sendSensorValuesMQTT(){   // This function is reference from the sendMQTTvalues function that is obtained from ArduinoJson website 
  // Stream& output;
  
  //DynamicJsonDocument doc(1024);
  JsonDocument doc;

  doc["temperature"] = temp;
  doc["pressure"] = pressure;
  doc["altitude"] = altitude;
  doc["lux"] = lux;

  char buff[256];
  serializeJson(doc, buff);

  client.publish("weatherstation",buff);

}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led, OUTPUT);

  if(!bmp.begin()){
    Serial.println(" Failed to Initialize the sensor");
    while (1)
    {
      /* code */
    }
  }

  lightmeter.begin();

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
    //client.connect("ESP32-");
    client.connect("ESP32weather");
  }

  unsigned long currentmillis = millis();

  if (currentmillis - previousMillis >= 5000){
    
    //digitalWrite(led, !digitalRead(led));
    //Serial.println("terminal statement \n");

    //sent to Node Red
    //client.publish("toNodeRed","Hello from ESP32");
    //client.subscribe("fromNodeRed",0);
    //sendMQTTvalues();

    temp = bmp.readTemperature();
    pressure = bmp.readPressure()/100.0F;
    altitude = bmp.readAltitude();

    lux = lightmeter.readLightLevel();

    previousMillis = currentmillis;
    //Serial.println("Blink");

    printSensorValue();

    sendSensorValuesMQTT();
  }
}

