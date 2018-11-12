#include <SPI.h>
#include "RF24.h"
#include "Ublox.h"
#include <SoftwareSerial.h>

#define SERIAL_BAUD 9600
#define GPS_BAUD 9600
#define N_FLOATS 4

static const int RXPin = 0, TXPin = 1; // Ublox 8sm GPS module to pins 0 and 1 - D6-RX, D7-TX
static const uint32_t GPSBaud = 9600;  // Ublox GPS default Baud Rate is 9600

Ublox M8_Gps;
SoftwareSerial ss(RXPin, TXPin);

// Altitude - Latitude - Longitude - N Satellites
float gpsArray[N_FLOATS] = {0, 0, 0, 0};

RF24 myRadio(7, 8);
byte addresses[][6] = {"0"};

struct package
{
    int id = 1;
    float altitude = 0.0;
    float longitude = 0.0;
    float latitude = 0.0;
    float nsatelites = 0.0;
    char text[100] = "Geographic coordinates";
};

typedef struct package Package;
Package data;

void setup()
{
    Serial.begin(115200);
    ss.begin(GPS_BAUD);
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

    if (!ss.available())
        return;

    while (ss.available())
    {
        char c = ss.read();
        if (M8_Gps.encode(c))
        {
            data.id = data.id + 1;
            data.altitude = M8_Gps.altitude;
            data.latitude = M8_Gps.latitude;
            data.longitude = = M8_Gps.longitude;
            data.nsatelites = M8_Gps.sats_in_use;
        }
    }
    myRadio.write(&data, sizeof(data));
    Serial.print("\nPackage:");
    Serial.print(data.id);
    Serial.print("\n");
    Serial.println(data.longitude);
    Serial.println(data.latitude);
    Serial.println(data.text);
    delay(1000);
}