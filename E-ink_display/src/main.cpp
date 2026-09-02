#include <Arduino.h>
#include <ArduinoJson.h>
#include "wifimqtt.h"

#include <GxEPD2_BW.h> // including both doesn't use more code or ram
#include <GxEPD2_3C.h> // including both doesn't use more code or ram
#include <GxEPD2_7C.h> // same for all three

#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeSans9pt7b.h>


#include "eink_image.h"

//#define GxEPD2_DRIVER_CLASS GxEPD2_290c     // GDEW029Z10  128x296, UC8151 (IL0373), (WFT0290CZ10)
//GxEPD2_3C<GxEPD2_290c, GxEPD2_290c::HEIGHT> display(GxEPD2_290c(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4)); // GDEW029Z10 128x296, UC8151 (IL0373)
GxEPD2_3C<GxEPD2_290_C90c, GxEPD2_290_C90c::HEIGHT> display(GxEPD2_290_C90c(/*CS=*/ 10, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));

const char HelloWorld[] = "Hello VectorJii";

//millis() : returns the number of milliseconds elapsed since the board started running its current program
unsigned long previousMillis = millis();

void helloWorldMinimum(String eInkText)
{
  
  //display.init(115200); // default 10ms reset pulse, e.g. for bare panels with DESPI-C02
  display.init(115200, true, 2, false); // USE THIS for Waveshare boards with "clever" reset circuit, 2ms reset pulse
  // comment out next line to have no or minimal Adafruit_GFX code

 display.setRotation(1);
 display.setFullWindow();
/*display.setFont(&FreeMonoBold9pt7b);

  //helper variable 
  int16_t tbx, tby;
  uint16_t tbw, tbh;

  display.getTextBounds(eInkText,0,0,&tbx,&tby,&tbw,&tbh);

  uint16_t x =((display.width() - tbw)/2)- tbx;
  uint16_t y =((display.height() - tbh)/2)- tby;
  
  display.setFullWindow();


  display.setTextColor(GxEPD_BLACK);  */

  

  display.firstPage();
  do
  {
    //display.fillScreen(GxEPD_WHITE);
    // comment out next line to have no or minimal Adafruit_GFX code
    //display.print(HelloWorld);
    //display.print(eInkText);

    display.fillScreen(GxEPD_WHITE);
    display.drawInvertedBitmap(0,0,eink_image,740,338,GxEPD_BLACK);

    display.setFont(&FreeSans9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(55,61);
    display.print(25);

    display.setCursor(155,61);
    display.print("Raining");

    display.setCursor(38,20);
    display.print("9:00 pm");

    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(GxEPD_BLACK);
    display.setCursor(152,108);
    display.print("This is different font");
  }
  while (display.nextPage());
}

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