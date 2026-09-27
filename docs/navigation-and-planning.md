# Navigation and Planning

## Maze representation

Four 16×16 structures are sufficient for the core exploration model:

```text
walls[x][y]    -> N/E/S/W wall bitmask
known[x][y]    -> measured-edge bitmask
distance[x][y] -> flood value
visited[x][y]  -> exploration tie-breaker
pose           -> (x, y, heading)
```

A separate `known` mask is important. “No wall bit” does not necessarily mean “confirmed open”; it can still mean “unknown.”

## Dynamic flood fill

1. Set every distance to infinity.
2. Seed the four center cells with zero.
3. Run breadth-first propagation over currently traversable edges.
4. Recompute after new wall evidence changes connectivity.
5. Select a neighboring cell with the smallest flood value.

During exploration, unknown edges are traversable until measured. During the speed run, only confirmed-open edges are traversable.

## Direction policy

A deterministic direction order reduces oscillation and makes debugging reproducible. Reaper preferred:

1. forward,
2. right,
3. left,
4. back.

Unvisited cells were preferred when flood values tied.

## Heading-aware weighted planner

Shortest cell count is not always the fastest physical route. Braking, rotating, settling, and accelerating can make a slightly longer route with fewer turns faster.

The speed-run state therefore includes heading:

```text
state = (x, y, arrival_heading)
transition = move through a confirmed-open edge
cost = forward_cost + turn_penalty
```

A Dijkstra-style search minimizes cost. Ties are resolved by fewer turns and then fewer cells. After backtracking, repeated directions are compressed into multi-cell straight segments.

## Safety rule

If no fully confirmed route to the center exists, speed-plan construction fails. The firmware does not guess through unknown edges during the speed run.
