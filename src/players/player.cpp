#include "player.hpp"
#include <assert.h>
#include <iostream>
using namespace players;
void player::initializeBoard() {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      this->board[i][j] = EMPTY;
    }
  }
}
void player::addShipToBoard(ships::ship &ship) {
  std::vector<std::pair<int, int>> shipPos = ship.getPosition();
  char shipName = ship.getName()[0];
  for (unsigned k = 0; k < shipPos.size(); ++k) {
    this->board[shipPos[k].first][shipPos[k].second] = shipName;
  }
}
void player::initializeShips() {
  int sumEachShip = 0;
  for (int i = 0; i < SHIP_TYPES; ++i) {
    sumEachShip += NUM_EACH_SHIP[i];
  }
  assert(sumEachShip == TOTAL_SHIPS);
  int shipInitializer = 0;
  for (int i = 0; i < SHIP_TYPES; ++i) {
    for (int j = 0; j < NUM_EACH_SHIP[i]; ++j) {
      switch (i) {
      case 0:
        this->ships[shipInitializer] = new ships::carrier;
        break;
      case 1:
        this->ships[shipInitializer] = new ships::battleship;
        break;
      case 2:
        this->ships[shipInitializer] = new ships::destroyer;
        break;
      case 3:
        this->ships[shipInitializer] = new ships::submarine;
        break;
      case 4:
        this->ships[shipInitializer] = new ships::patrolBoat;
        break;
      default:
        std::cerr << "Error: couldn't initialize ships: unexpected ship type";
      }
      shipInitializer++;
    }
  }
  assert(shipInitializer == TOTAL_SHIPS);
}
player::~player() {
  for (int i = 0; i < TOTAL_SHIPS; ++i) {
    delete ships[i];
  }
}
