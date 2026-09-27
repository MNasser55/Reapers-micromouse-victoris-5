/*
  Educational pattern: assigning unique addresses to identical VL53L0X sensors.
  Hardware pins and addresses are placeholders, not Reaper's production mapping.
*/
#include <Arduino.h>

struct SensorSlot {
  uint8_t xshutPin;
  uint8_t newAddress;
};

SensorSlot sensors[] = {
  {2,  0x30},
  {15, 0x31},
  {16, 0x32},
  {17, 0x33},
  {18, 0x34}
};

void holdAllSensorsInReset() {
  for (auto &sensor : sensors) {
    pinMode(sensor.xshutPin, OUTPUT);
    digitalWrite(sensor.xshutPin, LOW);
  }
  delay(10);
}

bool enableAndAddressOneSensor(size_t index) {
  digitalWrite(sensors[index].xshutPin, HIGH);
  delay(10);

  // Replace these comments with calls from your VL53L0X library:
  // if (!devices[index].begin(DEFAULT_ADDRESS)) return false;
  // devices[index].setAddress(sensors[index].newAddress);
  return true;
}

bool initializeSensorArray() {
  holdAllSensorsInReset();

  for (size_t i = 0; i < sizeof(sensors) / sizeof(sensors[0]); ++i) {
    if (!enableAndAddressOneSensor(i)) return false;
  }
  return true;
}
