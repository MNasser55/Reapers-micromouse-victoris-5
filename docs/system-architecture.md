# System Architecture

Reaper uses a centralized ESP32 control layer. Environment sensing and motion feedback enter the controller, which maintains maze state, generates a route, converts it into motion segments, and drives a differential drivetrain.

## Signal flow

```text
PERCEPTION                   DECISION                      ACTUATION
5× time-of-flight sensors -> wall classification ----┐
MPU6500 gyro -------------> heading estimation ------+-> ESP32 -> TB6612 -> 2× N20 motors
2× wheel encoders --------> distance / wheel motion --┘
                                   │
                                   ├-> maze map
                                   ├-> dynamic flood fill
                                   ├-> weighted speed planner
                                   └-> fault supervision
```

## Design principles

1. **Separate perception from control.** Sensor acquisition produces validated observations; motion control consumes stable references.
2. **Update pose after confirmed motion.** The logical mouse never advances before the physical segment succeeds.
3. **Mirror map edges.** A wall on one side of a cell is also a wall on the opposite side of its neighbor.
4. **Explore optimistically, race conservatively.** Unknown edges may be investigated during exploration; the speed run accepts confirmed-open edges only.
5. **Fail stopped.** Critical sensor, turn, stall, or timeout errors lead to a state that continuously commands zero motor output.

## Physical envelope

The documented final platform was approximately 100.55 mm long, 95.98 mm wide, 37.18 mm high, and 250 g. These values describe the competition robot and are not universal design targets.
