#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H
#include "player.hpp"
namespace Players {
// Uses a random number generator to simulate a player
class computer : public player {
  private:
    bool chooseDirection() const;
    pair<uint, uint> chooseShipPosition(const Ships::ship &ship) const override;

  public:
    computer();
    pair<uint, uint> chooseAttackPosition() override;
};
} // namespace Players
#endif
