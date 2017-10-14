
#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "define.h"

SoftwareSerial mySerial(3, 2); // RX, TX

volatile int mode = TEST;//BEGIN ;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Wire.begin();

  irSensorsBegin();
  eepromBegin();
  lineFollowBegin();
  //sonarBegin();

  motorsBegin();

  pinMode(BUTTON_1, INPUT_PULLUP);
  //pinMode(BUTTON_2, INPUT_PULLUP);

  pinMode(PIN_LED, OUTPUT);
  //loadEEPROM(); // loading EEPROM data

  beep(2);
}

void test() {

  int  s = readIR();

  if (s == 0) {
    // 0x0 NoBox
    Serial.println("0x0 NoBox");

  } else if (s == 1) {      // 0001
    // 3x3 NoBox
    Serial.println("3x3 NoBox");

  } else if (s == 11) {     // 0011 -> Take Box 0
    // 0x0 Box || 5x5 NoBox
    Serial.println("0x0 Box || 5x5 NoBox ");

  } else if (s == 111) {    // 0111 -> Take Box 3
    // 3x3 Box
    Serial.println("3x3 Box");

  } else if (s == 1111) {   // 1111 -> Take Box 5
    // 5x5 Box
    Serial.println("5x5 Box");

  } else {
    Serial.println(s);
  }


}

