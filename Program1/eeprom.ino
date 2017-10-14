

void eepromBegin() {
  loadEEPROM();
  //resetEEPROM();
}

void updateEEPROM(int address, int value) {
  EEPROM.update(address, value);
}

void saveEEPROM() {
  // saving the maze

  EEPROM.update(100 + eP , kP * 10);
  EEPROM.update(100 + eI , kI * 10);
  EEPROM.update(100 + eD , kD * 10);

  EEPROM.update(100 + eBase , baseSpeed);
  EEPROM.update(100 + eMax , maxSpeed);
  EEPROM.update(100 + eDebug , debug);

  //Layout Data
  for (int i = 0; i < 6; i++) {
    EEPROM.update(150 + i , layout[i]);
  }
}

void loadEEPROM() {

  if ((int)EEPROM.read(149) == 148) {
    //Serial.println(">> EEPROM laoded !!! ");

    // If EEPROM already has data
    kP = (float)EEPROM.read(eP + 100) / 10;
    kI = (float)EEPROM.read(eI + 100) / 10;
    kD = (float)EEPROM.read(eD + 100) / 10;

    baseSpeed = (int)EEPROM.read(eBase + 100);
    maxSpeed = (int)EEPROM.read(eMax + 100);
    Serial.println(EEPROM.read(149));

  } else {
    Serial.println(">> EEPROM Reprogrammed !!! ");
    resetEEPROM();
    //EEPROM.write(149, 148);
  }

}

void resetEEPROM() {

  EEPROM.update(149, 148);
  
  // Write with default values
  EEPROM.update(100 + eP , 20 * 10);
  EEPROM.update(100 + eI , 0);
  EEPROM.update(100 + eD , 0);

  EEPROM.update(100 + eBase , 150);
  EEPROM.update(100 + eMax , 250);
  EEPROM.update(100 + eDebug , 0);

  //Layout Data
  for (int i = 0; i < 6; i++) {
    EEPROM.update(150 + i , 10);
  }

}

void printEEPROM() {

  loadEEPROM();
  Serial.print("Kp\t:"); Serial.println(kP);
  Serial.print("Ki\t:"); Serial.println(kI);
  Serial.print("Kd\t:"); Serial.println(kD);
  Serial.print("Base\t:" ); Serial.println(baseSpeed);
  Serial.print("Max\t:"); Serial.println(maxSpeed);
  Serial.print("Debug\t:"); Serial.println(debug);
}

