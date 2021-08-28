#include "player.hpp"
#include "color.hpp"
#include <assert.h>
#include <iostream>
using namespace Players;
bool player::isThereEnoughSpace() const {
    int shipSizes[SHIP_TYPES] = {Ships::CARRIER_SIZE, Ships::BATTLESHIP_SIZE,
                                 Ships::DESTROYER_SIZE, Ships::SUBMARINE_SIZE,
                                 Ships::PATROL_BOAT_SIZE};
    int occupableTiles = 0;
    for (int i = 0; i < SHIP_TYPES; ++i) {
        occupableTiles += shipSizes[i] * NUM_EACH_TYPE[i];
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
    // those asterisks. This problem sounds really complex to solve
    // analytically, so instead, we do not allow occupableTiles ~ TILES and use
    // an approximation.
    return (occupableTiles <= MAX_OCCUPABLE * TILES);
}
void player::initializeGrid() {
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j) this->grid[i][j] = EMPTY;
}
void player::initializeShips() {
    int sumEachShip = 0;
    for (int i = 0; i < SHIP_TYPES; ++i) sumEachShip += NUM_EACH_TYPE[i];
    assert(sumEachShip == TOTAL_SHIPS);
    assert(this->isThereEnoughSpace());
    int shipInitializer = 0;
    for (int i = 0; i < SHIP_TYPES; ++i) {
        for (int j = 0; j < NUM_EACH_TYPE[i]; ++j) {
            switch (i) {
            case 0:
                this->ships[shipInitializer] = new Ships::carrier;
                break;
            case 1:
                this->ships[shipInitializer] = new Ships::battleship;
                break;
            case 2:
                this->ships[shipInitializer] = new Ships::destroyer;
                break;
            case 3:
                this->ships[shipInitializer] = new Ships::submarine;
                break;
            case 4:
                this->ships[shipInitializer] = new Ships::patrolBoat;
                break;
            default:
                std::cerr
                    << "Error: couldn't initialize ships: unexpected ship type";
            }
            shipInitializer++;
        }
    }
    assert(shipInitializer == TOTAL_SHIPS);
}
bool player::isOutOfBounds(const Ships::ship &ship,
                           const pair<uint, uint> &pos) const {
    return ((ship.getDirection() && ship.getSize() + pos.second > ROWS) ||
            (!ship.getDirection() && ship.getSize() + pos.first > COLS));
}
bool player::isOverlaping(const Ships::ship &ship,
                          const pair<uint, uint> &position) const {
    Ships::ship testShip = ship;
    testShip.setCells(position);
    std::vector<pair<uint, uint>> positionCandidate = testShip.getLocation();
    for (uint k = 0; k < positionCandidate.size(); ++k) {
        if (this->grid[positionCandidate[k].first]
                      [positionCandidate[k].second] != EMPTY) {
            return true;
        }
    }
    return false;
}
void player::insertShipInGrid(const Ships::ship &ship) {
    std::vector<pair<uint, uint>> shipPos = ship.getLocation();
    char shipName = ship.getName()[0];
    for (unsigned k = 0; k < shipPos.size(); ++k) {
        this->grid[shipPos[k].first][shipPos[k].second] = shipName;
    }
}
player::~player() {
    for (int i = 0; i < TOTAL_SHIPS; ++i) delete ships[i];
}
void player::printHeader() const {
    for (int i = 0; i < COLS + 1; ++i) {
        (i == 0) ? std::cout << "  " : std::cout << i;
        if (i != COLS) {
            std::cout << Color::Modifier(Color::FG_CYAN) << " │ "
                      << Color::RESET;
        }
    }
    std::cout.put('\n');
}
void player::printSeparator() const {
    for (int i = 0; i < COLS + 1; ++i) {
        (i == 0) ? std::cout << Color::Modifier(Color::FG_CYAN) << "───┼"
                             << Color::RESET
        : (i == COLS) ? std::cout << Color::Modifier(Color::FG_CYAN) << "───"
                                  << Color::RESET
                      : std::cout << Color::Modifier(Color::FG_CYAN) << "───┼"
                                  << Color::RESET;
    }
    std::cout.put('\n');
}
bool player::wasAttacked(const pair<uint, uint> &position) const {
    return (this->alreadyAttacked.find(position) !=
            this->alreadyAttacked.end());
}
bool player::wasDamaged(const pair<uint, uint> &position) const {
    return (this->alreadyDamaged.find(position) != this->alreadyDamaged.end());
}
void player::takeDamage(const pair<uint, uint> &attack) {
    for (uint i = 0; i < TOTAL_SHIPS; ++i) {
        std::vector<pair<uint, uint>> location = this->ships[i]->getLocation();
        for (uint k = 0; k < this->ships[i]->getSize(); ++k) {
            if (location[k] == attack) {
                this->alreadyDamaged.insert(attack);
                this->ships[i]->bombCell(attack);
                this->ships[i]->destroyShip();
            }
        }
    }
}
bool player::isDead() const {
    uint lostShips = 0;
    for (uint i = 0; i < TOTAL_SHIPS; ++i)
        if (this->ships[i]->getState()) lostShips++;
    return (lostShips == TOTAL_SHIPS);
}
