int oldMode = mode;
int i = 0, j = 0;

void loop() {
  displayLoopStatus(mode);

  switch (mode) {

    //-------------------------------------------------------------------------------------------------------------- Begin
    case BEGIN:
      buttonStatus = digitalRead(BUTTON_1);

      if (buttonStatus == 0 ) {

        /*motorWrite(150, -150);
          delay(500);
          motorStop();*/

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
        motorWait(10);
        mode = OUTER_FLOOR;

      } else {
        //test();
      }

      break;

    //-------------------------------------------------------------------------------------------------------------- Follow outer floor (White Line)
    case OUTER_FLOOR:

      linePos = readSensorLine(sensor_values);

      if (leftEnd == 1 && rightEnd == 1) {    // Robo entered to storage floor
        motorWait(10);
        mode = STORAGE_FLOOR;
        lineType = BLACK;

      } else {
        lineFollow(linePos);
      }

      break;

    //-------------------------------------------------------------------------------------------------------------- Follow storage floor (Black Line)
    case STORAGE_FLOOR:

      linePos = readSensorLine(sensor_values);

      if (leftEnd == 1 &&  rightEnd == 1 ) {
        // End of the storage floor
        lineType = WHITE;
        i = 3;
        j = 3;
        mode = PROD_FLOOR;

      } else  if (leftEnd == 1 && i < 3) {
        // Find a T junction, just skip it
        motorStop();
        beep(i + 1);

        motorWrite(150, 150);
        delay(250);
        motorWrite(-150, 150);
        delay(150);
        //delay(100);
        //motorStop();

        //Serial.println("rotate CCW");
        rotate90(CCW);
        Serial.println("findShelf");
        findShelf();
        Serial.println("backToPath");
        backToPath();
        Serial.println("rotate CCW");
        rotate90(CCW);

        //motorWrite(150, 150);
        delay(250);

        i++;
        j++;

      } else {
        lineFollow(linePos);
      }

      break;

    //-------------------------------------------------------------------------------------------------------------- Follow production floor (White Line)
    case PROD_FLOOR:

      linePos = readSensorLine(sensor_values);

      if (rightEnd == 1) {
        // Find a T junction, just skip it
        motorStop();
        beep(i);
        delay(10);
        motorWrite(150, 150);
        delay(250);
        i++;
        j++;

        if (i == 6) {
          // End of the arena
          motorStop();
          delay(5000);
          mode = PROD_FLOOR_B;
        }

      } else {
        lineFollow(linePos);
      }

      break;

    //-------------------------------------------------------------------------------------------------------------- Follow production floor reverse (White Line)
    case PROD_FLOOR_B:

      linePos = readSensorLine(sensor_values);

      if (leftEnd == 1 && rightEnd == 1) {
        mode = STORAGE_FLOOR_B;
        lineType == BLACK;
        motorWrite(baseSpeed, baseSpeed);
        delay(150);

      } else if (leftEnd == 1) {
        // Find a T junction, just skip it
        motorStop();
        beep(i);
        delay(10);
        motorWrite(150, 150);
        delay(250);
        i--;
        j--;

      } else {
        lineFollow(linePos);
      }

      break;

    //-------------------------------------------------------------------------------------------------------------- Follow storage floor reverse (Black Line)
    case STORAGE_FLOOR_B:

      linePos = readSensorLine(sensor_values);

      if (leftEnd == 1 &&  rightEnd == 1 ) {
        // End of the storage floor
        lineType = WHITE;
        mode = OUTER_FLOOR_B;

      } else if (rightEnd == 1 && i > 0) {
        // Find a T junction, just skip it
        motorStop();
        beep(i);
        delay(10);
        motorWrite(150, 150);
        delay(250);
        i--;
        j--;

      } else {
        lineFollow(linePos);
      }

      break;

    //-------------------------------------------------------------------------------------------------------------- Outer floor :reverse
    case OUTER_FLOOR_B:
      linePos = readSensorLine(sensor_values);

      if (allIn == 1) {
        motorWrite(150, 150);
        delay(150);
        motorStop();
        beep(3);
      } else {
        lineFollow(linePos);
      }
      break;
















    //-------------------------------------------------------------------------------------------------------------- Test
    case TEST:
      //buttonStatus = digitalRead(BUTTON_1);

      lineType = BLACK;

      Serial.println("rotate");
      rotate90(CCW);
      Serial.println("findShelf");
      findShelf();
      Serial.println("backToPath");
      backToPath();

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

      case OUTER_FLOOR:
        Serial.println("Outer Floor");
        break;
      case STORAGE_FLOOR:
        Serial.println("Storage Floor");
        break;
      case PROD_FLOOR:
        Serial.println("Production Floor");
        break;

      case OUTER_FLOOR_B:
        Serial.println("Outer Floor : Back");
        break;
      case STORAGE_FLOOR_B:
        Serial.println("Storage Floor : Back");
        break;
      case PROD_FLOOR_B:
        Serial.println("Production Floor : Back");
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
