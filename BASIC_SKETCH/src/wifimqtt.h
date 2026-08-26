#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "credentials.h"

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
            //client.subscribe("topic");
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

  if (String(topic)== "topic"){
    //actions
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