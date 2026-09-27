/*
  Adapted from Team Reapers' competition firmware.
  Breadth-first flood recomputation from the four center cells.
*/
#include <stdint.h>

constexpr uint8_t N = 16;
constexpr uint8_t UNREACHED = 255;
static uint8_t distanceMap[N][N];

enum Direction : uint8_t { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 };
static constexpr int8_t DX[4] = {0, 1, 0, -1};
static constexpr int8_t DY[4] = {1, 0, -1, 0};

bool canTraverse(uint8_t x, uint8_t y, Direction direction);

static bool inBounds(int x, int y) {
  return x >= 0 && x < N && y >= 0 && y < N;
}

static bool isCenter(int x, int y) {
  return (x == N / 2 - 1 || x == N / 2) &&
         (y == N / 2 - 1 || y == N / 2);
}

void recomputeFlood() {
  static uint8_t queueX[N * N];
  static uint8_t queueY[N * N];
  uint16_t head = 0;
  uint16_t tail = 0;

  for (uint8_t x = 0; x < N; ++x) {
    for (uint8_t y = 0; y < N; ++y) {
      distanceMap[x][y] = UNREACHED;
      if (isCenter(x, y)) {
        distanceMap[x][y] = 0;
        queueX[tail] = x;
        queueY[tail] = y;
        ++tail;
      }
    }
  }

  while (head < tail) {
    const uint8_t x = queueX[head];
    const uint8_t y = queueY[head];
    ++head;

    for (uint8_t rawDirection = 0; rawDirection < 4; ++rawDirection) {
      const Direction direction = static_cast<Direction>(rawDirection);
      if (!canTraverse(x, y, direction)) continue;

      const int nx = x + DX[rawDirection];
      const int ny = y + DY[rawDirection];
      if (!inBounds(nx, ny)) continue;
      if (distanceMap[nx][ny] != UNREACHED) continue;

      distanceMap[nx][ny] = distanceMap[x][y] + 1U;
      queueX[tail] = static_cast<uint8_t>(nx);
      queueY[tail] = static_cast<uint8_t>(ny);
      ++tail;
    }
  }
}
