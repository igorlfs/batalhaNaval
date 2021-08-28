#ifndef PATROL_BOAT_H
#define PATROL_BOAT_H
#include "ship.hpp"
namespace Ships {
static constexpr int PATROL_BOAT_SIZE = 2;
class patrolBoat : public ship {
  public:
    patrolBoat() : ship(PATROL_BOAT_SIZE, "Patrol boat"){};
};
} // namespace Ships
#endif
