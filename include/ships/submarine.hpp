#ifndef SUBMARINE_H
#define SUBMARINE_H
#include "ship.hpp"
namespace Ships {
static constexpr int SUBMARINE_SIZE = 3;
class submarine : public ship {
  public:
    submarine() : ship(SUBMARINE_SIZE, "Submarine"){};
};
} // namespace Ships
#endif
