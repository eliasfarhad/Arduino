#include "HX711.h"

HX711 cell(3, 2);

void setup() {
  Serial.begin(9600);
}

long val = 0;
float count = 0;
float tempResult = 0;

void loop() {
//  count = count + 1;
  
  // Use only one of these
  //val = ((count-1)/count) * val    +  (1/count) * cell.read(); // take long term average
  
  val = 0.5 * val    +   0.5 * cell.read(); // take recent average
  
 //  val = cell.read(); // most recent reading
  
 // Serial.println( val );
//  Serial.println(val - 8307600);
//  Serial.println((8307600 - val) / 440.30f);
 
  float result = ((8307500 - val) / 440.30f) - 29.40;         // 29.40g is the weight of the plastic on top of the load cell

  if (abs(result - tempResult) >= .2) {
    int roundResult = round(result);
    Serial.println(roundResult);
    tempResult = result;
  }
}

// 8334606

// 8308000

// 8388607

// 407.68f

