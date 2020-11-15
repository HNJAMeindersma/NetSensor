// System ------------------------------------------------------------------------------- // #
const char*           systemTitle             = "NetSensor";                              // String
const char*           systemVersion           = "1.0";                                    // String
const unsigned long   systemBlinkTime         = 500;                                      // Millis
const unsigned long   systemRestartWait       = 5000;                                     // Millis
const bool            systemSerialOutput      = true;                                     // Boolean
const int             systemSerialBaud        = 9600;                                     // Number
// -------------------------------------------------------------------------------------- // #

// Ethernet ----------------------------------------------------------------------------- // #
const int             ethernetPin             = 10;                                       // Pin
const byte            ethernetMAC[]           = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };   // HEX
const int             ethernetRetryCount      = 3;                                        // Number
const unsigned long   ethernetRetryTimeout    = 100;                                      // Millis
const unsigned long   ethernetDHCPtime        = 60000;                                    // Millis
// -------------------------------------------------------------------------------------- // #

// MQTT --------------------------------------------------------------------------------- // #
const char*           mqttClientHost          = "netsensor_xxxxxx";                       // Hostname
const char*           mqttServerHost          = "mqtt";                                   // Hostname
const int             mqttServerPort          = 1883;                                     // Port
const int             mqttRetries             = 10;                                       // Number
const unsigned long   mqttKeepAlive           = 120;                                      // Seconds
const unsigned long   mqttSocketTimeout       = 10;                                       // Seconds
const bool            mqttHeartbeatEnable     = true;                                     // Boolean
const unsigned long   mqttHeartbeatTime       = 60;                                       // Seconds
// -------------------------------------------------------------------------------------- // #

// Analog ranges ------------------------------------------------------------------------ // #
const inputAnalogRange inputAnalogRanges[] {                                              // #
  { inputAnalogStateShort,        "shorted",         0,    0,  162 },                     // Ranges
  { inputAnalogStateNormal,       "normal",        163,  326,  409 },                     // Ranges
  { inputAnalogStateTamper,       "tamper",        410,  495,  551 },                     // Ranges
  { inputAnalogStateAlarm,        "alarm",         552,  609,  641 },                     // Ranges
  { inputAnalogStateAlarmTamper,  "alarm+tamper",  642,  675,  848 },                     // Ranges
  { inputAnalogStateCut,          "cut",           849, 1023, 1023 },                     // Ranges
  { inputAnalogStateUnknown,      "unknown",      1024, 1024, 1024 },                     // Ranges
};                                                                                        // #
// -------------------------------------------------------------------------------------- // #

// Analog inputs ------------------------------------------------------------------------ // #
inputAnalogArray inputAnalogList[] {                                                      // #
  { "Analog sensor 1", 0, "pir", "tele/analog/sensor1", inputAnalogStateUnknown },        // Input
  { "Analog sensor 2", 1, "pir", "tele/analog/sensor2", inputAnalogStateUnknown },        // Input
  { "Analog sensor 3", 2, "pir", "tele/analog/sensor3", inputAnalogStateUnknown },        // Input
  { "Analog sensor 4", 3, "pir", "tele/analog/sensor4", inputAnalogStateUnknown },        // Input
};                                                                                        // #
// -------------------------------------------------------------------------------------- // #

// Digital inputs --------------------------------------------------------------------------------------- // #
inputDigitalArray inputDigitalList[] {                                                                    // #
  { "Digital sensor 1", 4, "door", "tele/digital/sensor1", "closed", "open", inputDigitalStateUnknown },  // Input
  { "Digital sensor 2", 5, "door", "tele/digital/sensor2", "closed", "open", inputDigitalStateUnknown },  // Input
  { "Digital sensor 3", 6, "door", "tele/digital/sensor3", "closed", "open", inputDigitalStateUnknown },  // Input
  { "Digital sensor 4", 7, "door", "tele/digital/sensor4", "closed", "open", inputDigitalStateUnknown },  // Input
};                                                                                                        // #
// ------------------------------------------------------------------------------------------------------ // #
