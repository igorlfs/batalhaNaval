#ifndef SHIP_H
#define SHIP_H
#include <map>
#include <string>
#include <utility>
#include <vector>
namespace ships {
class ship {
  protected:
    int size;
    std::string name;
    bool direction;
    // A cell is an unit (ie, a square in a grid) from a ship
    // Each cell can be either bombed (1) or nom-bombed (0)
    std::map<std::pair<uint, uint>, bool> cells;
    bool isDestroyed{0};

  public:
    // Contructors
    ship(const int &size, const std::string &name) : size(size), name(name){};

    // Getters
    int getSize() const { return this->size; }
    std::string getName() const { return this->name; }
    std::vector<std::pair<uint, uint>> getLocation() const;
    bool getState() const { return this->isDestroyed; }
    // return 'true' for horizontal, 'false' for vertical
    bool getDirection() const { return this->direction; }

    // Setters
    // Human based method to set a direction
    void setDirection(const char &direction);
    // Non-Human based method to set a direction
    void setDirection(const bool &direction) { this->direction = direction; }
    // Initialize cells as non-bombed
    void setCells(const std::pair<uint, uint> &position);

    void clearCells() { this->cells.clear(); }
    void bombCell(const std::pair<uint, uint> position) {
        this->cells[{position.first, position.second}] = 1;
    }
    void wasDestroyed();
};
} // namespace ships

#endif
