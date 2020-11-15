// Check MQTT connection
bool mqttConnection() {

  // Only execute on error
  if(mqttClient.connected() != true || mqttClient.state() != MQTT_CONNECTED) {

    // Display update
    if(systemSerialOutput) {
      Serial.println("[MQTT] connecting to MQTT as client '" + String(mqttClientHost) + "' to broker '" + String(mqttServerHost) + "'...");
    }

    // Try (re)connect
    if(mqttClient.connect(mqttClientHost)) {

      // MQTT connected
      if(systemSerialOutput) {
        Serial.println("[MQTT] successfully connected to MQTT!");
      }
      return true;

    } else {

      // Display error
      if(systemSerialOutput) {
        Serial.print("[MQTT] failed to connect");
        if(mqttClient.state() == MQTT_CONNECTION_TIMEOUT) {
          Serial.print(": connection timeout");
        } else if(mqttClient.state() == MQTT_CONNECTION_LOST) {
          Serial.print(": connection lost");
        } else if(mqttClient.state() == MQTT_CONNECT_FAILED) {
          Serial.print(": connection failed");
        } else if(mqttClient.state() == MQTT_DISCONNECTED) {
          Serial.print(": client disconnected");
        } else if(mqttClient.state() == MQTT_CONNECT_BAD_PROTOCOL) {
          Serial.print(": unsupported protocol");
        } else if(mqttClient.state() == MQTT_CONNECT_BAD_CLIENT_ID) {
          Serial.print(": rejected client identifier");
        } else if(mqttClient.state() == MQTT_CONNECT_UNAVAILABLE) {
          Serial.print(": connection unavailable");
        } else if(mqttClient.state() == MQTT_CONNECT_BAD_CREDENTIALS) {
          Serial.print(": rejected credentials");
        } else if(mqttClient.state() == MQTT_CONNECT_UNAUTHORIZED) {
          Serial.print(": client unauthorized");
        }
        Serial.println("!");
      }
      return false;

    }

  } else {

    return true;

  }

}

// Publish MQTT message
bool mqttPublish(char* topic, char* payload, bool retain = false, char* subject = "unknown") {

  int retries = 0;
  bool sended = false;

  // Retry loop
  while(retries < mqttRetries && sended != true) {

    // Check MQTT connection
    while(mqttConnection() != true) {
      delay(500);
    }

    // Publish MQTT message
    if(mqttClient.publish(topic, payload, retain)) {
      if(systemSerialOutput) {
        Serial.println("[MQTT] successfully published '" + String(subject) + "' (attempt " + (retries + 1) + ")");
      }
      sended = true;
      break;
    } else {
      if(systemSerialOutput) {
        Serial.println("[MQTT] failed to publish '" + String(subject) + "' (attempt " + (retries + 1) + ")");
      }
    }

    // Retry timeout
    retries++;
    delay(250);

  }

  // Return
  if(sended) {
    return true;
  } else {
    if(systemSerialOutput) {
      Serial.println("[MQTT] dropped publication of '" + String(subject) + "' after " + retries + " attempts");
    }
    return false;
  }

}

// MQTT heartbeat
unsigned long mqttHeartbeatLast;
void mqttHeartbeat() {

  // Only execute if MQTT heartbeat is enabled
  if(mqttHeartbeatEnable == true) {

    // Reset last heartbeat after overflow
    if(mqttHeartbeatLast > millis()) {
      mqttHeartbeatLast = millis();
      if(systemSerialOutput) {
        Serial.println("[MQTT] reset last heartbeat timer due to overflow");
      }
    }

    // Periodic execution
    if(millis() > (mqttHeartbeatLast + (mqttHeartbeatTime * 1000))) {

      // Compose heartbeat topic
      String messageTopicString = "";
      messageTopicString += "tele/";
      messageTopicString += mqttClientHost;
      messageTopicString += "/STATE";
      char* messageTopic = messageTopicString.c_str();

      // Compose heartbeat payload
      String messagePayloadString = "";
      messagePayloadString += "{";
      messagePayloadString += "\"UptimeSec\":";
      messagePayloadString += (millis() / 1000);
      messagePayloadString += ",";
      messagePayloadString += "\"MAC\":\"";
      messagePayloadString += String(ethernetMAC[0], HEX);
      messagePayloadString += ":";
      messagePayloadString += String(ethernetMAC[1], HEX);
      messagePayloadString += ":";
      messagePayloadString += String(ethernetMAC[2], HEX);
      messagePayloadString += ":";
      messagePayloadString += String(ethernetMAC[3], HEX);
      messagePayloadString += ":";
      messagePayloadString += String(ethernetMAC[4], HEX);
      messagePayloadString += ":";
      messagePayloadString += String(ethernetMAC[5], HEX);
      messagePayloadString += "\",";
      messagePayloadString += "\"Hostname\":\"";
      messagePayloadString += mqttClientHost;
      messagePayloadString += "\",";
      messagePayloadString += "\"Version\":\"";
      messagePayloadString += systemVersion;
      messagePayloadString += "\",";
      messagePayloadString += "\"Broker\":\"";
      messagePayloadString += mqttServerHost;
      messagePayloadString += "\",";
      if(systemSerialOutput == true) {
        messagePayloadString += "\"Serial\":true,";
      } else {
        messagePayloadString += "\"Serial\":false,";
      }
      if((sizeof(inputAnalogList) / sizeof(inputAnalogList[0])) > 0) {
        messagePayloadString += "\"Analog\":{";
        for(byte inputAnalogSensorId = 0; inputAnalogSensorId < (sizeof(inputAnalogList) / sizeof(inputAnalogList[0])); inputAnalogSensorId++) {
          messagePayloadString += "\"";
          messagePayloadString += inputAnalogList[inputAnalogSensorId].topic;
          messagePayloadString += "\":\"";
          messagePayloadString += inputAnalogList[inputAnalogSensorId].last_state;
          messagePayloadString += "\"";
          if((inputAnalogSensorId + 1) < (sizeof(inputAnalogList) / sizeof(inputAnalogList[0]))) {
            messagePayloadString += ",";
          }
        }
        messagePayloadString += "},";
      }
      if((sizeof(inputDigitalList) / sizeof(inputDigitalList[0])) > 0) {
        messagePayloadString += "\"Digital\":{";
        for(byte inputDigitalSensorId = 0; inputDigitalSensorId < (sizeof(inputDigitalList) / sizeof(inputDigitalList[0])); inputDigitalSensorId++) {
          messagePayloadString += "\"";
          messagePayloadString += inputDigitalList[inputDigitalSensorId].topic;
          messagePayloadString += "\":\"";
          messagePayloadString += inputDigitalList[inputDigitalSensorId].last_state;
          messagePayloadString += "\"";
          if((inputDigitalSensorId + 1) < (sizeof(inputDigitalList) / sizeof(inputDigitalList[0]))) {
            messagePayloadString += ",";
          }
        }
        messagePayloadString += "},";
      }
      messagePayloadString += "\"Message\":\"heartbeat\"";
      messagePayloadString += "}";
      char* messagePayload = messagePayloadString.c_str();

      // Send MQTT heartbeat
      mqttPublish(messageTopic, messagePayload, false, "heartbeat");

      // Set last heartbeat
      mqttHeartbeatLast = millis();

    }

  }

}

// Setup MQTT
void setupMQTT() {

  // MQTT settings
  mqttClient.setClient(ethernetClient);
  mqttClient.setServer(mqttServerHost, mqttServerPort);   
  mqttClient.setKeepAlive(mqttKeepAlive);
  mqttClient.setSocketTimeout(mqttSocketTimeout);

  // Try MQTT connection
  if(mqttConnection()) {
    mqttHeartbeatLast = millis();
  }

}
