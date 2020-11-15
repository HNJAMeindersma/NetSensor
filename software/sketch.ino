// Load global variables
#include "glob.h"
#include "conf.h"

// Load libraries
#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Initiate libraries
EthernetClient ethernetClient;
PubSubClient mqttClient;

// Load functions
#include "funcSystem.h"
#include "funcEthernet.h"
#include "funcMQTT.h"
#include "funcInput.h"

// Setup
void setup() {

  // System
  setupSystem();

  // Ethernet
  setupEthernet();

  // MQTT
  setupMQTT();

  // Input
  setupInput();

}

// Loop
void loop() {

  // System LED blink
  systemBlink();

  // Check ethernet connection
  ethernetConnection();

  // Renew ethernet DHCP
  ethernetDHCP();

  // Send MQTT heartbeat
  mqttHeartbeat();

  // Read analog inputs
  inputAnalog();

  // Read digital inputs
  inputDigital();

}
