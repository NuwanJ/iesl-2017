
/****************************************************************************
  Functions

  lineFollowingBegin()
  int, calculatePID()

****************************************************************************/

void lineFollowBegin() {
  //lineType = WHITE;
  lineType = BLACK;
}

void lineFollow(int pos) {

  //pos = readSensorLine(sensor_values);
  error = (pos - CENTER_EDGE_READING);

  if (debug) Serial.println(error);//irLineString

  if (error != lastError || error == 0) {

    //PID Calculating
    int motorSpeed = calculatePID(error);

    if (error == 0) {
      rightMotorSpeed = maxSpeed;
      leftMotorSpeed = maxSpeed;

    } else {

      //Assigning motor speeds
      rightMotorSpeed = baseSpeed + motorSpeed;
      leftMotorSpeed = baseSpeed - motorSpeed;

      if (leftMotorSpeed < 0 && allOut == 0) leftMotorSpeed = leftMotorSpeed * slowFactor ;
      if (rightMotorSpeed < 0 && allOut == 0) rightMotorSpeed = rightMotorSpeed * slowFactor;
    }

    motorWrite(leftMotorSpeed, rightMotorSpeed);
    lastError = error;
  }
  //delay(50);
}

int calculatePID(int error) {

  int P = error * kP;
  int I = I + (error * kI);
  int D = (error - lastError) * 0;

  lastError = error;

  return (P + I + D);
}
