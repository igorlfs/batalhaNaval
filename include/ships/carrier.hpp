#ifndef CARRIER_H
#define CARRIER_H
#include "ship.hpp"
namespace ships {
class carrier : public ship {
  static constexpr int CARRIER_SIZE = 5;

public:
  carrier() : ship(CARRIER_SIZE, "carrier"){};
};
} // namespace ships
#endif
