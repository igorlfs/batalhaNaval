#ifndef SUBMARINE_H
#define SUBMARINE_H
#include "ship.hpp"
namespace ships {
static constexpr int SUBMARINE_SIZE = 3;
class submarine : public ship {
  public:
    submarine() : ship(SUBMARINE_SIZE, "submarine"){};
};
} // namespace ships
#endif
