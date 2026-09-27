# Firmware Architecture

The competition project used C++ with PlatformIO and the Arduino framework. The firmware was divided by responsibility rather than written as one monolithic loop.

## Modules

| Area | Responsibility |
|---|---|
| Run supervision | Start handling, phases, telemetry, and fault transitions |
| I²C buses | Independent range-sensor and IMU communication |
| Sensors | Startup, unique addressing, non-blocking polling, filtering, and wall decisions |
| Maze | Map storage, flood fill, direction choice, and weighted planning |
| Cell motion | Distance profile, braking, front correction, trim, and recovery |
| Steering | Wall centering combined with gyro heading hold |
| Encoders | Interrupt counting, speed sampling, and odometry |
| IMU | Bias calibration, yaw integration, and closed-loop turns |
| Diagnostics | Front-wall squaring and development telemetry |
| Motors | Direction and PWM output |

## Run-state model

```text
WAIT_EXPLORE
    ↓
EXPLORE_COUNTDOWN
    ↓
EXPLORE ───────────> FAULT
    ↓
REACHED
    ↓ operator returns mouse to start
SPEED_COUNTDOWN
    ↓
SPEED
    ↓
DONE
```

A critical failure can transition to `FAULT` from any active phase. The fault state maintains zero motor output rather than stopping only once.

## Event-driven loop

The controller avoids long blocking delays during normal operation. Each loop iteration services bounded work:

1. poll a limited number of sensors,
2. integrate gyro and encoder updates,
3. update the active motion controller,
4. supervise deadlines and safety conditions,
5. emit optional development telemetry.

This keeps sensing, control, and safety responsive even when several peripherals share processor time.
