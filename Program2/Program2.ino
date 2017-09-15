#include <Servo.h>
#include <Wire.h>
#include "define.h"
Servo pick, grab;

void setup() {

  Serial.begin(9600);
  Serial.println(">> Begin : Prog2");

  //compassBegin();
  //sharpIRBegin();
  //sonarBegin();
  //colorBegin();
  indicatorBegin();

}

/*
  ---- Beeps -------------------------------------------------
  1
  2
  3
  4 beeps --> Color Sensor not attached
  5
*/

void loop() {
  delay(100);

}

