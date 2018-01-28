#define CUSTOM_SETTINGS
#define INCLUDE_VOICE_RECOGNIZER_SHIELD
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_TEXT_TO_SPEECH_SHIELD
#define INCLUDE_SMS_SHIELD

#include <OneSheeld.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"
#include "DHT.h"
#include <math.h>

#define DHTPIN 7                // what pin we are connected to
#define DHTTYPE DHT22           // DHT 22 (AM2302)

HX711 cell(3, 2);
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);
DHT dht(DHTPIN, DHTTYPE);

//float sensorValue = 0;
char charValT[4];
char charValH[4];

const char str1[] = "what's the temperature inside the box";
const char str2[] = "what is the temperature inside the box";

const char str3[] = "what's the weight of my package";
const char str4[] = "what is the weight of my package";

const char str5[] = "what's the humidity inside the box";
const char str6[] = "what is the humidity inside the box";

long val = 0;
float count = 0;
int roundResult = 0;
float poundWeight = 0;
float tempResult = 0;
char charValW[4];

long previousMillis = 0;
long interval = 3000;

boolean isMessageSent = false;


void setup() {
  lcd.begin(16,2);
  OneSheeld.begin();
  dht.begin();

  VoiceRecognition.setOnError(error);
  VoiceRecognition.start();
}

void loop() {
  
  unsigned long currentMillis = millis();   

   val = 0.5 * val    +   0.5 * cell.read();
   float result = ((8307500 - val) / 440.30f) - 31 - 38;                           // silver top = 55 g, paper top = 37 g, glue = 1 g
   

  if (abs(result - tempResult) >= .2) {
    roundResult = round(result);
    poundWeight = abs(result * 0.0022);
 //   poundWeight = roundf(poundWeight * 100) / 100;
 //   poundWeight = ((int)(poundWeight * 100 + .5)/100.0);
    lcd.print("                ");
    lcd.setCursor(0,0);
    lcd.print(poundWeight);
    lcd.print(" lbs");
    tempResult = result;

//    dtostrf(result, 4, 1, charValW);
    dtostrf(poundWeight, 4, 1, charValW);
  }

  if (currentMillis - previousMillis > interval) {
    
    previousMillis = currentMillis;
  //  float t = dht.readTemperature();
    float t = (dht.readTemperature()*(9.0/5.0)) + 32.0;
    float h = dht.readHumidity();
 //   lcd.clear();
    lcd.setCursor(0,1);
    lcd.print (t);
    lcd.setCursor(6,1);
    lcd.print("*F");
    lcd.setCursor(10,1);
    lcd.print (h);
    lcd.print("%");
    lcd.setCursor(0,0);
  }

 // sensorValue = 25.4;
 // dtostrf(sensorValue, 4, 1, charValT);

  if(VoiceRecognition.isNewCommandReceived())
  {
    if(!strcmp(str1,VoiceRecognition.getLastCommand()) || !strcmp(str2,VoiceRecognition.getLastCommand()))
    {
      float t = (dht.readTemperature()*(9.0/5.0)) + 32.0;
      
      if (isnan(t)) {
        TextToSpeech.say("Failed to read from the sensor");
        delay(5000);
      }
      else {
        dtostrf(t, 4, 1, charValT);
        TextToSpeech.say("Temperature equals ");
        delay(1400);
        TextToSpeech.say(charValT);
        delay(1300);
        TextToSpeech.say("fahrenheit");
   //     delay(3000);
   
        if (t > 60.0) {
          if (!isMessageSent) {
            SMS.send("+12023043417", "WARNING! Package Temperature is higher than 60 degree fahrenheit. Immediate attention required.");
            isMessageSent = true;     // 5712127214, 7037985149
           }
        }
        else {
          isMessageSent = false;
        }
      }   
    }
    else if (!strcmp(str3,VoiceRecognition.getLastCommand()) || !strcmp(str4,VoiceRecognition.getLastCommand()))
    {
      TextToSpeech.say("Weight equals ");
      delay(1400);
      TextToSpeech.say(charValW);
//      if (result < 100.0) {
//        delay(1300);
//      }
//      else if (result >= 100.0 && result < 1000.0) {
//        delay(2000);
//      }
//      else if (result >= 1000.0) {
//        delay(3000);
//      }
      delay(1500);
      TextToSpeech.say("pounds");
    }
    else if(!strcmp(str5,VoiceRecognition.getLastCommand()) || !strcmp(str6,VoiceRecognition.getLastCommand()))
    {
      float h = dht.readHumidity();

      if (isnan(h)) {
        TextToSpeech.say("Failed to read from the sensor");
        delay(5000);
      }
      else {
        dtostrf(h, 4, 1, charValH);
        TextToSpeech.say("Humidity equals ");
        delay(1400);
        TextToSpeech.say(charValH);
        delay(1500);
        TextToSpeech.say("percent");
 //       delay(3000);  
      }
    }
  }
}




/* Error checking function. */
void error(byte errorData)
{
  /* Switch on error and print it on the terminal. */
  switch(errorData)
  {
    case NETWORK_TIMEOUT_ERROR: Terminal.println("Network timeout");break;
    case NETWORK_ERROR: Terminal.println("Network Error");break;
    case AUDIO_ERROR: Terminal.println("Audio error");break;
    case SERVER_ERROR: Terminal.println("No Server");break;
    case SPEECH_TIMEOUT_ERROR: Terminal.println("Speech timeout");break;
    case NO_MATCH_ERROR: Terminal.println("No match");break;
    case RECOGNIZER_BUSY_ERROR: Terminal.println("Busy");break;
  }
}
