#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "Credentials.h"

extern byte led;

//MQTT
String CLientID = "ESP32";
const char *mqtt_server = "192.168.0.225";
const char *mqtt_user = "";
const char *mqtt_password = "";
WiFiClient espCLient;
PubSubClient client(espCLient);

void reconnect()
{
      while (!client.connected()) {
        Serial.println("Attempting MQTT connection...");
        CLientID += String(random(0xffff),HEX);
        if (client.connect(CLientID.c_str(),mqtt_user,mqtt_password)){
            Serial.println("Connected");
            //client.subscribe("fromNodeRed");
            //client.subscribe("ledState");
            //client.subscribe("JSONfromNodeRED");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
      }
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.print(" .message:  ");

  String messageTemp;      //Decleared a String
  
  for (int i=0;i<length;i++) {
    //Serial.print((char)payload[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  /*if(String(topic) == "fromNodeRed"){
    Serial.println(messageTemp);
  }

  else if(String(topic) == "ledState"){
    if(messageTemp == "on"){
      digitalWrite(led,HIGH);
    }
    else if(messageTemp == "off"){
      digitalWrite(led, LOW);
  }
  }
  if (String(topic) == "JSONfromNodeRED"){
    // Stream& input;

    JsonDocument doc;

    DeserializationError error = deserializeJson(doc, messageTemp);

    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.c_str());
      return;
    }

    const char* device = doc["device"]; // "DO IT ESP32 DEV KIT V1"
    int temperature = doc["temperature"]; // 33
    int humidity = doc["humidity"]; // 90
    int lux = doc["lux"]; // 643

    float data_0 = doc["data"][0]; // 48.75608
    float data_1 = doc["data"][1]; // 2.302038

    String output = String(device)+"\ntmeperature:"+String(temperature)+"  \nhumidity :"+String(humidity)+"\nlux"+String(lux)+" "+String(data_0)+" "+String(data_1);
    Serial.println(output);

  }  */

  if(String(topic) == "topic"){
    //  action
  }
}

void connectAP()
{
    Serial.println("Connect to my WiFI");
    //WiFi.mode(WIFI_AP_STA);
    WiFi.begin(ssid,password);

    byte count=0;

    while ((WiFi.status()!=WL_CONNECTED))
    {
        /* code */
        delay(1000);
        Serial.println("Trying to connect to WiFI");
        count++;

        if(count >=30){
            //ESP.restart();
            Serial.println("Wifi connection failed");
            break;
                  }

    }
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi connected!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    }
    
}