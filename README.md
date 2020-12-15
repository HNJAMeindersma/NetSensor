# NetSensor
NetSensor is an __Arduino__-based analog and digital sensor reader with with __Ethernet__ connectivity through the __WizNet W5500__ (or similar). Combined with the designed mainboard it can read the status of __4 analog__ and __4 digital__ sensors. And relay their status to a __MQTT__ broker. It also sends out a 'heartbeat' status update in regular interfalls.

### Software
The software was designed with constant operability in mind. In the case of ethernet hardware or link problems the system will restart to try to regain connectivity. The system will try to resend a MQTT message that was not confirmed to be send correctly. This approach tries to mitigate the chance of lost messages as much as possible.

A configuration array makes it easy to add, remove or change any new sensors to the system. It is optional for the user to define all analog and digital ports and ignore any messages from unused ports. Or to remove unused sensor ports from the configuration to lower system load and network traffic.

### Hardware
The hardware design of the main board is currently in prototype-stage. It consists of the basic components to distribute power and read the sensors. RJ45 connectors were chosen for easy and cheap connectivity to the board. The connector pins are mirrored to limitate orientation problems. __Please keep in mind that currently no protection circuitry is applied in the schematic!__

##### RJ45 pinout
- +12V
- +5V
- GND
- Sense +/-
- Sense -/+
- GND
- +5V
- +12V

It is recommended to use cables with the exact amount of conductors you plan to use on the other end. Or, when using Cat5/6 twisted pairs, to use pairs with the same signal on the mirrored side.

##### Schematics
![Schematics](https://raw.githubusercontent.com/HNJAMeindersma/NetSensor/main/hardware/schematic.svg "Schematics")

### Credits
Special thanks to Jonathan Oxer of [SuperHouse](https://www.superhouse.tv/) for part of the [code](https://github.com/SuperHouse/SecuritySensor4ToMQTT) for the analog sensors

Also thanks to Nick O'Leary for his [MQTT library](https://pubsubclient.knolleary.net/) on Arduino ([GitHub](https://github.com/knolleary/pubsubclient))
