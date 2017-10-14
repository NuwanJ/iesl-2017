#include <Servo.h>
#include <Wire.h>
#include "define.h"
Servo pick, grab;

void setup() {

  Serial.begin(9600);
  Serial.println(">> Begin : Prog2");

  wire_begin();
  indicatorBegin();
  sensorBegin();
}

/*
  ---- Beeps -------------------------------------------------
  1
  2
  3
  4 beeps --> Color Sensor not attached
  5
*/
static volatile int nextAction = 0;

void loop() {

  if (nextAction != 0) {
    Serial.print(">>> Next Action: ");
    Serial.println(nextAction);

    switch (nextAction) {
      case 90:
        handleServo(0);
        break;
      case 91:
        handleServo(1);
        break;
      case 92:
        handleServo(2);
        break;
    }
    nextAction = 0;
  }


  //noInterrupts();  // critical, time-sensitive code here

  /*readyToPick(2);
    delay(1000);
    pickBox();
    delay(1000);
    dropBox(2);
    delay(2000);*/


  //interrupts();

}

