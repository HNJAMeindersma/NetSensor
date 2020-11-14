// Read analog sensors
void inputAnalog() {

  // Loop through analog inputs
  for(byte inputAnalogSensorId = 0; inputAnalogSensorId < (sizeof(inputAnalogList) / sizeof(inputAnalogList[0])); inputAnalogSensorId++) {

    // Read sensor state
    byte inputAnalogSensorState = inputAnalogStateUnknown;
    int inputAnalogSensorReading = analogRead(inputAnalogList[inputAnalogSensorId].analog_input);

    // Compare sensor state ranges
    if((inputAnalogSensorReading >= inputAnalogRanges[inputAnalogStateShort].range_bottom)              &&  (inputAnalogSensorReading <= inputAnalogRanges[inputAnalogStateShort].range_top)) {
      inputAnalogSensorState = inputAnalogStateShort;
    } else if((inputAnalogSensorReading >= inputAnalogRanges[inputAnalogStateNormal].range_bottom)      &&  (inputAnalogSensorReading <= inputAnalogRanges[inputAnalogStateNormal].range_top)) {
      inputAnalogSensorState = inputAnalogStateNormal;
    } else if((inputAnalogSensorReading >= inputAnalogRanges[inputAnalogStateTamper].range_bottom)      &&  (inputAnalogSensorReading <= inputAnalogRanges[inputAnalogStateTamper].range_top)) {
      inputAnalogSensorState = inputAnalogStateTamper;
    } else if((inputAnalogSensorReading >= inputAnalogRanges[inputAnalogStateAlarm].range_bottom)       &&  (inputAnalogSensorReading <= inputAnalogRanges[inputAnalogStateAlarm].range_top)) {
      inputAnalogSensorState = inputAnalogStateAlarm;
    } else if((inputAnalogSensorReading >= inputAnalogRanges[inputAnalogStateAlarmTamper].range_bottom) &&  (inputAnalogSensorReading <= inputAnalogRanges[inputAnalogStateAlarmTamper].range_top)) {
      inputAnalogSensorState = inputAnalogStateAlarmTamper;
    } else if((inputAnalogSensorReading >= inputAnalogRanges[inputAnalogStateCut].range_bottom)         &&  (inputAnalogSensorReading <= inputAnalogRanges[inputAnalogStateCut].range_top)) {
      inputAnalogSensorState = inputAnalogStateCut;
    } else {
      inputAnalogSensorState = inputAnalogStateUnknown;
    }

    // Execute when sensor state changed
    if(inputAnalogSensorState != inputAnalogList[inputAnalogSensorId].last_state) {

      // Publish change
      if(serialOutput) {
        Serial.println("[INPT] analog input '" + inputAnalogList[inputAnalogSensorId].label + "' (" + inputAnalogList[inputAnalogSensorId].type + ") changed from '" + inputAnalogRanges[inputAnalogList[inputAnalogSensorId].last_state].label + "' to '" + inputAnalogRanges[inputAnalogSensorState].label + "'");
      }
      mqttPublish(inputAnalogList[inputAnalogSensorId].topic, inputAnalogRanges[inputAnalogSensorState].label, false, "analog input");

      // Reset last state
      inputAnalogList[inputAnalogSensorId].last_state = inputAnalogSensorState;

    }

  }

}

// Read digital sensors
void inputDigital() {

  // Loop through digital inputs
  for(byte inputDigitalSensorId = 0; inputDigitalSensorId < (sizeof(inputDigitalList) / sizeof(inputDigitalList[0])); inputDigitalSensorId++) {

    // Read sensor state
    char* inputDigitalSensorState = inputDigitalStateUnknown;
    int inputDigitalSensorReading = digitalRead(inputDigitalList[inputDigitalSensorId].digital_input);

    // Get sensor state
    if(inputDigitalSensorReading == HIGH) {
      inputDigitalSensorState = inputDigitalList[inputDigitalSensorId].state_high;
    } else {
      inputDigitalSensorState = inputDigitalList[inputDigitalSensorId].state_low;
    }

    // Execute when sensor state changed
    if(inputDigitalSensorState != inputDigitalList[inputDigitalSensorId].last_state) {

      // Publish change
      if(serialOutput) {
        Serial.println("[INPT] digital input '" + inputDigitalList[inputDigitalSensorId].label + "' (" + inputDigitalList[inputDigitalSensorId].type + ") changed from '" + inputDigitalList[inputDigitalSensorId].last_state + "' to '" + inputDigitalSensorState + "'");
      }
      mqttPublish(inputDigitalList[inputDigitalSensorId].topic, inputDigitalSensorState, false, "digital input");

      // Reset last state
      inputDigitalList[inputDigitalSensorId].last_state = inputDigitalSensorState;

    }

  }

}

// Setup Input
void setupInput() {

  // Pin modes
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

}
