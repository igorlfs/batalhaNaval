#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H
#include "player.hpp"
namespace Players {
class human : public player {
  private:
    // Track ship placement while user is placing the ships
    void printContructionGrid() const;

    char chooseDirection(const Ships::ship &ship) const;
    std::pair<uint, uint>
    chooseShipPosition(const Ships::ship &ship) const override;

    // Remove ship if user wants to relocate it
    void removeShipFromGrid(Ships::ship *ship);

  public:
    human();

    std::pair<uint, uint> chooseAttackPosition() override;
};
} // namespace Players
#endif
