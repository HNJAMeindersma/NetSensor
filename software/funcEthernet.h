// Check ethernet connection
void ethernetConnection() {

  // Check ethernet hardware and link status
  if(Ethernet.linkStatus() != LinkON) {

    // Display information
    if(systemSerialOutput) {
      Serial.print("[ETHR] failed to connect to ethernet");
      if(Ethernet.hardwareStatus() == EthernetNoHardware) {
        Serial.print(": hardware disconnected");
      } else if(Ethernet.linkStatus() == LinkOFF) {
        Serial.print(": link offline");
      } else if(Ethernet.linkStatus() == Unknown) {
        Serial.print(": link status unknown");
      }
      Serial.println("!");
    }

    // Restart system
    systemRestart();

  }

}

// Renew ethernet DHCP lease
unsigned long ethernetDHCPlast;
void ethernetDHCP() {

  // Reset last DHCP renew after overflow
  if(ethernetDHCPlast > millis()) {
    ethernetDHCPlast = millis();
    if(systemSerialOutput) {
      Serial.println("[DHCP] reset last DHCP lease timer due to overflow");
    }
  }

  // Periodic execution
  if(millis() > (ethernetDHCPlast + ethernetDHCPtime)) {

    // Try ethernet DHCP renew
    byte ethernetDHCPresult = Ethernet.maintain();
    if(systemSerialOutput) {
      if(ethernetDHCPresult == 0) {
        Serial.println("[DHCP] lease does not require updating");
      } else if(ethernetDHCPresult == 1) {
        Serial.println("[DHCP] lease renew failed");
      } else if(ethernetDHCPresult == 2) {
        Serial.println("[DHCP] lease renewed successfully");
      } else if(ethernetDHCPresult == 3) {
        Serial.println("[DHCP] lease rebind failed");
      } else if(ethernetDHCPresult == 4) {
        Serial.println("[DHCP] lease rebinded successfully");
      }
    }

    // Set last DHCP renew
    ethernetDHCPlast = millis();

  }

}

// Setup ethernet
void setupEthernet() {

  if(systemSerialOutput) {
    Serial.print("[ETHR] connecting to ethernet with MAC '");
    Serial.print(String(ethernetMAC[0], HEX) + ":");
    Serial.print(String(ethernetMAC[1], HEX) + ":");
    Serial.print(String(ethernetMAC[2], HEX) + ":");
    Serial.print(String(ethernetMAC[3], HEX) + ":");
    Serial.print(String(ethernetMAC[4], HEX) + ":");
    Serial.print(String(ethernetMAC[5], HEX));
    Serial.println("'...");
  }
  Ethernet.init(ethernetPin);
  delay(250);
  if(Ethernet.begin(ethernetMAC)) {

    // Ethernet settings
    Ethernet.setRetransmissionCount(ethernetRetryCount);
    Ethernet.setRetransmissionTimeout(ethernetRetryTimeout);
    ethernetDHCPlast = millis();

    // Display information
    if(systemSerialOutput) {
      Serial.println("[ETHR] successfully connected to ethernet!");
      if(false) {
        Serial.print("  Local IP:    ");
        Serial.println(Ethernet.localIP());
        Serial.print("  Subnet mask: ");
        Serial.println(Ethernet.subnetMask());
        Serial.print("  Gateway IP:  ");
        Serial.println(Ethernet.gatewayIP());
        Serial.print("  DNS server:  ");
        Serial.println(Ethernet.dnsServerIP());
      }
    }

  } else {

    // Check ethernet problem
    ethernetConnection();

  }

}
