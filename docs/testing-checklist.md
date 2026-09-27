# Testing Checklist

Do not proceed to the next group until the current group is repeatable.

## Electrical safety

- [ ] Battery polarity verified
- [ ] Regulated rail measured before connecting the MCU
- [ ] Common ground verified
- [ ] Motor stall current measured
- [ ] Driver, wiring, connector, and protection ratings checked
- [ ] Emergency stop tested physically
- [ ] No component overheats during a sustained motor test

## Motors and encoders

- [ ] Left motor forward/backward direction correct
- [ ] Right motor forward/backward direction correct
- [ ] Encoder signs match forward motion
- [ ] Counts are stable when wheels are stationary
- [ ] Ten repeated wheel rotations give similar counts
- [ ] Stall detection stops motion

## IMU and turns

- [ ] Stationary bias calibration is repeatable
- [ ] Clockwise/counter-clockwise signs are correct
- [ ] Ten right 90° turns tested
- [ ] Ten left 90° turns tested
- [ ] Ten 180° turns tested
- [ ] Turn timeout tested
- [ ] No false completion while angular rate is high

## Range sensors

- [ ] Every sensor receives a unique address
- [ ] Cold boot is reliable
- [ ] Invalid readings are rejected
- [ ] Stale data is detected
- [ ] Wall decisions tested under different lighting
- [ ] Side and diagonal sensors tested independently
- [ ] Front emergency stop tested at several speeds

## Straight motion

- [ ] Ten one-cell runs in open space
- [ ] Ten multi-cell runs in open space
- [ ] One-wall corridor test
- [ ] Two-wall corridor test
- [ ] No-wall gyro-hold test
- [ ] Transition between wall-reference modes tested
- [ ] High- and low-battery tests completed

## Mapping

- [ ] Outer boundaries initialized correctly
- [ ] Edge updates mirrored to neighboring cells
- [ ] Unknown, open, and wall states remain distinct
- [ ] Pose updates only after successful motion
- [ ] Dead ends handled
- [ ] Loops handled
- [ ] Four center cells recognized

## Planning

- [ ] Flood fill reaches the center in simulation
- [ ] Direction tie-breaking is deterministic
- [ ] Speed planner rejects unknown edges
- [ ] Turn costs affect route choice
- [ ] Path backtracking verified
- [ ] Straight directions compressed into segments
- [ ] No-route case enters a safe failure state

## Full run

- [ ] Small-maze exploration completed repeatedly
- [ ] Full-maze simulation completed
- [ ] Physical exploration reaches the center
- [ ] Map retained between attempts
- [ ] Pose reset verified before speed run
- [ ] Speed run starts at conservative speed
- [ ] Fault state maintains zero motor output
- [ ] Debug interfaces disabled or accepted by the event rules
