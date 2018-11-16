#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <SPI.h>
#include "RF24.h"

int in1 = 12;
float lattitude,longitude; // create variable for latitude and longitude object 
SoftwareSerial gpsSerial(8,9);//rx,tx
TinyGPSPlus gps;// create gps object
RF24 myRadio(7, 8);
byte addresses[][6] = {"0"};
//the following are all ~PWM capable ports 
int enable1 = 11;
int rc_channel4 = 3;

struct package
{
    int id = 1;
    float longitude = 0.0;
    float latitude = 0.0;
    char text[100] = "";
};

typedef struct package Package;
Package data;

void setup() {
  pinMode(rc_channel4, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(enable1, OUTPUT);

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

void gps(){
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
}

void loop() {
  
  int pwm = 0;

  int rc4 = pulseIn(rc_channel4, HIGH, 25000);
 
  Serial.print(" raw channel4: ");
  Serial.print(rc4);

  if(rc4 > 1070){
      gps();
  }
  
  if(rc4<1070){
      Serial.println(" no signal");
      digitalWrite(in1, LOW);
      
      analogWrite(enable1, 0);
  }
  else if(rc4 > 1070){ //right stick
      pwm = map(rc4, 1070, 2000, 0, 255); //map our speed to 0-255 range
      digitalWrite(in1, LOW);
      analogWrite(enable1, pwm);
      Serial.print(" mptor speed: ");
      Serial.println(pwm);
  }
  else if(rc4 > 1180){
      pwm = map(rc4, 1350, 2000, 0, 255); //map our speed to 0-255 range
      digitalWrite(in1, LOW);
      analogWrite(enable1, pwm);
      Serial.print(" motor speed: ");
      Serial.println(pwm);
  }
  else if(rc4 > 1350){
      pwm = map(rc4, 1480, 2000, 0, 255); //map our speed to 0-255 range
      digitalWrite(in1, LOW);
      analogWrite(enable1, pwm);
      Serial.print(" motor speed: ");
      Serial.println(pwm);
      Serial.print("stick centered");
  }   
  else if(rc4 > 1480){
      pwm = map(rc4, 1660, 2000, 0, 255); //map our speed to 0-255 range
      digitalWrite(in1, LOW);
      analogWrite(enable1, pwm);
      Serial.print(" motor speed ");
      Serial.println(pwm);
  }

   else if(rc4 > 1660){
      pwm = map(rc4, 1805, 2000, 0, 255); //map our speed to 0-255 range
      digitalWrite(in1, LOW);
      analogWrite(enable1, pwm);
      Serial.print(" motor speed ");
      Serial.println(pwm);
  }
   else if(rc4 > 1805){
      pwm = map(rc4, 1920, 2000, 0, 255); //map our speed to 0-255 range
      digitalWrite(in1, HIGH);
      analogWrite(enable1, pwm);
      Serial.print(" motor speed ");
      Serial.println(pwm);
  }
  delay(10);
}