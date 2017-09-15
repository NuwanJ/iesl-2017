String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void serialEvent() {

  while (Serial.available()) {
    int r = Serial.read();
    char inChar = (char)r;
    inputString += inChar;

    if (inChar == '\n' || (inChar == '\r') ) {

      inputString = inputString.substring(0, inputString.length() - 1);
      stringComplete = true;

      if (inputString.substring(0, 1) == "p") {
        int val = (int)inputString.substring(1).toInt();
        Kp = (float)val / 10;
        EEPROM.update(eP, (byte)val);
        Serial.print("Kp:"); Serial.println(val);
      }

      else if (inputString.substring(0, 1) == "i") {
        int val = inputString.substring(1).toInt();
        Ki = (float)val / 10;
        EEPROM.update(eI, (byte)val);
        Serial.print("Ki:"); Serial.println(val);
      }

      else if (inputString.substring(0, 1) == "d") {
        int val = inputString.substring(1).toInt();
        Kd = (float)val / 10;
        EEPROM.update(eD, (byte)val);
        Serial.print("Kd:"); Serial.println(val);
      }

      else if (inputString.substring(0, 1) == "m") {
        int val = inputString.substring(1).toInt();
        maxSpeed = val;
        EEPROM.update(eMax, (byte)val);
        Serial.print("Max speed:"); Serial.println(val);
      }

      else if (inputString.substring(0, 1) == "b") {
        int val = inputString.substring(1).toInt();
        baseSpeed = val;
        EEPROM.update(eBase, (byte)val);
        Serial.print("Base speed:"); Serial.println(val);
      }

      else if (inputString.substring(0, 1) == "+") {
        mode ++;
      }

      else if (inputString.substring(0, 1) == "-") {
        mode --;
      }

      else if (inputString.substring(0, 1) == "q") {
        byte val = 0;
        sPrint = ! sPrint;
        if (sPrint == 1)val = 1;
        EEPROM.update(eDebug, val);
        Serial.print("Print\t:"); Serial.println(sPrint);
      }

      else if (inputString.substring(0, 1) == "s") {
        Serial.print("Kp\t:"); Serial.println(Kp * 10);
        Serial.print("Ki\t:"); Serial.println(Ki * 10);
        Serial.print("Kd\t:"); Serial.println(Kd * 10);
        Serial.print("Base\t:" ); Serial.println(baseSpeed);
        Serial.print("Max\t:"); Serial.println(maxSpeed);
        Serial.print("Debug\t:"); Serial.println(sPrint);
      }

      inputString = "";
      stringComplete = false;
      Serial.println();
    }

  }
}


