

#define PICK_ON 160
#define PICK_OFF 80


#define GRAB_UP 50
#define GRAB_0 170
#define GRAB_3 160
#define GRAB_5 150


void handleServo(int type) {

  buzzer(type + 1);
  readyToPick(type);
  //delay(1000);
  pickBox();
  //delay(1000);
  dropBox(type);
  delay(1000);
  //stand();
}


void pickBox() {

  attachServos();

  pick.write(PICK_ON);
  delay(1000);
  grab.write(GRAB_UP);
  delay(1500);
  detachServos();
  Serial.println(">> Pick : Complete");

}

void readyToPick(int type) {
  attachServos();
  pick.write(PICK_OFF);
  delay(1000);

  if (type == 0)grab.write(GRAB_0);
  else if (type == 1)grab.write(GRAB_3);
  else if (type == 2)grab.write(GRAB_5);

  delay(1000);
  detachServos();
  Serial.println(">> readyToPick : Complete");
}

void dropBox(int type) {
  attachServos();

  if (type == 0)grab.write(GRAB_0);
  else if (type == 1)grab.write(GRAB_3);
  else if (type == 2)grab.write(GRAB_5);

  delay(1000);
  pick.write(PICK_OFF);
  delay(500);
  detachServos();
  datachServoPick();
  Serial.println(">> Drop : Complete");
}

void stand() {
  attachServos();
  grab.write(GRAB_UP);
  delay(500);
  pick.write(PICK_ON);
  delay(1000);
  detachServos();
  datachServoPick();
  //Serial.println(">> stand : Complete");
}

void attachServos() {
  pick.attach(PIN_PICK_COLLECT);
  grab.attach(PIN_SERVO_LIFT);
}

void detachServos() {
  grab.detach();
}

void datachServoPick() {
  pick.detach();
}


