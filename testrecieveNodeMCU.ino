#include <SPI.h>
#include "RF24.h"
#include <ESP8266WiFi.h>

RF24 myRadio(D7, D8);
const char* ssid = "Nokia6";
const char* password = "tromesh31";
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
    Serial.begin(9600);
    myRadio.begin();
    myRadio.setChannel(115);
    myRadio.setPALevel(RF24_PA_MAX);
    myRadio.setDataRate(RF24_250KBPS);
    myRadio.openReadingPipe(1, addresses[0]);
    myRadio.startListening();
    
    WiFi.begin(ssid, password);
    Serial.println();
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
     delay(500);
     Serial.print(".");
    }
    Serial.println("success!");
    Serial.print("IP Address is: ");
    Serial.println(WiFi.localIP());
    delay(1000);
}

void loop()
{

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
    Serial.print("Package :");
    Serial.print(myRadio.available());
    Serial.println(WiFi.localIP());
}