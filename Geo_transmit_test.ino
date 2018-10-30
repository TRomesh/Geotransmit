#include <SPI.h>
#include "RF24.h"

RF24 myRadio(7, 8);
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

void setup()
{
    Serial.begin(115200);
    delay(1000);
    myRadio.begin();
    myRadio.setChannel(115);
    myRadio.setPALevel(RF24_PA_MAX);
    myRadio.setDataRate(RF24_250KBPS);
    myRadio.openWritingPipe(addresses[0]);
    delay(1000);
}

void loop()
{
    myRadio.write(&data, sizeof(data));

    Serial.print("\nPackage:");
    Serial.print(data.id);
    Serial.print("\n");
    Serial.println(data.longitude);
    Serial.println(data.latitude);
    Serial.println(data.text);
    data.id = data.id + 1;
    data.longitude = data.longitude + 0.1;
    data.latitude = data.latitude + 0.1;
    delay(1000);
}