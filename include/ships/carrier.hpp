#ifndef CARRIER_H
#define CARRIER_H
#include "ship.hpp"
namespace Ships {
static constexpr int CARRIER_SIZE = 5;
class carrier : public ship {
  public:
    carrier() : ship(CARRIER_SIZE, "Carrier"){};
};
} // namespace Ships
#endif
