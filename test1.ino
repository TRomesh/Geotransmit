#include <TinyGPS++.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include "RF24.h"

RF24 myRadio(4, 5);
byte addresses[][6] = {"0"};

struct package
{
    int id = 1;
    float altitude = 0.0;
    float longitude = 0.0;
    float latitude = 0.0;
    float nsatelites = 0.0;
    char text[100] = "";
};

typedef struct package Package;
Package data;

float lattitude,longitude; // create variable for latitude and longitude object 
SoftwareSerial gpsSerial(8,9);//rx,tx
TinyGPSPlus gps;// create gps object
void setup(){
Serial.begin(9600); // connect serial
gpsSerial.begin(9600); // connect gps sensor
    delay(1000);
    myRadio.begin();
    myRadio.setChannel(115);
    myRadio.setPALevel(RF24_PA_MAX);
    myRadio.setDataRate(RF24_250KBPS);
    myRadio.openWritingPipe(addresses[0]);
    delay(1000);

};
void loop(){
  
  while(true)
  {
   while (gpsSerial.available() > 0){ gps.encode(gpsSerial.read()); }

      if (gps.location.isUpdated())
      {
       lattitude=gps.location.lat();
       longitude=gps.location.lng();
       Serial.print("LATTITUDE="); Serial.println(lattitude,6);
       Serial.print("LONGITUDE="); Serial.println(longitude,6);
      }
   }
      delay(1000);
};