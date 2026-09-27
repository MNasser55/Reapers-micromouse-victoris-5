# Calibration Guide

Calibration is a measurement process, not a collection of copied constants. Tune on the final robot, wheels, battery, surface, and sensor geometry.

## 1. Encoder distance calibration

1. Mark a straight distance equal to several maze cells.
2. Move slowly to reduce wheel slip.
3. Record left and right counts for at least ten trials.
4. Reject trials with obvious collisions or manual disturbance.
5. Use the average count per cell as the initial conversion.
6. Validate forward and reverse separately if both are used.

Prefer measuring several cells and dividing rather than calibrating from one short movement.

## 2. Wheel mismatch

Command equal PWM to both motors and log encoder speed.

- If one side is consistently faster, record the ratio.
- Fix mechanical friction before compensating in software.
- Apply only bounded trim; a large correction often indicates a hardware issue.

## 3. Gyro bias and sign

1. Keep the robot stationary.
2. Collect many Z-axis samples.
3. Compute the average bias.
4. Repeat after warm-up and at different battery levels.
5. Rotate 90° in both directions to verify sign and scale.

Recalibrate before a run only while the robot is confirmed stationary.

## 4. Turn controller

Tune at low PWM first:

1. Use proportional control to approach the target.
2. Add derivative damping if the robot overshoots or oscillates.
3. Require both low angle error and low angular rate before declaring completion.
4. Add a short settling window.
5. Enforce a hard timeout.

Test repeated right, left, and 180° turns—not only one successful turn.

## 5. Wall thresholds

For every sensor position:

1. Record readings with a wall present at expected cell positions.
2. Record readings with no wall.
3. Repeat under multiple lighting conditions and wall finishes.
4. Choose a threshold with margin between the two distributions.
5. Add hysteresis around the threshold.
6. Reject stale or invalid samples before making a wall decision.

Do not copy one threshold to every sensor automatically; geometry and mounting angle differ.

## 6. Wall-centering controller

Tune in this order:

1. Gyro-only straight motion.
2. Two-wall centering using left-minus-right error.
3. One-wall following with a measured side-distance reference.
4. Transitions between wall configurations.

Limit the maximum steering correction and reset incompatible integral/derivative history when the reference changes.

## 7. Cell-motion profile

1. Start with a low launch command.
2. Increase speed over a measured acceleration region.
3. Begin braking early.
4. Approach the target using encoder distance.
5. Use trusted front-wall range only as a final correction—not as the only odometry source.
6. Test at high and low battery voltage.

## 8. Speed-run tuning

Increase performance in small steps:

- one straight cell,
- several straight cells,
- one turn plus one cell,
- mixed segments,
- then the full confirmed route.

If repeatability falls, reduce speed and fix the failing layer rather than increasing controller gains blindly.

## Calibration record template

| Test | Trials | Mean | Spread | Battery state | Surface | Notes |
|---|---:|---:|---:|---|---|---|
| Ticks per cell |  |  |  |  |  |  |
| 90° right error |  |  |  |  |  |  |
| 90° left error |  |  |  |  |  |  |
| Front stop error |  |  |  |  |  |  |
| Corridor lateral error |  |  |  |  |  |  |
