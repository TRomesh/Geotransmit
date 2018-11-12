#include <SPI_Class.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <ESP8266WiFi.h>
#define PIN_CE D4
#define PIN_CSN D3
RF24 radio(PIN_CE, PIN_CSN);

struct package{
  int id = 1;
  int location = 1;
  char timeStamp = "date/time"
};

typedef struct package Package;
Package data;

public int data1=data.id;
public int data2=data.location;
public char data3=data.timeStamp;

byte  address[][6] = "00001"

const char* ssid = "Jino";
const char* pass = "myinternet";

char server[] = "cdgresearch.000webhostapp.com";

WiFiClient client;

int led = 2;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid,pass);
  pinMode(led,OUTPUT);
  digitalWrite(led, HIGH);
  delay(500);
  Serial.println("Connecting to: ");
  Serial.println(ssid);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED)
  {

    delay(1000);
    Serial.print(".");
  }

  delay(300);
  digitalWrite(led, LOW);
  Serial.println();
  Serial.println("Successfully connected to the network");
  Serial.print("NodeMCU IP Address: ");
  Serial.println(WiFi.localIP());

  delay(1000);

  radio.begin();
  radio.setChannel(115);
  radio.setPALevel(RF24_PA_LOW);
  radio.openWritingPipe(address[0]);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(9000);
  sendData();
}

void sendData(){
  Serial.println("Sending Data...");
  delay(1000);
  if (client.connect(server, 80)){
    WiFi.printDiag(Serial);
    Serial.println("Connected to server");
    client.print("GET /tag2.php?");
    client.print("incoming=Id ");
    client.print(data1);
    client.print("&incoming2=Loc");
    client.print(data2);
    client.println(" HTTP/1.1");
    client.println("Host: cdgresearch.000webhostapp.com");
    client.println("Connection: close");
    client.println();
    Serial.println();

    while(client.connected()){
      while(client.available()){
        Serial.write(client.read());
       }
      }
    radio.write(&data,sizeof(data));

    Serial.print("\nPackage: ");
    Serial.println(data1);
    Serial.print("Location: ")
    Serial.println(data2)
    Serial.println(data3)
    data1+=1;
    data2+=1;
    delay(1000);

  }

  else{
    Serial.println("Failed to Connect to server...");
    }

  client.stop();
  Serial.println("Disconnected from Server");
  while(client.status()!=0){
    delay (10);
   }
  }