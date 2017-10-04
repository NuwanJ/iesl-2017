
/****************************************************************************
  Functions

  motorsBegin()
  motorWrite(left,right)
  wait( {duration})
  calibrateSpeed()

****************************************************************************/

void motorsBegin() {

  Serial.println(">> MotorControl : Begin...");

  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(leftMotorPWM, OUTPUT);

  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);

  motorWrite(0, 0);
}


void motorWrite(int leftMotorSpeed, int rightMotorSpeed) {

  //leftMotorSpeed += drift;
  //rightMotorSpeed -= drift;

  if (leftMotorSpeed != leftSpd) {              // Left Motor
    leftSpd = leftMotorSpeed;

    if (leftMotorSpeed > 0) {
      digitalWrite(leftMotor1, HIGH);
      digitalWrite(leftMotor2, LOW);

    } else if (leftMotorSpeed < 0) {
      leftMotorSpeed  *= -1;
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, HIGH);


    } else {
      digitalWrite(leftMotor1, LOW);
      digitalWrite(leftMotor2, LOW);
    }
  }

  if (rightMotorSpeed != rightSpd) {              // Right Motor
    rightSpd = rightMotorSpeed;

    if (rightMotorSpeed > 0) {
      digitalWrite(rightMotor1, HIGH);
      digitalWrite(rightMotor2, LOW);

    } else if (rightMotorSpeed < 0) {
      rightMotorSpeed *= -1;
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, HIGH);

    } else {
      digitalWrite(rightMotor1, LOW);
      digitalWrite(rightMotor2, LOW);
    }
  }

  // Limit motor speed below maxSpeed
  rightMotorSpeed =  min(rightMotorSpeed, maxSpeed) ;
  leftMotorSpeed =  min(leftMotorSpeed, maxSpeed) ;

  analogWrite(leftMotorPWM, leftMotorSpeed);
  analogWrite(rightMotorPWM, rightMotorSpeed);

  if (debug) {
    Serial.print(">> L:"); Serial.print(leftMotorSpeed); Serial.print(" R:"); Serial.println(rightMotorSpeed);
  }
}

void motorStop() {

  analogWrite(leftMotorPWM, 0);
  analogWrite(rightMotorPWM, 0);

  digitalWrite(leftMotorPWM, LOW);
  digitalWrite(rightMotorPWM, LOW);

  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, HIGH);

  digitalWrite(leftMotor1, HIGH);
  digitalWrite(leftMotor2, HIGH);

  leftSpd = 0;
  rightSpd = 0;
}

void motorLeft(int spd) {
  motorWrite(0, spd);
}

void motorRight(int spd)
{
  motorWrite(spd, 0);
}

void motorWait() {
  motorWrite(0, 0);
}

void motorWait(int d) {
  motorWrite(0, 0);
  delay(d);
}

void calibrateSpeed() {
  Serial.println(F(">> Calibrating Speed \n"));
  Serial.println(F(">> Increasing Mode"));

  for (int i = 0; i <= 255; i += 1) {
    Serial.print("Speed : "); Serial.println(i);
    motorWrite(i, i);
    delay(100);
  }

  delay(5000);

  Serial.println(F("\n>> Decreasing Mode"));

  for (int i = 250; i >= 10 ; i -= 1) {
    Serial.print("Speed : "); Serial.println(i);
    motorWrite(i, i);
    delay(100);
  }
}



void rotate90(int dir) {

  // Rotate CCW/CW until middle sensor left line

  linePos = readSensorLine(sensor_values);

  if (dir == CCW) {
    while (linePos <= CENTER_EDGE_READING) {
      motorWrite(baseSpeed, -1 * baseSpeed);
      linePos = readSensorLine(sensor_values);
      delay(10);
    }
  } else {
    while (linePos >= CENTER_EDGE_READING) {
      motorWrite(-1 * baseSpeed, baseSpeed);
      linePos = readSensorLine(sensor_values);
      delay(10);
    }
  }
  motorStop();
  delay(10);

  // Rotate CCW/CW until robot centered to new line segment

  linePos = readSensorLine(sensor_values);
  while (linePos != CENTER_EDGE_READING) {
    linePos = readSensorLine(sensor_values);

    if (dir == CCW) {
      if (linePos <= CENTER_EDGE_READING) error = 20;
      else error = linePos - CENTER_EDGE_READING;

    } else {
      if (linePos <= CENTER_EDGE_READING) error = -20;
      else error = -1 * (linePos - CENTER_EDGE_READING);

    }
    rightMotorSpeed = baseSpeed / 2 + (error * -10);
    leftMotorSpeed = baseSpeed / 2 - (error * -10);

    motorWrite(leftMotorSpeed, rightMotorSpeed);
    delay(10);
  }

  motorStop();
  //findEnd();

}

void findEnd() {

  linePos = readSensorLine(sensor_values);
  // If the robot meets the end, condition satisfy
  while  (sum < 4) { //((allIn || ((linePos >= 30 || linePos <= 20) && sum == 4)) == 0) {
    lineFollow(linePos);
    linePos = readSensorLine(sensor_values);
    Serial.println(linePos);
    delay(20);
  }
  motorStop();
  motorWrite(-150, -150);
  delay(70);
  motorStop();
}


void backToLine() {
  Serial.println("*");
  // Rotate CCW until robot left line
  motorWrite(-150, -150);
  delay(100);
  
  linePos = readSensorLine(sensor_values);
  while (allOut) {
    motorWrite(baseSpeed, -1 * baseSpeed);
    linePos = readSensorLine(sensor_values);
    delay(10);
  }
  motorStop();
  //delay(10);

  // Rotate CCW until robot centered to new line segment
  Serial.println("**");
  linePos = readSensorLine(sensor_values);
  while (linePos != CENTER_EDGE_READING) {
    linePos = readSensorLine(sensor_values);

    if (linePos <= CENTER_EDGE_READING) error = 20;
    else error = linePos - CENTER_EDGE_READING;

    rightMotorSpeed = baseSpeed + (error * -10);
    leftMotorSpeed = baseSpeed - (error * -10);
    motorWrite(leftMotorSpeed, rightMotorSpeed);
    delay(10);
  }
  motorStop();
  Serial.println("***");
  delay(500);

  // Now go forward until robot meet the main line
  linePos = readSensorLine(sensor_values);
  while (leftEnd == 1 && rightEnd == 1) {
    linePos = readSensorLine(sensor_values);
    lineFollow(linePos);
    delay(10);
  }
  motorStop();
  Serial.println("****");
}

