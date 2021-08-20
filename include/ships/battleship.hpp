#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include "ship.hpp"
namespace ships {
class battleship : public ship {
  static constexpr int BATTLESHIP_SIZE = 4;

public:
  battleship() : ship(BATTLESHIP_SIZE, "battleship"){};
};
} // namespace ships
#endif
