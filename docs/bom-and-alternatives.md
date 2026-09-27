# BOM and Alternatives

This is a functional bill of materials, not a purchasing guarantee. Check voltage levels, current ratings, dimensions, availability, and library support before ordering.

| Function | Reaper choice | Beginner-friendly alternatives | Selection notes |
|---|---|---|---|
| Main controller | ESP32 development board | STM32 Nucleo, RP2040, Arduino-compatible MCU | Enough GPIO, timers, interrupts, memory, and I²C buses |
| Wall ranging | 5 × VL53L0X | VL53L1X or analog IR sensors | Field of view, update rate, minimum range, ambient-light behavior |
| Heading | MPU6500 | MPU6050, ICM-42688, other supported IMU | Gyro bias, noise, bus support, library quality |
| Motors | 2 × N20 geared DC motors with encoders | Similar micro gearmotors with encoders | Gear ratio, stall current, shaft, speed, encoder resolution |
| Motor driver | TB6612FNG | DRV8833 or suitable low-loss dual H-bridge | Motor voltage, continuous/peak current, voltage drop |
| Battery | 2S LiPo | Protected pack appropriate to the motors | Capacity, discharge rating, protection, charger compatibility |
| Regulation | MP1584 module | Suitable buck regulator | Input range, output current, efficiency, layout, thermal margin |
| Mechanical support | Integrated PCB chassis | Laser-cut plate or 3D-printed chassis | Rigidity, sensor alignment, center of mass, serviceability |
| Third contact | Caster/skid | Low-friction ball caster or skid | Friction, vibration, ground clearance |
| Stop control | Physical switch | Latching motor-power switch | Immediate accessibility and predictable behavior |

## Before buying

- Verify motor stall current against the driver and battery.
- Confirm whether encoder outputs need pull-ups or level shifting.
- Check whether chosen ESP32 pins are input-only or boot-strapping pins.
- Confirm all sensor boards expose XSHUT.
- Plan connector orientation and sensor alignment before PCB layout.
- Buy spare sensors, motors, connectors, and regulators for competition repairs.

## Suggested development equipment

- digital multimeter,
- bench supply with current limiting,
- soldering tools,
- logic analyzer or oscilloscope if available,
- ruler/calipers,
- repeatable test corridor,
- and a small modular maze before building a full 16×16 maze.
