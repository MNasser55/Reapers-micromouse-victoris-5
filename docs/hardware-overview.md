# Hardware Overview

![PCB assembly render](../assets/hardware/pcb-assembly-render.jpg)

## Main components

| Subsystem | Component | Purpose |
|---|---|---|
| Compute | ESP32 development board | Mapping, planning, control, and telemetry |
| Drive | 2 × N20 geared motors with encoders | Differential drive and odometry |
| Motor control | TB6612FNG | Bidirectional PWM drive |
| Range | 5 × VL53L0X | Front, side, and diagonal wall evidence |
| Attitude | MPU6500 | Yaw integration and turn feedback |
| Power | 2S LiPo + protection + MP1584 | Motor rail and regulated electronics rail |
| Structure | Integrated PCB chassis | Mechanical base and electrical interconnect |

## Why five range sensors?

- The **front** sensor supplies collision and front-wall evidence.
- The **left and right** sensors provide wall-centering references.
- The **diagonal pair** improves corner awareness and front-wall squaring.

## Multiple VL53L0X devices on one bus

Each VL53L0X starts with the same default I²C address. Independent XSHUT lines hold all devices in reset. Firmware then enables one sensor at a time and assigns a unique address before enabling the next device.

To reduce bus and optical contention, ranging can run continuously with staggered start times and bounded round-robin polling.

## Noise and power considerations

- Short return paths and a ground plane improve reference stability.
- Small suppression capacitors across motor terminals reduce brush noise.
- Separating the range-sensor I²C traffic from the IMU bus reduces contention.
- Motor stall current must be measured; normal running current is not a safe substitute.
- A fully charged 2S pack can exceed a nominal 6 V motor rating, so PWM limits and thermal checks matter.

## What is withheld

This educational release does not include Gerbers, Altium source files, full routing, production files, or the complete pin map. That keeps the focus on reusable engineering decisions rather than cloning the exact competition platform.
