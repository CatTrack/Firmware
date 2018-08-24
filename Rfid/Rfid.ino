#include <SoftwareSerial.h>

SoftwareSerial SoftSerial(0, 1);

void setup()
{
  
  Serial.begin(9600);
  SoftSerial.begin(9600);
  
  SoftSerial.println("       **** Its a Software Serial **** ");
  SoftSerial.println(" Designed by www.TheEngineeringProjects.com");
  SoftSerial.println();
  
  Serial.println("       **** Its a Hardware Serial **** ");
  Serial.println(" Designed by www.TheEngineeringProjects.com");
  Serial.println();
}



void loop()
{
      if (SoftSerial.available())
      {
           char data = SoftSerial.read();
           
           if( data >= '0' && data <= '9'){
           data = data - '0';}
           else if( data >= 'A' && data <= 'F'){
           data = 10 + data - 'A';}
           
           Serial.print(data);
           delay(1000);
           
      }
}
