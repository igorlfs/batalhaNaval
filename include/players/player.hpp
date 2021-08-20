#ifndef PLAYER_H
#define PLAYER_H
#include "battleship.hpp"
#include "carrier.hpp"
#include "destroyer.hpp"
#include "patrolBoat.hpp"
#include "submarine.hpp"
#include <string>
namespace players {
class player {
private:
  static constexpr int SHIP_TYPES = 5;
  static constexpr int NUM_EACH_SHIP[SHIP_TYPES] = {1, 1, 1, 1, 2};

  // Lembre-se de inicializar as funções virtuais!
  // O linkador espera que elas estejam definidas em algum momento do programa
  // Um jeito de fazer isso é usando esse '= 0'
  virtual bool isOutOfBounds(const ships::ship &ship,
                             const std::pair<int, int> &pos) const = 0;
  virtual bool isOverlaping(const ships::ship &ship,
                            const std::pair<int, int> &pos) const = 0;
  virtual std::pair<int, int> choosePosition(const ships::ship &ship) const = 0;
  virtual char chooseDirection(const ships::ship &ship) const = 0;

protected:
  static constexpr int ROWS = 6;
  static constexpr int COLS = 6;

  static constexpr int TOTAL_SHIPS = 6;

  static constexpr char EMPTY = ' ';

  char board[ROWS][COLS];

  // Segundo a wikipédia, o jogo original conta com
  // 1 carrier, 2 battleships, 3 destroyers, 4 submarines, 5 patrolBoats
  // (mas isso fica meio chato de colocar no terminal)
  ships::ship *ships[TOTAL_SHIPS];

  void initializeBoard();
  void initializeShips();

  void addShipToBoard(ships::ship &ship);

  virtual ~player();
};
} // namespace players
#endif
