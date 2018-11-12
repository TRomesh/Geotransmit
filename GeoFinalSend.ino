#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <SPI.h>
#include "RF24.h"

int rc = 3;
int op = 5;
float lattitude,longitude; // create variable for latitude and longitude object 
SoftwareSerial gpsSerial(0,1);//rx,tx
TinyGPSPlus gps;// create gps object
RF24 myRadio(7, 8);
byte addresses[][6] = {"0"};

struct package
{
    int id = 1;
    float longitude = 0.0;
    float latitude = 0.0;
    char text[100] = "Geographic coordinates";
};

typedef struct package Package;
Package data;

void setup() {
    pinMode(rc, INPUT);
    pinMode(op,OUTPUT);
    Serial.begin(115200);
    gpsSerial.begin(115200); // connect gps sensor
    delay(1000);
    myRadio.begin();
    myRadio.setChannel(115);
    myRadio.setPALevel(RF24_PA_MAX);
    myRadio.setDataRate(RF24_250KBPS);
    myRadio.openWritingPipe(addresses[0]);
    delay(1000);
}

void loop() {

  int rc4 = pulseIn(rc, HIGH, 25000);
  int gpsa = gpsSerial.available();


    while(1)
        {
         while (gpsa > 0)
         { gps.encode(gpsSerial.read()); }

            if (gps.location.isUpdated())
            {
                Serial.print("LAT=");  Serial.println(gps.location.lat(), 6);
                Serial.print("LONG="); Serial.println(gps.location.lng(), 6);
                lattitude=gps.location.lat();
                longitude=gps.location.lng();
                data.id = data.id + 1;
                data.longitude = gps.location.lng();
                data.latitude = gps.location.lat();
                 if(rc4==0){
                        Serial.println(" No Motor Signal");
                    }
                    else if(rc4 > 1530){ 
                        Serial.println("Motor ON!");
                        digitalWrite(op, HIGH);
                        myRadio.write(&data, sizeof(data));
                    }
                    else if(rc4 < 1460){
                        Serial.println("Motor OFF!");
                        digitalWrite(op, LOW);
                    }else{
                        Serial.println("Something");
                    }
                Serial.print("LATTITUDE="); Serial.println(lattitude,6);
                Serial.print("LONGITUDE="); Serial.println(longitude,6);
                delay(1000);
                break;
            }
        }
}