#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H
#include "player.hpp"
namespace players {
class human : public player {
  public:
    human();

    void attack() override;

  private:
    void printGrid() const;

    void clearShip(ships::ship *ship);

    char chooseDirection(const ships::ship &ship) const;
    std::pair<uint, uint>
    choosePosition(const ships::ship &ship) const override;
    bool isOutOfBounds(const ships::ship &ship,
                       const std::pair<uint, uint> &pos) const override;
    bool isOverlaping(const ships::ship &ship,
                      const std::pair<uint, uint> &pos) const override;

    bool
    isAttackOutOfBounds(const std::pair<uint, uint> &attackCandidate) const;
    bool
    isAttemptRepeated(const std::pair<uint, uint> &position) const override;
};
} // namespace players
#endif
