/****************************************************************************
  Functions

  void    irSensorsBegin, sonarBegin, irSensorsOutput
  array   readLine(*sensorValues)
  String  readLineString
  int     getSonarDistance
****************************************************************************/

void irSensorsBegin() {

  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(irPins[i], INPUT);
  }
  Serial.println(F(">> IRSensors : Begin..."));

}


int readSensorLine(unsigned int *sensor_values) {
  delay(10);

  weight = 0;
  sum = 0;
  irLineString = "";

  for (int i = 0; i < NUM_SENSORS; i++) {
    value = irSensorRead(i);

    sensor_values[i] = value;
    weight += value * (i * 10);
    sum += value;
    irLineString = (String)value + " " + irLineString;
  }

  allOut = (sum == 0) ? true : false;
  allIn  = (sum == NUM_SENSORS) ? true : false;

  leftEnd = sensor_values[NUM_SENSORS - 1];
  rightEnd = sensor_values[0];

  if (allOut)
  {
    if ((lastReading > RIGHT_EDGE_READING) && (CENTER_EDGE_READING - 10 > lastReading )) {        // <---***>
      lastReading = RIGHT_EDGE_READING;

    } else if ((LEFT_EDGE_READING > lastReading) && ( lastReading  > CENTER_EDGE_READING) + 10) { // <***--->
      lastReading = LEFT_EDGE_READING;

    } else if (lastReading == CENTER_EDGE_READING) {                                       // <--**-->
      lastReading = CENTER_EDGE_READING;
    }
  } else {
    lastReading = weight / sum;
  }
  //if (0)Serial.print(">> IR : "); Serial.println(irLineString);

  // Left-most and right-most sensors
  return lastReading;
}


int irSensorRead(int num) {
  int reading = analogRead(irPins[num]);

  reading = (reading > 512);
  if (lineType == WHITE) reading = 1 - reading;

  //reading = reading; //BLACK=0, WHITE=1
  return reading;
}


#if defined(SONAR_SENSORS)

void sonarBegin() {

  Serial.println(">> Sonar : Begin");

  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  digitalWrite(PIN_TRIGGER, LOW); * /
}

int getSonarDistance() {

  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(20);
  digitalWrite(PIN_TRIGGER, LOW);

  duration = pulseIn(PIN_ECHO, HIGH, 30000);
  distance = duration / 58;

  if (distance > maxDistance) {
    //distance = maxDistance;
  }
  return distance;
}
#endif



int readIR() {
  int x = wire_write('I');

  frontSensor[0] = x % 2;
  frontSensor[1] = (x / 2) % 2;
  frontSensor[2] = (x / 4) % 2;
  frontSensor[3] = (x / 8) % 2;

  if (debug) {
    Serial.print(">> Front Sensors : ");
    Serial.print(frontSensor[0]);
    Serial.print(frontSensor[1]);
    Serial.println(frontSensor[2]);
    Serial.println(frontSensor[3]);
  }

  return frontSensor[3] * 1000 +  frontSensor[2] * 100 + frontSensor[1] * 10 + frontSensor[0];
}


