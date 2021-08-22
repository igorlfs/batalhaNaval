#ifndef SHIP_H
#define SHIP_H
#include <map>
#include <string>
#include <utility>
#include <vector>
namespace ships {
class ship {
  public:
    ship(const int &size, const std::string &name) : size(size), name(name){};

    int getSize() const { return this->size; }
    std::string getName() const { return this->name; }

    // @return 'true' for horizontal, 'false' for vertical
    bool getDirection() const { return this->direction; }

    void setDirection(const char &direction);
    void setDirection(const bool &direction);
    void setCells(const std::pair<uint, uint> &position);

    std::vector<std::pair<uint, uint>> getLocation() const;
    void clearCells();

  protected:
    int size;
    std::string name;
    std::map<std::pair<uint, uint>, bool> cells;
    bool direction;
};
} // namespace ships

#endif
