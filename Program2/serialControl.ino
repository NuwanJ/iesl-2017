
/*

  a -> Read walls

  q -> Ready to pick
  w -> stand
  e -> pickBox
  r -> dropBox
  j -> readColor
  k -> beep
  d -> Change indicator (boolean 000 - 111 )
*/

void serialEvent() {

  while (Serial.available()) {
    /*//digitalWrite(13, HIGH);

      int r = Serial.read();
      char inChar = (char)r;

      // --------------------------------------------------------------------------------------- Buzzer
      if (inChar == 'k') {
      buzzer(1);
      }

      else if (inChar == '\n') {} // Nothing to do
      else if (inChar == '\r') {} // Nothing to do
      else {
      //This is to to say there is something wrong

      //Serial.write((int)inChar);
      //Serial.println();
      indicatorBlink(PIN_BLUE, 3);

      }

      //Serial.println(inChar);
      //digitalWrite(13, LOW);
      }
    */
  }
}



