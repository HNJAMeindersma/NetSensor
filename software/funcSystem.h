// System restart
void(* systemRestartNow) (void) = 0;
void systemRestart() {

  // Notify
  if(systemSerialOutput) {
    Serial.println("[SYST] Restarting...");
  }

  // Wait
  delay(systemRestartWait);

  // Restart
  systemRestartNow();

}

// System LED blink
unsigned long systemBlinkLast;
void systemBlink() {

  // Reset last blink after overflow
  if(systemBlinkLast > millis()) {
    systemBlinkLast = millis();
    if(systemSerialOutput) {
      Serial.println("[SYST] reset last blink timer due to overflow");
    }
  }

  // Periodic execution
  if(millis() > (systemBlinkLast + systemBlinkTime)) {

    // Alternate blink
    if(digitalRead(LED_BUILTIN) == LOW) {
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }

    // Set last blink
    systemBlinkLast = millis();

  }

}

// Setup System
void setupSystem() {

  // Pin modes
  pinMode(LED_BUILTIN, OUTPUT);

  // Serial output
  if(systemSerialOutput) {
    Serial.begin(systemSerialBaud);
    delay(250);
    Serial.println("[INFO] " + String(systemTitle) + " version " + String(systemVersion));
  }

}
