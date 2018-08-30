#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#define RFIDPin 8
#define ServoPin 1

SoftwareSerial SoftSerial(D2, D3);
int pos = 0;
Servo  lockleft;
    
void setup() {
  Serial.begin(9600);
  SoftSerial.begin(9600);             
  WiFi.begin("iPhone", "bobbyjim");  
  lockleft.attach(1);
  
  while (WiFi.status() != WL_CONNECTED) { 
      delay(500);
    Serial.println("Waiting for connection");
  }
 
}
 
void loop() {
  Serial.println("Loop...");
  //int ogval = 0;
  //ogval=val;
  String userID = "wxOMf0ORojPklj04diYXNayMAK42";
  //String catID = "64663456";
  String locID = "Catflap"; // specific cat locatoin
  String location = "Indoors"; // generic cat location
 
  if (SoftSerial.available() >= 13) {   //Checking connection

    byte tagID[12];
    
    
    if (SoftSerial.read() == 0x02) {
      for(int index = 0; index < sizeof(tagID); index++) {
        byte val = SoftSerial.read();
        
        //convert from ASCII value to value range from 0 to 9 and A to F
        if( val >= '0' && val <= '9')
        val = val - '0';
        else if( val >= 'A' && val <= 'F')
        val = 10 + val - 'A';
        
        tagID[index] = val;
        Serial.print(val);
        Serial.print(" ");
        
      }
    }
    else {
      Serial.println("Not 0x02.");
      lockleft.write(90);
      delay(10000);
      lockleft.write(-90);
    }
  
    HTTPClient http;    //Declare object of class HTTPClient
    
    http.begin("https://us-central1-te-cattrack.cloudfunctions.net/newLoc");      //Specify request destination
    http.addHeader("Content-Type", "text/json");  //Specify content-type header
    
  
    int httpCode = http.POST(
      "[setLoc = {\"userID:\"" + String(userID) +
      ",\"CatID\":" + String((const char*) "Zm024m93b9LMxH8UhFGe") +
      ",\"location\":" + String(location) +
      ",\"locID\":" + String(locID) + "}"
    );   //Send the request
    String payload = http.getString();                  //Get the response payload
    
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    
    http.end();  //Close connection
    //val=ogval  
    delay(10); 
  } else {
    Serial.println(SoftSerial.available());
  }
  delay(10000);  //Send a request every 10 seconds
}  
