#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>


void setup() {  
  Serial.begin(9600);     
  WiFi.begin("iPhone (2)", "whatevet");
  
  while (WiFi.status() != WL_CONNECTED) {  //Waiting for the connection
  delay(1000);
  Serial.println("Waiting for connection");
      }  
  if(WiFi.status() == WL_CONNECTED){
    Serial.println("Connection Successful");
    }    
  }


void loop() {
  Serial.begin(9600);
  
  
  String wifiSSID = "iPhone (2)";
  String wifiPASS = "whatevet";
  String userID = "0";
  int catID = 0;
  String locID = "Catflap"; // specific cat locatoin
  String location = "Indoors"; // generic cat location
  int state = 0;

  
  if(state == 1){
// ##################CONNECTING TO WIFI##################


   // if wifiSSID || wifiPASS = ""{//######################ADDING A ROUTER#################
    //}
    
    if(WiFi.status() != WL_CONNECTED){
      Serial.println("Error in Connection.");
      
      WiFi.begin("iPhone (2)", "whatevet");
      delay(5000);
    }
    if(WiFi.status() == WL_CONNECTED){
      Serial.println("Connected");
      state = 2;}


 
  if(state == 2){ //#############SCANNING THE cat###################

  if(Serial.available()>0){
    Serial.print(int(Serial.read()));  //Read serial data byte and send back to serial monitor

    HTTPClient http;
    //http.begin("https://cattrack.readme.io/v1.0/reference#testinput");      //Specify request destination
    http.begin("http://ptsv2.com/t/0f3z5-1535113827/post");
    http.addHeader("Content-Type", "text/json");  //Specify content-type header
    
    int httpCode = http.POST("setLoc = {""userID:"+ userID+",  CatID:"+ catID+",  location:"+ location+",  locID:"+ locID +"}");
    String payload = http.getString();

    Serial.println("httpCode:");
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println("payload");
    Serial.println(payload);    //Print request response payload
    http.end();  //Close connection
    delay(1000);}
  
  else{
    Serial.println("No data recieved/sent");
    delay(5000);}
    
  

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Error In WiFi Connection.");  
    delay(1000);}
  }
  }
}

