#ifndef PATROL_BOAT_H
#define PATROL_BOAT_H
#include "ship.hpp"
namespace ships {
class patrolBoat : public ship {
  static constexpr int PATROL_BOAT_SIZE = 2;

public:
  patrolBoat() : ship(PATROL_BOAT_SIZE, "patrol boat"){};
};
} // namespace ships
#endif
