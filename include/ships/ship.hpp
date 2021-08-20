#ifndef SHIP_H
#define SHIP_H
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
  void setPosition(const std::pair<int, int> &position);

  std::vector<std::pair<int, int>> getPosition() const;
  void clearLocation();

protected:
  int size;
  std::string name;
  std::vector<std::pair<int, int>> location;
  bool direction;
};
} // namespace ships

#endif
