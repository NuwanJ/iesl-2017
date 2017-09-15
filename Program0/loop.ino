
void loop() {

  switch (mode) {

    // ---------------------------------------------------------------------------------------------------------------------- Test
    case TEST:




      break;

    // ---------------------------------------------------------------------------------------------------------------------- Begin
    case BEGIN:

      buttonStatus = digitalRead(BUTTON_1);

      if (buttonStatus == 0 ) {
        //turnDirection = LEFT;
        mode = TEST;

      } else {

      }
      break;



  }
}
