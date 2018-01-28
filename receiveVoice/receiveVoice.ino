#define CUSTOM_SETTINGS
#define INCLUDE_VOICE_RECOGNIZER_SHIELD
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_TEXT_TO_SPEECH_SHIELD

#include <OneSheeld.h>

float sensorValue = 0;
char charVal[4];


void setup() {
  OneSheeld.begin();

}

void loop() {
  sensorValue = 25.4;
  dtostrf(sensorValue, 4, 1, charVal);
  TextToSpeech.say("Temperature equals ");
  delay(1400);
  TextToSpeech.say(charVal);
  delay(1300);
  TextToSpeech.say("celsius");
  delay(3000);

}
