#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
 
void setup() {
 
  Serial.begin(115200);                              
  WiFi.begin("iPhone (2)", "whatevet");   //WiFi connection 
  while (WiFi.status() != WL_CONNECTED) {  //Waiting for the connection
    delay(500);
    Serial.println("Waiting for connection");

 
  }
 
}
 
void loop() {
    String userID = "0";
  String catID = "64663456";
  String locID = "Catflap"; // specific cat locatoin
  String location = "Indoors"; // generic cat location
 
 if(WiFi.status()== WL_CONNECTED){   //Checking connection
 
   HTTPClient http;    //Declare object of class HTTPClient
 
   http.begin("http://ptsv2.com/t/ns5l9-1535102937/post");      //Specify request destination
   http.addHeader("Content-Type", "text/json");  //Specify content-type header
 
   int httpCode = http.POST("[setLoc = {""userID:"+ userID+",  CatID:"+ catID+",  location:"+ location+",  locID:"+ locID +"}");   //Send the request
   String payload = http.getString();                  //Get the response payload
 
   Serial.println(httpCode);   //Print HTTP return code
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 }else{
 
    Serial.println("Error in WiFi connection");   
 
 }
 
  delay(30000);  //Send a request every 30 seconds
}  
