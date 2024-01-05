// Wemos D1 mini: GPS to SSD1306


#include <TinyGPS++.h> //https://github.com/mikalhart/TinyGPSPlus/blob/master/src/TinyGPS%2B%2B.h
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h> //https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_SSD1306.h> //https://github.com/adafruit/Adafruit_SSD1306

// Software Serial for GPS
int RXPin = 2; //D4
int TXPin = 16; //D0
int GPSBaud = 9600; 

TinyGPSPlus gps;
SoftwareSerial gpsSerial(RXPin, TXPin);

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  oled.clearDisplay();
  gpsSerial.begin(GPSBaud);
}

void loop(){
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
     oled.clearDisplay();
     oled.setTextSize(1);             
     oled.setTextColor(WHITE);
     oled.setCursor(0,1);      
     oled.print(F("latitude: "));
     oled.print(gps.location.lat(), 6);
     oled.setCursor(0,13);
     oled.print(F("longitude: "));
     oled.print(gps.location.lng(), 6);
     oled.setCursor(0,23);      
     oled.print(F("time: "));
     oled.setCursor(30,23);
     oled.print(gps.time.hour());
     oled.setCursor(50,23);
     oled.print(gps.time.minute());
     oled.setCursor(70,23);
     oled.print(gps.time.second());
     oled.setCursor(0,53);
     oled.setCursor(0,33);      
     oled.print(F("date: "));
     oled.setCursor(30,33);
     oled.print(gps.date.day());
     oled.setCursor(50,33);
     oled.print(gps.date.month());
     oled.setCursor(70,33);
     oled.print(gps.date.year());
     oled.setCursor(0,53);
     oled.print(F("created by JayTeramoto"));
     oled.display();
      delay(10);

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    oled.clearDisplay();
    oled.setTextSize(1);             
    oled.setTextColor(WHITE);
    oled.setCursor(0,13);      
    oled.print(F("No GPS detected"));
    oled.setCursor(0,23);      
    oled.print(F("check the cable and  restart the arduino"));
    oled.display();
    while(true);
  }
}
