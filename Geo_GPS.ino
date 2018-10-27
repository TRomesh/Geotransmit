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

void setup()
{
    Serial.begin(SERIAL_BAUD);
    ss.begin(GPS_BAUD);
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
            gpsArray[0] = M8_Gps.altitude;
            gpsArray[1] = M8_Gps.latitude;
            gpsArray[2] = M8_Gps.longitude;
            gpsArray[3] = M8_Gps.sats_in_use;
        }
    }
    for (byte i = 0; i < N_FLOATS; i++)
    {
        Serial.print(gpsArray[i], 6);
        Serial.print(" ");
    }
    Serial.println("");
}