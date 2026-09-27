/*
  Simplified flood-fill example. It demonstrates the idea, not full robot firmware.
*/
#include <stdint.h>

constexpr uint8_t N = 16;
constexpr uint8_t INF = 255;

enum Dir : uint8_t { North, East, South, West };
uint8_t distanceToGoal[N][N];

bool isGoal(uint8_t x, uint8_t y) {
  return (x == N / 2 - 1 || x == N / 2) &&
         (y == N / 2 - 1 || y == N / 2);
}

// Application supplies these using its known/wall map.
bool mayTraverse(uint8_t x, uint8_t y, Dir direction);
bool neighbor(uint8_t x, uint8_t y, Dir direction, uint8_t &nx, uint8_t &ny);

void recomputeFlood() {
  struct Cell { uint8_t x, y; };
  Cell queue[N * N];
  uint16_t head = 0, tail = 0;

  for (uint8_t x = 0; x < N; ++x) {
    for (uint8_t y = 0; y < N; ++y) {
      distanceToGoal[x][y] = INF;
      if (isGoal(x, y)) {
        distanceToGoal[x][y] = 0;
        queue[tail++] = {x, y};
      }
    }
  }

  while (head < tail) {
    const Cell current = queue[head++];

    for (uint8_t raw = 0; raw < 4; ++raw) {
      const Dir direction = static_cast<Dir>(raw);
      uint8_t nx, ny;
      if (!mayTraverse(current.x, current.y, direction)) continue;
      if (!neighbor(current.x, current.y, direction, nx, ny)) continue;
      if (distanceToGoal[nx][ny] != INF) continue;

      distanceToGoal[nx][ny] = distanceToGoal[current.x][current.y] + 1;
      queue[tail++] = {nx, ny};
    }
  }
}
