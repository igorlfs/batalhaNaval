#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H
#include "player.hpp"
namespace players {
class human : public player {
  private:
    // Track ship placement while user is placing the ships
    void printContructionGrid() const;

    char chooseDirection(const ships::ship &ship) const;
    bool isDirectionValid(const std::string &str) const;
    std::pair<uint, uint>
    choosePosition(const ships::ship &ship) const override;
    bool isOutOfBounds(const ships::ship &ship,
                       const std::pair<uint, uint> &pos) const override;
    bool isOverlaping(const ships::ship &ship,
                      const std::pair<uint, uint> &pos) const override;

    bool
    isAttackOutOfBounds(const std::pair<uint, uint> &attackCandidate) const;
    bool isAttackRepeated(const std::pair<uint, uint> &attackCandidate) const;

    // Remove ship if user wants to relocate it
    void removeShipFromGrid(ships::ship *ship);

  public:
    human();

    std::pair<uint, uint> chooseAttackPosition() override;
};
} // namespace players
#endif
