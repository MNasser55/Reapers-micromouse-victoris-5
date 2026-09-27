/*
  Adapted from Team Reapers' competition firmware.
  Production GPIO numbers, debounce interval, and calibration are omitted.
*/
#include <Arduino.h>

static volatile long leftTicks = 0;
static volatile long rightTicks = 0;
static volatile uint32_t lastLeftPulseUs = 0;
static volatile uint32_t lastRightPulseUs = 0;

void IRAM_ATTR onLeftEncoderA() {
  const uint32_t now = micros();
  if (now - lastLeftPulseUs < MIN_PULSE_INTERVAL_US) return;

  lastLeftPulseUs = now;
  const bool channelB = digitalRead(LEFT_ENCODER_B_PIN);
  leftTicks += channelB ? -1 : 1;
}

void IRAM_ATTR onRightEncoderA() {
  const uint32_t now = micros();
  if (now - lastRightPulseUs < MIN_PULSE_INTERVAL_US) return;

  lastRightPulseUs = now;
  const bool channelB = digitalRead(RIGHT_ENCODER_B_PIN);
  rightTicks += channelB ? -1 : 1;
}

void readEncoderCountsAtomic(long &left, long &right) {
  noInterrupts();
  left = leftTicks;
  right = rightTicks;
  interrupts();
}

float averageCellProgress() {
  long left, right;
  readEncoderCountsAtomic(left, right);
  const float averageTicks = (abs(left) + abs(right)) * 0.5f;
  return averageTicks / CALIBRATED_TICKS_PER_CELL;
}
