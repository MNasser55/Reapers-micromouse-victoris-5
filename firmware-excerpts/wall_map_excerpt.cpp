/*
  Adapted from Team Reapers' competition firmware.
  Shows consistent mirrored-edge updates using known and wall bitmasks.
*/
#include <stdint.h>

constexpr uint8_t MAZE_SIZE = 16;
enum Direction : uint8_t { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };
enum EdgeState : uint8_t { UNKNOWN = 0, OPEN, WALL };

static uint8_t walls[MAZE_SIZE][MAZE_SIZE];
static uint8_t known[MAZE_SIZE][MAZE_SIZE];
static constexpr int8_t DX[4] = {0, 1, 0, -1};
static constexpr int8_t DY[4] = {1, 0, -1, 0};

static bool inBounds(int x, int y) {
  return x >= 0 && x < MAZE_SIZE && y >= 0 && y < MAZE_SIZE;
}

static uint8_t edgeBit(Direction direction) {
  return static_cast<uint8_t>(1U << static_cast<uint8_t>(direction));
}

static Direction opposite(Direction direction) {
  return static_cast<Direction>((static_cast<uint8_t>(direction) + 2U) & 3U);
}

static void setOneSide(int x, int y, Direction direction, EdgeState state) {
  if (!inBounds(x, y)) return;
  const uint8_t bit = edgeBit(direction);

  if (state == WALL) {
    known[x][y] |= bit;
    walls[x][y] |= bit;
  } else if (state == OPEN) {
    // A confirmed wall wins over a later contradictory open observation.
    if ((walls[x][y] & bit) == 0) {
      known[x][y] |= bit;
      walls[x][y] &= static_cast<uint8_t>(~bit);
    }
  }
}

void setMirroredEdge(int x, int y, Direction direction, EdgeState state) {
  setOneSide(x, y, direction, state);

  const int nx = x + DX[direction];
  const int ny = y + DY[direction];
  if (inBounds(nx, ny)) {
    setOneSide(nx, ny, opposite(direction), state);
  }
}
