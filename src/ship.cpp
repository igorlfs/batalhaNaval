#include "ship.hpp"
#include <assert.h>
#include <iostream>
using namespace ships;
void ship::setDirection(const char &direction) {
  assert(direction == 'v' || direction == 'h');
  (direction == 'h') ? this->direction = 1 : this->direction = 0;
}
void ship::setDirection(const bool &direction) { this->direction = direction; }
void ship::setPosition(const std::pair<int, int> &position) {
  if (this->direction) {
    for (int i = 0; i < this->size; ++i) {
      this->location.push_back({position.first, position.second + i});
    }
  } else {
    for (int i = 0; i < this->size; ++i) {
      this->location.push_back({position.first + i, position.second});
    }
  }
}
std::vector<std::pair<int, int>> ship::getPosition() const {
  return this->location;
}
void ship::clearLocation() { this->location.clear(); }
