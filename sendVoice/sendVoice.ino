/*

Voice Recognition Shield Example

This example shows an application on 1Sheeld's voice recognition shield.

By using this example, you can play, pause and stop your smartphone's 
music using voice commands.

OPTIONAL:
To reduce the library compiled size and limit its memory usage, you
can specify which shields you want to include in your sketch by
defining CUSTOM_SETTINGS and the shields respective INCLUDE_ define. 

*/

#define CUSTOM_SETTINGS
#define INCLUDE_VOICE_RECOGNIZER_SHIELD
#define INCLUDE_MUSIC_PLAYER_SHIELD
#define INCLUDE_TERMINAL_SHIELD

/* Include 1Sheeld library. */
#include <OneSheeld.h>

/* Voice commands set by the user. */
const char str1[] = "on";
const char str2[] = "off";
int led = 13;

void setup()
{
  /* Start Communication. */
  OneSheeld.begin();
  /* Error Commands handiling. */
  VoiceRecognition.setOnError(error);
  VoiceRecognition.start();
  pinMode(led, OUTPUT);
}

void loop () 
{
  /* Check if new command received. */
  if(VoiceRecognition.isNewCommandReceived())
  {
    /* Compare the play command. */
    if(!strcmp(str1,VoiceRecognition.getLastCommand()))
    {
      digitalWrite(led, HIGH);
    }
    /* Compare the pause command. */
    else if (!strcmp(str2,VoiceRecognition.getLastCommand()))
    {
      digitalWrite(led, LOW);
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
