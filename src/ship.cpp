#include "ship.hpp"
#include <assert.h>
#include <iostream>
using namespace ships;
void ship::setDirection(const char &direction) {
    assert(direction == 'v' || direction == 'h');
    (direction == 'h') ? this->direction = 1 : this->direction = 0;
}
void ship::setDirection(const bool &direction) { this->direction = direction; }
void ship::setCells(const std::pair<uint, uint> &position) {
    if (this->direction) {
        for (int i = 0; i < this->size; ++i) {
            this->cells[{position.first, position.second + i}] = 0;
        }
    } else {
        for (int i = 0; i < this->size; ++i) {
            this->cells[{position.first + i, position.second}] = 0;
        }
    }
}
std::vector<std::pair<uint, uint>> ship::getLocation() const {
    std::vector<std::pair<uint, uint>> location;
    for (auto const &i : this->cells) {
        location.push_back(i.first);
    }
    return location;
}
void ship::clearCells() { this->cells.clear(); }
