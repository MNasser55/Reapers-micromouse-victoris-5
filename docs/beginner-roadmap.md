# Beginner Roadmap

This roadmap is for a student entering Micromouse for the first time. Build and verify one layer before adding the next. Do not begin with a full maze run.

## Phase 1 — Understand the challenge

Learn the maze dimensions, goal definition, run rules, restart rules, robot-size limits, battery limits, and whether mapping can be retained between attempts.

**Exit condition:** you can explain exploration and speed run as two different operating modes.

## Phase 2 — Bring up power safely

1. Verify battery polarity and protection.
2. Measure the regulated electronics rail without the ESP32 installed.
3. Check common ground between logic, sensors, and motor driver.
4. Confirm the physical stop switch removes motor power or safely disables motion.
5. Measure motor stall current before selecting wiring and protection limits.

**Exit condition:** stable logic voltage and repeatable emergency stopping.

## Phase 3 — Test one motor at a time

1. Run the left motor forward and backward at low PWM.
2. Repeat for the right motor.
3. Confirm the software sign matches physical forward motion.
4. Record the minimum PWM that starts each wheel reliably.

**Exit condition:** both wheels respond correctly with no unexpected reset or overheating.

## Phase 4 — Validate encoders

1. Rotate each wheel by hand and inspect counts.
2. Confirm forward motion produces the intended sign.
3. Reject impossible pulses caused by electrical noise.
4. Measure repeated one-wheel revolutions.
5. Estimate ticks per millimeter and later refine using real floor motion.

**Exit condition:** repeatable counts with correct direction.

## Phase 5 — Build one-cell motion

1. Move slowly for a small number of ticks.
2. Add acceleration and braking regions.
3. Measure one-cell travel repeatedly.
4. Compare left and right wheel progress.
5. Stop and report a fault if progress stalls.

**Exit condition:** repeatable one-cell translation before wall feedback is enabled.

## Phase 6 — Bring up the gyro

1. Keep the robot stationary during bias calibration.
2. Integrate the Z-axis angular rate into yaw.
3. Check the sign of clockwise and counter-clockwise rotation.
4. Test drift while stationary.
5. Implement bounded 90° and 180° turns with timeout and settling checks.

**Exit condition:** repeated grid turns without relying on fixed delays.

## Phase 7 — Bring up range sensors

1. Start with one VL53L0X.
2. Add XSHUT sequencing and a unique address for each additional sensor.
3. Reject impossible or stale measurements.
4. Test under different wall colors, distances, and lighting.
5. Add hysteresis so wall decisions do not flicker near a threshold.

**Exit condition:** stable front, side, and diagonal wall decisions.

## Phase 8 — Add corridor steering

1. Start with gyro heading hold.
2. Add one-wall following.
3. Add two-wall centering.
4. Reset controller history when the reference changes.
5. Limit correction so steering cannot reverse or saturate one wheel unexpectedly.

**Exit condition:** straight travel through open, one-wall, and two-wall test corridors.

## Phase 9 — Simulate the maze algorithm

1. Store walls and known edges separately.
2. Mirror every edge update into the neighboring cell.
3. Initialize outer boundaries as known walls.
4. Run flood fill on several mazes with loops and dead ends.
5. Verify the logical pose changes only after a successful motion.

**Exit condition:** the algorithm reaches the center in simulation and produces a consistent map.

## Phase 10 — Physical exploration

1. Begin with a small test maze.
2. Run one decision and one cell at a time.
3. Compare the internal map with the real walls after every step.
4. Add recovery for stale sensors, failed turns, stalls, and overruns.
5. Expand toward a full-size maze only after small tests are repeatable.

**Exit condition:** autonomous center-reaching exploration with no operator correction.

## Phase 11 — Map retention and speed run

1. Keep the confirmed map after exploration.
2. Reset pose and control state when the robot returns to start.
3. Reject unknown edges in the speed planner.
4. Add heading to the planner state so turns carry a cost.
5. Compress repeated directions into multi-cell segments.
6. Increase speed gradually; never begin with maximum PWM.

**Exit condition:** a confirmed route is executed reliably before speed is increased.
