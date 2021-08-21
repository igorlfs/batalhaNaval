#include "player.hpp"
#include <assert.h>
#include <iostream>
using namespace players;
void player::initializeBoard() {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      this->grid[i][j] = EMPTY;
    }
  }
}
void player::addShipToGrid(const ships::ship &ship) {
  std::vector<std::pair<int, int>> shipPos = ship.getLocation();
  char shipName = ship.getName()[0];
  for (unsigned k = 0; k < shipPos.size(); ++k) {
    this->grid[shipPos[k].first][shipPos[k].second] = shipName;
  }
}
bool player::isThereEnoughSpace() {
  int shipSizes[SHIP_TYPES] = {ships::CARRIER_SIZE, ships::BATTLESHIP_SIZE,
                               ships::DESTROYER_SIZE, ships::SUBMARINE_SIZE,
                               ships::PATROL_BOAT_SIZE};
  int occupableTiles = 0;
  for (int i = 0; i < SHIP_TYPES; ++i) {
    occupableTiles += shipSizes[i] * NUM_EACH_SHIP[i];
  }
  // It's possible to have occupableTiles ~ TILES and still get an untilable
  // grid. This happens because you can create 'vortexes' where no ship would
  // fit, eg:
  //
  //  *
  // * *
  //  *
  //
  // It's impossible to fit a ship (whose size is greater than 1) in between
  // those asterisks. This problem sounds really complex to solve analitically,
  // so instead, we do not allow occupableTiles ~ TILES and use an aproximation.
  if (occupableTiles <= MAX_OCCUPABLE * TILES) {
    return 1;
  } else {
    return 0;
  }
}
void player::initializeShips() {
  int sumEachShip = 0;
  for (int i = 0; i < SHIP_TYPES; ++i) {
    sumEachShip += NUM_EACH_SHIP[i];
  }
  assert(sumEachShip == TOTAL_SHIPS);
  assert(this->isThereEnoughSpace());
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
void player::printHeader() const {
  for (int i = 0; i < COLS + 1; ++i) {
    (i == 0)      ? std::cout << "  "
    : (i == COLS) ? std::cout << 'X'
                  : std::cout << i - 1;
    if (i != COLS) {
      std::cout << " │ ";
    }
  }
  std::cout << std::endl;
}
void player::printSeparator() const {
  for (int i = 0; i < COLS + 1; ++i) {
    if (i == 0) {
      std::cout << "───┼";
    } else if (i == COLS) {
      std::cout << "───";
    } else {
      std::cout << "───┼";
    }
  }
  std::cout << std::endl;
}
bool player::wasAnAttempt(const std::pair<int, int> &cell) const {
  for (auto i : this->bombingAttempts) {
    if (i == cell) {
      return true;
    }
  }
  return false;
}
