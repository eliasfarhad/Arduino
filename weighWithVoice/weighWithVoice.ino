#define CUSTOM_SETTINGS
#define INCLUDE_VOICE_RECOGNIZER_SHIELD
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_TEXT_TO_SPEECH_SHIELD

#include <OneSheeld.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

HX711 cell(3, 2);
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

float sensorValue = 0;
char charVal[4];

const char str1[] = "what's the temperature inside the box";
const char str3[] = "what is the temperature inside the box";


const char str2[] = "what's the weight of my package";
const char str4[] = "what is the weight of my package";

long val = 0;
float count = 0;
int roundResult = 0;
float tempResult = 0;
char charVal2[4];

long previousMillis = 0;
long interval = 1000;


void setup() {
  lcd.begin(16,2);
  lcd.print("Hey, Brad! -USPS");
  delay(3000);
  
  OneSheeld.begin();

  VoiceRecognition.setOnError(error);
  VoiceRecognition.start();
}

void loop() {

   val = 0.5 * val    +   0.5 * cell.read();
   float result = ((8307500 - val) / 440.30f) - 30;

  if (abs(result - tempResult) >= .2) {
    roundResult = round(result);
  //  Serial.println(roundResult);
    lcd.clear();
    lcd.print(roundResult);
    lcd.print(" g");
    tempResult = result;

    dtostrf(result, 4, 1, charVal2);
  }

  sensorValue = 25.4;
  dtostrf(sensorValue, 4, 1, charVal);

  if(VoiceRecognition.isNewCommandReceived())
  {
    /* Compare the play command. */
    if(!strcmp(str1,VoiceRecognition.getLastCommand()) || !strcmp(str3,VoiceRecognition.getLastCommand()))
    {
        TextToSpeech.say("Temperature equals ");
        delay(1400);
        TextToSpeech.say(charVal);
        delay(1300);
        TextToSpeech.say("celsius");
        delay(3000);
    }
    /* Compare the pause command. */
    else if (!strcmp(str2,VoiceRecognition.getLastCommand()) || !strcmp(str4,VoiceRecognition.getLastCommand()))
    {
      TextToSpeech.say("Weight equals ");
        delay(1400);
        TextToSpeech.say(charVal2);
        delay(1300);
        TextToSpeech.say("grams");
        delay(3000);
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
