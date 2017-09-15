int oldMode = mode;

void loop() {
  displayLoopStatus(mode);

  switch (mode) {

    //-------------------------------------------------------------------------------------------------------------- Begin
    case BEGIN:
      buttonStatus = digitalRead(BUTTON_1);

      if (buttonStatus == 0 ) {
        mode =  TEST; 
        Serial.println(F(">> BEGIN -> ###"));
      } else {
        delay(50);
      }
      break;

    //-------------------------------------------------------------------------------------------------------------- Test
    case TEST:
      buttonStatus = digitalRead(BUTTON_1);

      if (buttonStatus == 0 ) {
        mode = BEGIN;
        beep(2);
        Serial.println(F(">> TEST -> BEGIN"));
      } else {
        //test();
      }

      break;
  }
}


void displayLoopStatus(int mode) {

  if (mode != oldMode) {
    oldMode = mode;
    Serial.println(F("--------------------------------------------------"));
    switch (mode) {
      case BEGIN:
        Serial.println("BEGIN");
        break;
      case TEST:
        Serial.println("TEST");
        break;
    }
    Serial.println(F("--------------------------------------------------"));
  }
}



void debugProcedure() {

  beep();
}
