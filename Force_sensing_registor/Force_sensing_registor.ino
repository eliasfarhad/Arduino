int pressurePin = A0;
int force;
int LEDpin = 12;

void setup() {
  pinMode(LEDpin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  force = analogRead(pressurePin);
  Serial.println(force);

  if (force > 500) {
    digitalWrite(LEDpin, HIGH);
  }
  else {
    digitalWrite(LEDpin, LOW);
  }
  delay(100);
}









// The code below did not give the desired output

//int fsrAnalogPin = A0;
//int LEDpin = 9;
//int fsrReading;
//int LEDbrightness;
//
//void setup(void) {
//  // put your setup code here, to run once:
//  Serial.begin(9600);
//  pinMode(LEDpin, OUTPUT);
//}
//
//void loop(void) {
//  // put your main code here, to run repeatedly:
//  fsrReading = analogRead(fsrAnalogPin);
//  int num = fsrAnalogPin/5;
//  Serial.print("Analog reading = ");
//  Serial.println(num);
//
//  LEDbrightness = map(fsrReading, 0, 1023, 0, 255);
//
//  analogWrite(LEDpin, LEDbrightness);
//
//  delay(100);
//}
