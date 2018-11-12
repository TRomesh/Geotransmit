#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <SPI.h>
#include "RF24.h"

float lattitude,longitude; // create variable for latitude and longitude object 
SoftwareSerial gpsSerial(8,9);//rx,tx
TinyGPSPlus gps;// create gps object
RF24 myRadio(7, 8);
byte addresses[][6] = {"0"};
typedef struct package Package;
Package data;

struct package
{
    int id = 1;
    float altitude = 0.0;
    float longitude = 0.0;
    float latitude = 0.0;
    float nsatelites = 0.0;
    char text[100] = "";
};


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
}

void loop(){
  
  while(1)
  {
   while (gpsSerial.available() > 0)
   { gps.encode(gpsSerial.read()); }

      if (gps.location.isUpdated())
      {
       myRadio.write(&data, sizeof(data));
       Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
       Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
       lattitude=gps.location.lat();
       longitude=gps.location.lng();
       data.id = data.id + 1;
       data.longitude = gps.location.lng();
       data.latitude = gps.location.lat();
      break;
      }
  
}

 Serial.print("LATTITUDE="); Serial.println(lattitude,6);
 Serial.print("LONGITUDE="); Serial.println(longitude,6);
 delay(1000);


}