#define CUSTOM_SETTINGS
#define INCLUDE_VOICE_RECOGNIZER_SHIELD
#define INCLUDE_TERMINAL_SHIELD
#define INCLUDE_TEXT_TO_SPEECH_SHIELD

#include <OneSheeld.h>

float sensorValue = 0;
char charVal[4];

const char str1[] = "on";
const char str2[] = "off";


void setup() {
  OneSheeld.begin();

  VoiceRecognition.setOnError(error);
  VoiceRecognition.start();
}

void loop() {
  sensorValue = 25.4;
  dtostrf(sensorValue, 4, 1, charVal);

    if(VoiceRecognition.isNewCommandReceived())
  {
    /* Compare the play command. */
    if(!strcmp(str1,VoiceRecognition.getLastCommand()))
    {
        TextToSpeech.say("Temperature equals ");
        delay(1400);
        TextToSpeech.say(charVal);
        delay(1300);
        TextToSpeech.say("celsius");
        delay(3000);
    }
    /* Compare the pause command. */
    else if (!strcmp(str2,VoiceRecognition.getLastCommand()))
    {
      TextToSpeech.say("Humidity equals ");
        delay(1400);
        TextToSpeech.say(charVal);
        delay(1300);
        TextToSpeech.say("percent");
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
