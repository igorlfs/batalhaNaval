#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H
#include "player.hpp"
namespace Players {
class computer : public player {
  private:
    bool chooseDirection() const;
    std::pair<uint, uint>
    chooseShipPosition(const Ships::ship &ship) const override;

  public:
    computer();
    std::pair<uint, uint> chooseAttackPosition() override;
};
} // namespace Players
#endif
