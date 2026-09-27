# Common Mistakes

## Starting with the full maze

A full run combines power, sensing, odometry, control, mapping, and planning. When it fails, the cause is unclear. Validate each subsystem first.

## Using delays as motion control

A fixed delay changes with battery voltage, floor friction, wheel wear, and motor temperature. Use encoder and gyro feedback with timeouts.

## Updating pose before motion finishes

If a cell move stalls but the map advances, all later wall observations are written into the wrong cells. Update logical pose only after successful physical completion.

## Treating unknown as open during the speed run

Optimistic exploration is useful, but racing through an unmeasured edge can cause a collision. Speed planning should accept confirmed-open edges only.

## Storing walls without storing known edges

A cleared wall bit can mean either open or unmeasured. Maintain a separate known-edge mask.

## Forgetting mirrored edges

A wall east of one cell is the same physical wall as the west wall of its neighbor. Update both sides together.

## Copying PID gains

Controller gains depend on motor, mass, wheel diameter, supply voltage, loop rate, and floor. Copying values can make the robot unstable.

## Integrating gyro drift forever

Calibrate bias while stationary, use bounded turns, and take advantage of trustworthy geometric corrections such as front-wall squaring.

## Enabling all VL53L0X sensors together

Identical sensors boot at the same I²C address. Use independent XSHUT lines and assign addresses sequentially.

## Ignoring stale sensor data

A plausible old measurement is still wrong for the current position. Track freshness separately from numeric validity.

## Tuning software around a hardware fault

Large wheel trim, frequent resets, or unstable sensor readings can indicate friction, loose wiring, poor grounding, noise, or inadequate power—not bad code.

## Increasing speed before repeatability

A single successful run is not calibration. Increase speed only after repeated low-speed tests show small spread and safe stopping.

## Publishing unverified numbers

Separate estimates, simulated behavior, implemented features, and measured results. Do not report a run time or accuracy figure without evidence.
