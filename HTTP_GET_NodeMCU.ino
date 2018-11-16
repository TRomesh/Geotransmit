#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
 
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
 
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://35.239.8.77:4000/getgeo");      //Specify request destination

 
   int httpCode = http.GET();   //Send the request
   if(httpCode>0){
       String payload = http.getString();                  //Get the response payload
       Serial.println(payload);    //Print request response payload
   }

   http.end();  //Close connection
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }


 
  delay(2000);  //Send a request every 30 seconds
 
}