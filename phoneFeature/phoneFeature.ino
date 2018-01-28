#define CUSTOM_SETTINGS
#define INCLUDE_PHONE_SHIELD
#define INCLUDE_SMS_SHIELD

#include <OneSheeld.h>

boolean isMessageSent = false;
//int tracker = true;

void setup() {

  OneSheeld.begin();
}

void loop() {

  float temp = 22.6;
  delay(5000);

  if (temp > 20.0 && temp < 25.0) 
  {   
    if (!isMessageSent) 
    {
      SMS.send("+13474197893", "Package Temperature is higher than 20 degree celsius");
      isMessageSent = true;
  //    tracker = false;
    }
  }
  else
  {
    isMessageSent = false;
  }
  
  if (temp > 25.0)
  {
    Phone.call("+13474197893");
  }
}
