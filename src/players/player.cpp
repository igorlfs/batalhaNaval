#include "player.hpp"
#include <assert.h>
#include <iostream>
using namespace players;
bool player::isThereEnoughSpace() const {
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
    // those asterisks. This problem sounds really complex to solve
    // analitically, so instead, we do not allow occupableTiles ~ TILES and use
    // an aproximation.
    if (occupableTiles <= MAX_OCCUPABLE * TILES) {
        return 1;
    } else {
        return 0;
    }
}
void player::initializeGrid() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            this->grid[i][j] = EMPTY;
        }
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
                std::cerr
                    << "Error: couldn't initialize ships: unexpected ship type";
            }
            shipInitializer++;
        }
    }
    assert(shipInitializer == TOTAL_SHIPS);
}
void player::insertShipInGrid(const ships::ship &ship) {
    std::vector<std::pair<uint, uint>> shipPos = ship.getLocation();
    char shipName = ship.getName()[0];
    for (unsigned k = 0; k < shipPos.size(); ++k) {
        this->grid[shipPos[k].first][shipPos[k].second] = shipName;
    }
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
        (i == 0)      ? std::cout << "───┼"
        : (i == COLS) ? std::cout << "───"
                      : std::cout << "───┼";
    }
    std::cout << std::endl;
}
bool player::wasAttacked(const std::pair<uint, uint> &position) const {
    return (this->alreadyAttacked.find(position) !=
            this->alreadyAttacked.end());
}
bool player::wasDamaged(const std::pair<uint, uint> &position) const {
    return (this->alreadyDamaged.find(position) != this->alreadyDamaged.end());
}
void player::takeDamage(const std::pair<uint, uint> &attack) {
    for (uint i = 0; i < TOTAL_SHIPS; ++i) {
        std::vector<std::pair<uint, uint>> location =
            this->ships[i]->getLocation();
        for (uint k = 0; k < this->ships[i]->getSize(); ++k) {
            if (location[k] == attack) {
                this->alreadyDamaged.insert(attack);
                this->ships[i]->bombCell(attack);
                this->ships[i]->wasDestroyed();
            }
        }
    }
}
bool player::isDead() const {
    uint lostShips = 0;
    for (uint i = 0; i < TOTAL_SHIPS; ++i) {
        if (this->ships[i]->getState()) lostShips++;
    }
    return (lostShips == TOTAL_SHIPS);
}
