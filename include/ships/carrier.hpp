#ifndef CARRIER_H
#define CARRIER_H
#include "ship.hpp"
namespace ships {
static constexpr int CARRIER_SIZE = 5;
class carrier : public ship {
  public:
    carrier() : ship(CARRIER_SIZE, "carrier"){};
};
} // namespace ships
#endif
