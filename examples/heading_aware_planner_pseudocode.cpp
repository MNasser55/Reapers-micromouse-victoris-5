/*
  Heading-aware route-planning sketch.
  The real implementation also stores predecessor states and compresses segments.
*/
#include <stdint.h>

struct State {
  uint8_t x;
  uint8_t y;
  uint8_t heading;  // north/east/south/west
};

constexpr uint16_t FORWARD_COST = 10;
constexpr uint16_t TURN_90_COST = 14;
constexpr uint16_t TURN_180_COST = 30;

uint16_t turnPenalty(uint8_t from, uint8_t to) {
  const uint8_t difference = (to - from + 4) % 4;
  if (difference == 0) return 0;
  if (difference == 2) return TURN_180_COST;
  return TURN_90_COST;
}

uint16_t transitionCost(const State &current, uint8_t moveDirection) {
  return FORWARD_COST + turnPenalty(current.heading, moveDirection);
}

/*
Dijkstra-style search:

1. Start at (0, 0, North) with cost 0.
2. Expand only confirmed-open edges.
3. Next state is (neighbor_x, neighbor_y, move_direction).
4. Add transitionCost(current, move_direction).
5. Store predecessor when the score improves.
6. Select the cheapest heading among the four center cells.
7. Backtrack directions and merge repeated directions into straight segments.

Useful tie-break order:
  a) lower weighted cost
  b) fewer turns
  c) fewer cells
*/
