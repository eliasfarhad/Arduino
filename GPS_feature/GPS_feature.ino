/*

GPS Shield Example

This example shows an application on 1Sheeld's GPS shield.

By using this example, you can send an SMS when the smartphone
is in a hundred meters distance from a fixed coordinates you
provide.

OPTIONAL:
To reduce the library compiled size and limit its memory usage, you
can specify which shields you want to include in your sketch by
defining CUSTOM_SETTINGS and the shields respective INCLUDE_ define. 

*/

#define CUSTOM_SETTINGS
#define INCLUDE_GPS_SHIELD

/* Include 1Sheeld library.*/
#include <OneSheeld.h>

float dist = 1.0;
long previousMillis = 0;
long interval = 1000;

void setup() 
{
  /* Start communication.*/
  OneSheeld.begin();
  Serial.begin(9600);
}

void loop()
{
   /* Always check if the smartphone's GPS and a given latitude and longitude are in a range of 100 meters. */
//  if(GPS.getDistance(38.8842251,-77.0266104))
//  {
//    Serial.println("Smartphone is In Range.");
//  }
//  else 
//  {
//     Serial.println("Smartphone is Not In Range."); 
//  }

  unsigned long currentMillis = millis();  

  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
//    dist = GPS.getDistance(38.8842251,-77.0266104);
    dist = GPS.getDistance(38.860529,-77.087747);
    Serial.println(dist);
  }
}






//#define CUSTOM_SETTINGS
//#define INCLUDE_GPS_SHIELD
//
//#include <OneSheeld.h>
//
//float latitude = 0;
//float longitude = 0;
//
//long previousMillis = 0;
//long interval = 1000;
//
//void setup() {
//  OneSheeld.begin();
//  Serial.begin(9600);
//}
//
//void loop() {
//
//  unsigned long currentMillis = millis();  
//
//  latitude = GPS.getLatitude();
//
//  if (currentMillis - previousMillis > interval) {
//    previousMillis = currentMillis;
//    Serial.println(latitude);
//  }
//}

