/*
  Adapted from Team Reapers' competition firmware.
  Production pins, addresses, timing values, and diagnostics are omitted.
*/
#include <Arduino.h>
#include <Adafruit_VL53L0X.h>

static constexpr size_t SENSOR_TOTAL = 5;
static Adafruit_VL53L0X sensors[SENSOR_TOTAL];

// Replace with pins and addresses validated for your own board.
static const uint8_t xshutPins[SENSOR_TOTAL] = {PIN_1, PIN_2, PIN_3, PIN_4, PIN_5};
static const uint8_t uniqueAddresses[SENSOR_TOTAL] = {0x30, 0x31, 0x32, 0x33, 0x34};

bool initializeRangeSensors(TwoWire &bus) {
  // Every VL53L0X starts at the same default address, so hold all in reset.
  for (size_t i = 0; i < SENSOR_TOTAL; ++i) {
    pinMode(xshutPins[i], OUTPUT);
    digitalWrite(xshutPins[i], LOW);
  }
  delay(STARTUP_RESET_DELAY_MS);

  // Enable and re-address one device at a time.
  for (size_t i = 0; i < SENSOR_TOTAL; ++i) {
    digitalWrite(xshutPins[i], HIGH);
    delay(SENSOR_BOOT_DELAY_MS);

    if (!sensors[i].begin(uniqueAddresses[i], false, &bus)) {
      return false;
    }
  }

  // Stagger continuous ranging to reduce simultaneous optical/bus activity.
  for (size_t i = 0; i < SENSOR_TOTAL; ++i) {
    if (!sensors[i].startRangeContinuous(RANGING_PERIOD_MS)) {
      return false;
    }
    delay(START_STAGGER_MS);
  }

  return true;
}
