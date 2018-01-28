/*
  Blink
  Turns an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.
 */

 int led = 9;

// the setup routine runs once in the beginning of execution (or when you press reset):
void setup() {
  // inititalize the digital pin as an output.
  pinMode(led, OUTPUT);
}

// the loop function runs over and over again, forever:
void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(led, HIGH);      // turn the LED on (HIGH is the voltage level)
  delay(1000);                  // wait for a second
  digitalWrite(led, LOW);       // turn the LED off by making the voltage LOW
  delay(1000);                  // wait for a second
}
