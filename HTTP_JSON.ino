#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

int package =11;
int longitude = 79.934703;
int lattitude=6.825258;
 
void setup() {
  
  Serial.begin(115200);                                  //Serial connection
  WiFi.begin("Nokia6", "tromesh31");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
 
    delay(500);
    Serial.println("Waiting for connection");
 
  }
 
}
 
void loop() {
 
 if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
   StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
   package = package + 1;
   longitude = longitude + 0.000001;
   lattitude = lattitude + 0.000001;
   JsonObject& JSONencoder = JSONbuffer.createObject();
   JSONencoder["package"] = package;
   JSONencoder["longitude"] = longitude;
   JSONencoder["lattitude"] = lattitude;
   Serial.println(package);
   Serial.println(longitude);
   Serial.println(lattitude);
   char JSONmessageBuffer[300];
   JSONencoder.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));

   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://35.239.8.77:4000/addgeo");      //Specify request destination
   http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
 
   //int httpCode = http.POST("{\"package\":\"1\",\"longitude\":\"111\",\"lattitude\":\"112\"}");   //Send the request
   int httpCode = http.POST(JSONmessageBuffer);   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(2000);  //Send a request every 30 seconds
 
}