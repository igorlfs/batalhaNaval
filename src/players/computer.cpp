#include "computer.hpp"
#include <iostream>
#include <random>
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
    this->initializeGrid();
    this->initializeShips();
    std::cout << "Inicializando navios do computador\n";
    for (int i = 0; i < TOTAL_SHIPS; ++i) {
        this->ships[i]->setDirection(chooseDirection());
        this->ships[i]->setCells(chooseShipPosition(*this->ships[i]));
        this->insertShipInGrid(*this->ships[i]);
    }
}
bool computer::chooseDirection() const { return randomNumberGenerator(0, 1); }
std::pair<uint, uint>
computer::chooseShipPosition(const ships::ship &ship) const {
    std::pair<uint, uint> position;
    do {
        position = {randomNumberGenerator(0, ROWS - 1),
                    randomNumberGenerator(0, COLS - 1)};
    } while (this->isOutOfBounds(ship, position) == true ||
             this->isOverlaping(ship, position) == true);
    return position;
}
std::pair<uint, uint> computer::chooseAttackPosition() {
    std::pair<uint, uint> attackPosition;
    do {
        attackPosition = {randomNumberGenerator(0, ROWS - 1),
                          randomNumberGenerator(0, COLS - 1)};
    } while (this->wasAttacked(attackPosition) == true);
    this->alreadyAttacked.insert(attackPosition);
    return attackPosition;
}
