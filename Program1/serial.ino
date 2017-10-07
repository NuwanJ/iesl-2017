
/*
   b -> debug (on|off)
   k -> Sunde buzzer
   0 -> Start Game (mode == WHITE_SQUARE)
   q -> print IR sensor values
   s -> show EEPROM values
   r -> reset EEPROM
*/
void serialEvent() {

  while (Serial.available()) {

    digitalWrite(13, HIGH);

    int r = Serial.read();
    char inChar = (char)r;


    //-------------------------------------------------------------------------------------------------------------- b -> debug
    if (inChar == 'b') {
      byte val = 0;
      debug = ! debug;
      EEPROM.update(debug, debug);
      Serial.print(F(">> Print\t:")); Serial.println(debug);
    }

    //-------------------------------------------------------------------------------------------------------------- k -> sound buzzer
    else if (inChar == 'k') {
      beep();
      Serial.println(">> Beep...");
    }

    //-------------------------------------------------------------------------------------------------------------- 0 -> Start game
    else if (inChar == '0') {
      mode = WHITE_SQUARE;
      lineType = WHITE;
      motorWrite(200, 200);
      Serial.println(">> Beep...");
    }

    //-------------------------------------------------------------------------------------------------------------- q -> print IR sensor values
    else if (inChar == 'q') {
      linePos = readSensorLine(sensor_values);
      Serial.print(linePos);
      Serial.print(" | ");
      Serial.println(irLineString);

    }

    //-------------------------------------------------------------------------------------------------------------- s -> shoe EEPROM variables
    else if (inChar == 's') {
      printEEPROM();
    }

    //-------------------------------------------------------------------------------------------------------------- s -> reset EEPROM variables
    else if (inChar == 'r') {
      resetEEPROM();
    }

    //-------------------------------------------------------------------------------------------------------------- t -> test
    else if (inChar == 't') {
      mode == BEGIN;
    }
    //-------------------------------------------------------------------------------------------------------------- 2,4,5,6,7,8,9-> bluetooth mode
    else if (mode == BLUETOOTH) {

      if  (inChar == '8')motorWrite(maxSpeed, maxSpeed);
      else if (inChar == '2')motorWrite(-1 * maxSpeed, -1 * maxSpeed);
      else if (inChar == '4')motorWrite(baseSpeed, -1 * baseSpeed);
      else if (inChar == '6')motorWrite(-1 * baseSpeed, baseSpeed);
      else if (inChar == '5')motorWrite(0, 0);

    }

    digitalWrite(13, LOW);
  }
}


void beep() {
  mySerial.print("k");
}

void beep(int k) {
  for (k; k > 0; k--)mySerial.print("k");
}
