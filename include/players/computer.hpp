#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H
#include "player.hpp"
namespace players {
class computer : public player {
public:
  computer();

private:
  bool chooseDirection() const;
  std::pair<int, int> choosePosition(const ships::ship &ship) const override;
  bool isOutOfBounds(const ships::ship &ship,
                     const std::pair<int, int> &pos) const override;
  bool isOverlaping(const ships::ship &ship,
                    const std::pair<int, int> &pos) const override;
};
} // namespace players
#endif
