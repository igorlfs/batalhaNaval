#ifndef DESTROYER_H
#define DESTROYER_H
#include "ship.hpp"
namespace ships {
class destroyer : public ship {
  static constexpr int DESTROYER_SIZE = 3;

public:
  destroyer() : ship(DESTROYER_SIZE, "destroyer"){};
};
} // namespace ships
#endif
