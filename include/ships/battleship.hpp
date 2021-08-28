#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include "ship.hpp"
namespace Ships {
static constexpr int BATTLESHIP_SIZE = 4;
class battleship : public ship {
  public:
    battleship() : ship(BATTLESHIP_SIZE, "Battleship"){};
};
} // namespace Ships
#endif
