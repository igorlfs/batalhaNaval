#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H
#include "player.hpp"
namespace players {
class human : public player {
public:
  human();

private:
  void printBoard() const;
  void printHeader() const;
  void printSeparator() const;

  void clearShip(ships::ship *ship);

  bool isOutOfBounds(const ships::ship &ship,
                     const std::pair<int, int> &pos) const override;
  bool isOverlaping(const ships::ship &ship,
                    const std::pair<int, int> &pos) const override;
  std::pair<int, int> choosePosition(const ships::ship &ship) const override;
  char chooseDirection(const ships::ship &ship) const override;
};
} // namespace players
#endif
