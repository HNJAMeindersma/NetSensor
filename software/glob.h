// Analog states
#define inputAnalogStateShort       0
#define inputAnalogStateNormal      1
#define inputAnalogStateTamper      2
#define inputAnalogStateAlarm       3
#define inputAnalogStateAlarmTamper 4
#define inputAnalogStateCut         5
#define inputAnalogStateUnknown     6

// Analog state ranges
struct inputAnalogRange {
        int     sensor_state;
  const char*   label;
        int     range_bottom;
        int     range_optimum;
        int     range_top;
};

// Analog input list format
struct inputAnalogArray {
  const String  label;
        byte    analog_input;
  const String  type;
  const char*   topic;
        byte    last_state;
};

// Digital states
#define inputDigitalStateUnknown "unknown"

// Digital input list format
struct inputDigitalArray {
  const String  label;
        byte    digital_input;
  const String  type;
  const char*   topic;
  const char*   state_high;
  const char*   state_low;
        char*   last_state;
};
