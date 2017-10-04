
/*
   b -> debug (on|off)

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

    //-------------------------------------------------------------------------------------------------------------- s -> ???
    else if (inChar == 's') {
      /*
        Serial.print("Kp\t:"); Serial.println(kP * 10);
        Serial.print("Ki\t:"); Serial.println(kI * 10);
        Serial.print("Kd\t:"); Serial.println(kD * 10);
        Serial.print("Base\t:" ); Serial.println(baseSpeed);
        Serial.print("Max\t:"); Serial.println(maxSpeed);
        Serial.print("Debug\t:"); Serial.println(debug);
      */
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
