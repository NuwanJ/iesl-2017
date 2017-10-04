int oldMode = mode;

void loop() {
  displayLoopStatus(mode);

  switch (mode) {

    //-------------------------------------------------------------------------------------------------------------- Begin
    case BEGIN:
      buttonStatus = digitalRead(BUTTON_1);

      if (buttonStatus == 0 ) {
        mode = WHITE_SQUARE;
        lineType = WHITE;
        motorWrite(200, 200);
      } else {
        delay(10);
      }
      break;


    //-------------------------------------------------------------------------------------------------------------- White Square
    case WHITE_SQUARE:

      readSensorLine(sensor_values);

      if (allIn == 0 ) {    // Robo exits the square
        motorWait(100);
        mode = FOLLOW_OUTER;
      } else {
        //test();
      }

      break;

    //-------------------------------------------------------------------------------------------------------------- Follow outer floor (White Line)
    case FOLLOW_OUTER:

      linePos = readSensorLine(sensor_values);

      if (leftEnd == 1 && rightEnd == 1) {    // Robo entered to storage floor
        motorWait(100);
        mode = FOLLOW_STORAGE;
        lineType = BLACK;

      } else {
        lineFollow(linePos);
      }

      break;

    //-------------------------------------------------------------------------------------------------------------- Follow storage floor (Black Line)
    case FOLLOW_STORAGE:

      linePos = readSensorLine(sensor_values);

      if (leftEnd == 1) {
        motorWait(1000);
        Serial.println("rotate90");
        rotate90(CCW);
        beep();
        delay(1000);
        Serial.println("findEnd");
        findEnd();
        beep();
        delay(1000);
        Serial.println("backToLine");
        backToLine();
        beep();
        delay(1000);
        Serial.println("Begin");
        mode = BEGIN;
      } else {
        lineFollow(linePos);
      }

      break;

    //-------------------------------------------------------------------------------------------------------------- Test
    case TEST:
      buttonStatus = digitalRead(BUTTON_1);
      lineType = BLACK;
      rotate90(CW);
      findEnd();
      //backToLine();

      delay(10000);

      /*if (buttonStatus == 0 ) {
        mode = BEGIN;
        beep(2);
        Serial.println(F(">> TEST -> BEGIN"));
        } else {
        //test();
        }*/

      break;

    //-------------------------------------------------------------------------------------------------------------- Line Follow
    case LINE_FOLLOW:
      //buttonStatus = digitalRead(BUTTON_1);
      linePos = readSensorLine(sensor_values);

      if (0 ) {
        mode = BEGIN;
      } else {
        lineFollow(linePos);
      }

      break;

    //-------------------------------------------------------------------------------------------------------------- Bluetooth mode
    case BLUETOOTH:
      // Nothing to do here
      //delay(2000);
      //Serial.println("Bluetooth Mode");
      break;
  }
  displayLoopStatus(mode);
}

boolean detectColorChange(unsigned int *sensor_values) {
  if (sensor_values[0] == 1 && sensor_values[NUM_SENSORS - 1] == 1) {
    return true;
  } else {
    return false;
  }
}

void displayLoopStatus(int mode) {

  if (mode != oldMode) {
    beep();
    oldMode = mode;
    Serial.println(F("--------------------------------------------------"));
    switch (mode) {
      case BEGIN:
        Serial.println("BEGIN");
        break;

      case WHITE_SQUARE:
        Serial.println("WHITE_SQUARE");
        break;
      case FOLLOW_OUTER:
        Serial.println("FOLLOW_OUTER");
        break;
      case FOLLOW_STORAGE:
        Serial.println("FOLLOW_STORAGE");
        break;

      case LINE_FOLLOW:
        Serial.println("LINE_FOLLOW");
        break;
      case TEST:
        Serial.println("TEST");
        break;
      case BLUETOOTH:
        Serial.println("Bluetooth");
        break;
    }
    Serial.println(F("--------------------------------------------------"));
  }
}



void debugProcedure() {

  beep();
}
