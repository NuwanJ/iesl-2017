
#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include "define.h"

SoftwareSerial mySerial(3, 2); // RX, TX

volatile int mode = BEGIN ;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

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

}

