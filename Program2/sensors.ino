
// ---- Sonar Sensor Functions -----------------------------------------------------------------------

void sonarBegin() {

  /*Serial.println(">> ColorSensor : Begin");
    for (int i = 0; i < 3; i++) {
    pinMode(trigger[i], OUTPUT);
    pinMode(echo[i], INPUT);
    digitalWrite(trigger[i], LOW);
    }*/
}

int getDistance(int sensor) {

  /*digitalWrite(trigger[sensor], HIGH);
    delayMicroseconds(20);
    digitalWrite(trigger[sensor], LOW);

    duration = pulseIn(echo[sensor], HIGH, 30000);
    distance = duration / 58;

    if (distance > maxDistance) {
    distance = maxDistance;
    }
    return distance;*/
}

