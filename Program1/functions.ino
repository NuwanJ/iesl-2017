
//  50 | 25 | 00

void rotate90(int dir) {

  // Rotate CCW/CW until middle sensor left line
  linePos = readSensorLine(sensor_values);

  if (dir == CCW) {    // 25 -> 0 -> 50
    while (linePos <= CENTER_EDGE_READING) {
      motorWrite( -1 * baseSpeed, baseSpeed);
      linePos = readSensorLine(sensor_values);
      delay(10);
    }
  } else {             // 25 -> 50 -> 00
    while (linePos >= CENTER_EDGE_READING) {
      motorWrite(baseSpeed, -1 * baseSpeed);
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
    rightMotorSpeed = baseSpeed / 2 + (error * 10);
    leftMotorSpeed = baseSpeed / 2 - (error * 10);

    motorWrite(leftMotorSpeed, rightMotorSpeed);
    delay(10);
  }

  motorStop();

}

void findShelf() {

  linePos = readSensorLine(sensor_values);

  // If the robot meets the end, condition satisfy
  while  (sum < 4) { //((allIn || ((linePos >= 30 || linePos <= 20) && sum == 4)) == 0) {
    lineFollow(linePos);
    Serial.println(linePos);
    delay(20);
    linePos = readSensorLine(sensor_values);
  }
  motorStop();
  motorWrite(-150, -150);
  delay(70);
  motorStop();
}


void backToPath() {

  // Go little back before start turn
  motorWrite(-150, -150);
  delay(100);

  // Rotate CCW until robot left line
  linePos = readSensorLine(sensor_values);
  while (allOut == 0) {
    motorWrite(-1 * baseSpeed, baseSpeed);
    delay(10);
    linePos = readSensorLine(sensor_values);
  }
  motorStop();
  //delay(10);

  // Rotate CCW until robot centered to new line segment
  linePos = readSensorLine(sensor_values);

  while (linePos != CENTER_EDGE_READING) {
    if (linePos <= CENTER_EDGE_READING) error = 20;
    else error = linePos - CENTER_EDGE_READING;

    rightMotorSpeed = baseSpeed + (error * 10);
    leftMotorSpeed = baseSpeed - (error * 10);
    motorWrite(leftMotorSpeed, rightMotorSpeed);
    delay(10);
    linePos = readSensorLine(sensor_values);
  }
  motorStop();

  // Now go forward until robot meet the main line
  linePos = readSensorLine(sensor_values);
  while (leftEnd != 1 && rightEnd != 1) {
    lineFollow(linePos);
    delay(10);
    linePos = readSensorLine(sensor_values);
  }

  motorWrite(150, 150);
  delay(100);
  motorStop();
}


void alignToPath(int dir) {

  // Rotate CCW/CW until middle sensor left line
  linePos = readSensorLine(sensor_values);

  // Away from line before take the turn
  if (allOut == false) {
    motorWrite(150, 150);
    delay(10);
    linePos = readSensorLine(sensor_values);
  }
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
    rightMotorSpeed = baseSpeed / 2 + (error * 10);
    leftMotorSpeed = baseSpeed / 2 - (error * 10);

    motorWrite(leftMotorSpeed, rightMotorSpeed);
    delay(10);
  }

  motorStop();

}


int detectShelf(int i) {

  int  s = readIR();
  int t = 0;
  
  if (s == 0) {
    // 0x0 NoBox
    Serial.println("0x0 NoBox");
    t = 0;

  } else if (s == 1) {      // 0001
    // 3x3 NoBox
    Serial.println("3x3 NoBox");
    t = 3;

  } else if (s == 11) {     // 0011 -> Take Box 0
    // 0x0 Box || 5x5 NoBox
    Serial.println("0x0 Box || 5x5 NoBox ");
    t = 5;

  } else if (s == 111) {    // 0111 -> Take Box 3
    // 3x3 Box
    Serial.println("3x3 Box");
    t = 13;

  } else if (s == 1111) {   // 1111 -> Take Box 5
    // 5x5 Box
    Serial.println("5x5 Box");
    t = 15;

  } else {
    Serial.println(s);
    t = 99;
  }
  return t;
}

