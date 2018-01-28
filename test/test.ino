#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

HX711 cell(3, 2);
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

long val = 0;
float count = 0;
float tempResult = 0;

long previousMillis = 0;
long interval = 1000;

void setup() {
  
  lcd.begin(16,2);
  lcd.print("Hey, Brad! -USPS");
  delay(3000);
}

void loop() {

//  unsigned long currentMillis = millis();
//  if (currentMillis - previousMillis > interval) {
//    previousMillis = currentMillis;
//    ----------
//  }
 //  count = count + 1;
  
  // Use only one of these
  //val = ((count-1)/count) * val    +  (1/count) * cell.read(); // take long term average
  
  val = 0.5 * val    +   0.5 * cell.read(); // take recent average
  
 //  val = cell.read(); // most recent reading
  
 // Serial.println( val );
//  Serial.println(val - 8307600);
//  Serial.println((8307600 - val) / 440.30f);
 
  float result = ((8307500 - val) / 440.30f) - 31;         // 29.40g is the weight of the plastic on top of the load cell

  if (abs(result - tempResult) >= .2) {
    int roundResult = round(result);
  //  Serial.println(roundResult);
    lcd.clear();
    lcd.print(roundResult);
    lcd.print(" g");
    tempResult = result;
  }
  
//  delay(500);
}
