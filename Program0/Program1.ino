#include <Servo.h>
#include <EEPROM.h>
#include "define.h";

float Kp = 0;
float Kd = 0;
float Ki = 0;

volatile int mode = BEGIN ;

void setup() {
  Serial.begin(9600);
  lineFollowBegin();

  Serial.println("L");
  Kp = (float)EEPROM.read(eP) / 10;
  Ki = (float)EEPROM.read(eI) / 10;
  Kd = (float)EEPROM.read(eD) / 10;

  baseSpeed = (int)EEPROM.read(eBase);
  maxSpeed = (int)EEPROM.read(eMax);
  sPrint =  (int)EEPROM.read(eDebug);

  //Serial.println(sPrint);
  drop();
}

void test() {

}


