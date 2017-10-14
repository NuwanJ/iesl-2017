/*

  Used Commands :

  R,G,B : On LEDs
  r,g,b : Off LEDs
  K     : Ring Buzzer
*/

void wire_begin() {
  Wire.begin(wire_address);
  Wire.onReceive(wire_onReceive);
  Wire.onRequest(wire_onRequest);
}



void wire_onReceive(int howMany) {
  lastMasterCommand = Wire.read(); // 1 byte (maximum 256 commands), it can be easily changed to integer
}

void wire_onRequest() {
  int returnValue = 0;

  switch (lastMasterCommand) {
    case 0:   // No new command was received
      Wire.write('0');
      break;

    // ---------------------------------------------------------------------------------------------------- Servo Control

    case '{':
      returnValue = '1';
      nextAction = 90;
      break;
    case '}':
      returnValue = '1';
      nextAction = 91;
      break;
    case '|':
      returnValue = '1';
      nextAction = 92;
      break;

    // ---------------------------------------------------------------------------------------------------- Servo Control

    /*case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
      returnValue = '1';
      nextAction = lastMasterCommand - '0';
      Serial.print("Next Action: ");
      Serial.println(nextAction);
      break;*/
    // ---------------------------------------------------------------------------------------------------- Red LED : On
    case 'K':
      returnValue = '1';
      buzzer(1);
      break;


    // ---------------------------------------------------------------------------------------------------- Red LED : On
    case 'R':
      returnValue = '1';
      digitalWrite(PIN_RED, HIGH);
      break;

    // ---------------------------------------------------------------------------------------------------- Red LED : Off
    case 'r':
      returnValue = '1';
      digitalWrite(PIN_RED, LOW);
      break;

    // ---------------------------------------------------------------------------------------------------- Green LED : On
    case 'G':
      returnValue = '1';
      digitalWrite(PIN_GREEN, HIGH);
      break;

    // ---------------------------------------------------------------------------------------------------- Green LED : Off
    case 'g':
      returnValue = '1';
      digitalWrite(PIN_GREEN, LOW);
      break;

    // ---------------------------------------------------------------------------------------------------- Blue LED : On
    case 'B':
      returnValue = '1';
      digitalWrite(PIN_BLUE, HIGH);
      break;

    // ---------------------------------------------------------------------------------------------------- Blue LED : Off
    case 'b':
      returnValue = '1';
      digitalWrite(PIN_BLUE, LOW);
      break;

    // ---------------------------------------------------------------------------------------------------- Read IR sensor data and reply
    case 'I':
      readIRSensors();
      returnValue = irSensors[0] + 2 * irSensors[1] + 4 * irSensors[2] + 8 * irSensors[3];
      digitalWrite(PIN_BLUE, LOW);
      break;

    default:
      returnValue = '0';
      indicatorBlink(PIN_BLUE, 3);
      break;
  }

  Serial.print(">> Command: ");
  Serial.print((char)lastMasterCommand);
  Serial.print(" | Reply: ");
  Serial.println((char)returnValue);
  uint8_t buff[1];              // split integer return value into two bytes buffer
  //buff[0] = returnValue >> 8;
  //buff[1] = returnValue & 0xff;
  buff[0] = returnValue;
  Wire.write(buff, 1);          // return slave's response to last command
  lastMasterCommand = 0;          // null last Master's command and wait for next

}

