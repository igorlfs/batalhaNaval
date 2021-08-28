#ifndef SHIP_H
#define SHIP_H
#include <map>
#include <string>
#include <utility>
#include <vector>
using std::pair;
namespace Ships {
static constexpr char directions[2] = {'v', 'h'};
class ship {
  protected:
    int size;
    std::string name;
    bool direction;
    // A cell is an unit (ie, a square in a grid) from a ship
    // Each cell can be either bombed (1) or nom-bombed (0)
    std::map<pair<uint, uint>, bool> cells;
    bool isDestroyed{0};

  public:
    // Contructors
    ship(const int &size, const std::string &name) : size(size), name(name){};

    // Getters
    int getSize() const { return this->size; }
    std::string getName() const { return this->name; }
    // Return 'true' if destroyed, 'false' otherwise
    bool getState() const { return this->isDestroyed; }
    // Return 'true' for horizontal, 'false' for vertical
    bool getDirection() const { return this->direction; }
    // Return a vector containing the positions of each cell
    std::vector<pair<uint, uint>> getLocation() const;

    // Setters
    // Non-Human based method to set a direction
    void setDirection(const bool &direction) { this->direction = direction; }
    // Human based method to set a direction
    void setDirection(const char &direction);
    // Initialize cells as non-bombed
    void setCells(const pair<uint, uint> &position);

    // Modifiers
    void clearCells() { this->cells.clear(); }
    void bombCell(const pair<uint, uint> position) {
        this->cells[{position.first, position.second}] = 1;
    }
    // Destroys a ship; Also displays a message warning the players
    void destroyShip();
};
} // namespace Ships

#endif
