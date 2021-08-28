#ifndef DESTROYER_H
#define DESTROYER_H
#include "ship.hpp"
namespace Ships {
static constexpr int DESTROYER_SIZE = 3;
class destroyer : public ship {
  public:
    destroyer() : ship(DESTROYER_SIZE, "Destroyer"){};
};
} // namespace Ships
#endif
