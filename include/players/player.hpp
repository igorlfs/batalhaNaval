#ifndef PLAYER_H
#define PLAYER_H
#include "battleship.hpp"
#include "carrier.hpp"
#include "destroyer.hpp"
#include "patrolBoat.hpp"
#include "submarine.hpp"
#include <memory>
#include <set>
#include <string>
namespace Players {
// Declared outside the class as they are used outside an instance of player
static constexpr int ROWS = 6;
// The game may not look as good with more than 8 columns
// as it currently expects a single char when priting the header
static constexpr int COLS = 6;
static constexpr int TILES = ROWS * COLS;
static constexpr char EMPTY = 'O'; // 'O' as in Ocean
class player {
  private:
    static constexpr int SHIP_TYPES = 5;
    static constexpr int NUM_EACH_TYPE[SHIP_TYPES] = {1, 1, 1, 1, 2};
    static constexpr double MAX_OCCUPABLE = 0.8;

    // Check if it's possible to fit all ships in the grid
    // Uses MAX_OCCUPABLE
    bool isThereEnoughSpace() const;

    virtual pair<uint, uint>
    chooseShipPosition(const Ships::ship &ship) const = 0;

  protected:
    static constexpr int TOTAL_SHIPS = 6;

    std::unique_ptr<Ships::ship> ships[TOTAL_SHIPS];
    // Tracks attack positions already atttempted
    // eases the implementation of wasAttacked()
    std::set<pair<uint, uint>> alreadyAttacked;
    // Tracks positions already hit by the enemy
    // eases the implementation of wasDamaged()
    std::set<pair<uint, uint>> alreadyDamaged;

    // Set every char in the grid to EMPTY
    void initializeGrid();
    // Populate "ships" according to SHIP_TYPES & NUM_EACH_TYPE
    void initializeShips();

    // Check if a ship overflows the grid if put in a given position
    bool isOutOfBounds(const Ships::ship &ship,
                       const pair<uint, uint> &pos) const;
    // Check if a ship overlaps another ship
    bool isOverlaping(const Ships::ship &ship,
                      const pair<uint, uint> &pos) const;

    void insertShipInGrid(const Ships::ship &ship);

  public:
    char grid[ROWS][COLS]; // TODO: should use getters instead of being a public

    void printHeader() const;
    void printSeparator() const;

    bool wasAttacked(const pair<uint, uint> &position) const;
    bool wasDamaged(const pair<uint, uint> &position) const;

    virtual pair<uint, uint> chooseAttackPosition() = 0;
    // Try to match an attack with a cell from a ship, causing damage
    void takeDamage(const pair<uint, uint> &position);
    // Check if every ship was destroyed
    bool isDead() const;
};
} // namespace Players
#endif
