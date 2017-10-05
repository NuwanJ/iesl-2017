
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

