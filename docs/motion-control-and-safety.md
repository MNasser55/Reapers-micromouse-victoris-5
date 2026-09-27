# Motion Control and Safety

## Encoder-referenced translation

Wheel encoders measure cell progress. A motion segment uses an acceleration region, cruise region, and braking region rather than one fixed PWM command. Near a trusted front wall, range feedback can refine the final stopping position.

Calibration values depend on wheel diameter, encoder resolution, gear ratio, floor friction, battery state, and mechanical assembly. This repository intentionally omits the final tuned values.

## Fused straight-line steering

The steering correction combines two references:

```text
correction = wall_controller(side_error) + gyro_controller(heading_error)
```

- With two side walls, side error can be based on left-minus-right distance.
- With one side wall, the controller tracks a calibrated reference distance.
- Without reliable side walls, the gyro maintains heading.
- When the reference type changes, incompatible controller history should be reset.

## Gyro-referenced turns

A turn targets the nearest grid heading plus the requested 90° or 180° change. Completion requires:

- small angular error,
- low angular rate,
- a short settling period,
- and a hard timeout.

Successful front-wall squaring can correct accumulated heading drift.

## Sensor integrity

Useful practices include:

- reject impossible ranges,
- track sample freshness,
- allow only a bounded number of stale reads,
- apply hysteresis to wall decisions,
- stagger continuous sensor starts,
- and recover or fault when a stream stops updating.

## Protective behavior

- Raw front-proximity emergency check
- Dynamic stopping distance that increases with command speed
- Cell-overrun detection
- Stall timeout
- IMU and turn timeouts
- Physical emergency stop
- Fault state that continuously commands zero output

Software protection supplements, but does not replace, electrical protection and physical testing.
