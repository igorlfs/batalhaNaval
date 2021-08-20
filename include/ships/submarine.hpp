#ifndef SUBMARINE_H
#define SUBMARINE_H
#include "ship.hpp"
namespace ships {
class submarine : public ship {
  static constexpr int SUBMARINE_SIZE = 3;

public:
  submarine() : ship(SUBMARINE_SIZE, "submarine"){};
};
} // namespace ships
#endif
