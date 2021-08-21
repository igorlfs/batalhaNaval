#include "computer.hpp"
#include <iostream>
#include <random>
// taken from
// https://stackoverflow.com/questions/13445688/how-to-generate-a-random-number-in-c
int randomNumberGenerator(int floor, int ceiling) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(floor,
                                                                  ceiling);
    return dist(rng);
}
using namespace players;
computer::computer() {
    this->initializeBoard();
    this->initializeShips();
    std::cout << "Inicializando navios do computador\n";
    for (int i = 0; i < TOTAL_SHIPS; ++i) {
        this->ships[i]->setDirection(chooseDirection());
        this->ships[i]->setCells(choosePosition(*this->ships[i]));
        this->addShipToGrid(*this->ships[i]);
    }
}
bool computer::chooseDirection() const { return randomNumberGenerator(0, 1); }
std::pair<int, int> computer::choosePosition(const ships::ship &ship) const {
    std::pair<int, int> position;
    do {
        position = {randomNumberGenerator(0, ROWS - 1),
                    randomNumberGenerator(0, COLS - 1)};
    } while (this->isOutOfBounds(ship, position) == true ||
             this->isOverlaping(ship, position) == true);
    return position;
}
bool computer::isOutOfBounds(const ships::ship &ship,
                             const std::pair<int, int> &pos) const {
    if ((ship.getDirection() && ship.getSize() + pos.second > ROWS) ||
        (!ship.getDirection() && ship.getSize() + pos.first > COLS)) {
        return 1;
    }
    return 0;
}
bool computer::isOverlaping(const ships::ship &ship,
                            const std::pair<int, int> &pos) const {
    ships::ship testShip = ship;
    testShip.setCells(pos);
    std::vector<std::pair<int, int>> positionCandidate = testShip.getLocation();
    for (unsigned k = 0; k < positionCandidate.size(); ++k) {
        if (this->grid[positionCandidate[k].first]
                      [positionCandidate[k].second] != EMPTY) {
            return 1;
        }
    }
    return 0;
}
void computer::attack() {
    std::pair<int, int> attackPositionCandidate;
    do {
        attackPositionCandidate = {randomNumberGenerator(0, ROWS - 1),
                                   randomNumberGenerator(0, COLS - 1)};
    } while (this->isAttemptRepeated(attackPositionCandidate) == true);
    this->bombingAttempts.insert(attackPositionCandidate);
}
bool computer::isAttemptRepeated(const std::pair<int, int> &position) const {
    if (this->bombingAttempts.find(position) != this->bombingAttempts.end()) {
        return true;
    }
    return false;
}
