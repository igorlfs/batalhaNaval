#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H
#include "player.hpp"
namespace players {
class computer : public player {
  public:
    computer();
    void attack(player &enemy) override;

  private:
    bool chooseDirection() const;
    std::pair<uint, uint>
    choosePosition(const ships::ship &ship) const override;
    bool isOutOfBounds(const ships::ship &ship,
                       const std::pair<uint, uint> &pos) const override;
    bool isOverlaping(const ships::ship &ship,
                      const std::pair<uint, uint> &pos) const override;

    bool
    isAttemptRepeated(const std::pair<uint, uint> &position) const override;
};
} // namespace players
#endif
