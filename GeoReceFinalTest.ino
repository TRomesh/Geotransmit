#include <SPI.h>
#include <ESP8266WiFi.h>
#include "RF24.h"

const char* ssid     = "BELL4G-08BA";
const char* password = "JTYGGLADY7F";     
int wifiStatus;

RF24 myRadio(7, 8);
struct package
{
    int id = 0;
    float longitude = 0.0;
    float latitude = 0.0;
    char text[100] = "empty";
};

byte addresses[][6] = {"0"};
typedef struct package Package;
Package data;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    myRadio.begin();
    myRadio.setChannel(115);
    myRadio.setPALevel(RF24_PA_MAX);
    myRadio.setDataRate(RF24_250KBPS);
    myRadio.openReadingPipe(1, addresses[0]);
    myRadio.startListening();

      Serial.print("Your are connecting to;");
      Serial.println(ssid);
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
      }
}

void loop()
{
      wifiStatus = WiFi.status();

      if(wifiStatus == WL_CONNECTED){
         Serial.println("");
         Serial.println("Your ESP is connected!");  
         Serial.println("Your IP address is: ");
         Serial.println(WiFi.localIP());  
             if (myRadio.available())
                {
                    while (myRadio.available())
                    {
                        myRadio.read(&data, sizeof(data));
                    }
                    Serial.print("\nPackage:");
                    Serial.print(data.id);
                    Serial.print("\n");
                    Serial.println(data.longitude);
                    Serial.println(data.latitude);
                    Serial.println(data.text);
                }
      }
      else{
        Serial.println("");
        Serial.println("WiFi not connected");
      }
      
}