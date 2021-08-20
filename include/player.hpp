#ifndef PLAYER_H
#define PLAYER_H
#include "battleship.hpp"
#include "carrier.hpp"
#include "destroyer.hpp"
#include "patrolBoat.hpp"
#include "submarine.hpp"
#include <memory>
#include <string>
class player {
public:
  player();
  virtual ~player();

private:
  static constexpr int ROWS = 6;
  static constexpr int COLS = 6;
  static constexpr int TOTAL_SHIPS = 6;
  static constexpr char EMPTY = ' ';

  char board[ROWS][COLS];

  // Segundo a wikipédia, o jogo original conta com
  // 1 carrier, 2 battleships, 3 destroyers, 4 submarines, 5 patrolBoats
  // (mas isso fica meio chato de colocar no terminal)
  ships::ship *ships[TOTAL_SHIPS];
  /* std::unique_ptr<ship> ships[TOTAL_SHIPS]; */

  void initializeBoard();
  void printHeader() const;
  void printSeparator() const;
  void printBoard() const;

  std::pair<int, int> choosePosition(const ships::ship &ship) const;
  bool isOutOfBounds(const ships::ship &ship,
                     const std::pair<int, int> &pos) const;
  bool isOverlaping(const ships::ship &ship,
                    const std::pair<int, int> &pos) const;
  void clearShip(ships::ship *ship);
  void updateBoard(ships::ship &ship);
};
#endif
