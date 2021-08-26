#ifndef PLAYER_H
#define PLAYER_H
#include "battleship.hpp"
#include "carrier.hpp"
#include "destroyer.hpp"
#include "patrolBoat.hpp"
#include "submarine.hpp"
#include <set>
#include <string>
namespace players {
// Declared outside the class as they are used outside an instance of player
static constexpr int ROWS = 6;
static constexpr int COLS = 6;
static constexpr int TILES = ROWS * COLS;
class player {
  private:
    static constexpr int SHIP_TYPES = 5;
    static constexpr int NUM_EACH_TYPE[SHIP_TYPES] = {1, 1, 1, 1, 2};
    static constexpr double MAX_OCCUPABLE = 0.8;

    // Check if it's possible to fit all ships in the grid
    // Uses TILES & MAX_OCCUPABLE
    bool isThereEnoughSpace() const;

    virtual std::pair<uint, uint>
    chooseShipPosition(const ships::ship &ship) const = 0;

  protected:
    static constexpr int TOTAL_SHIPS = 6;
    static constexpr char EMPTY = ' ';

    ships::ship *ships[TOTAL_SHIPS];
    // Tracks attack positions already atttempted
    // eases the implementation of wasAttacked()
    std::set<std::pair<uint, uint>> alreadyAttacked;
    // Tracks positions already hit by the enemy
    // eases the implementation of wasDamaged()
    std::set<std::pair<uint, uint>> alreadyDamaged;

    // Set every char in the grid to EMPTY
    void initializeGrid();
    // Populate "ships" according to SHIP_TYPES & NUM_EACH_TYPE
    void initializeShips();

    // Check if a ship overflows the grid in a given position
    bool isOutOfBounds(const ships::ship &ship,
                       const std::pair<uint, uint> &pos) const;
    // Check if a ship overlaps another ship
    bool isOverlaping(const ships::ship &ship,
                      const std::pair<uint, uint> &pos) const;

    void insertShipInGrid(const ships::ship &ship);

    virtual ~player();

  public:
    char grid[ROWS][COLS];

    virtual void attack(player &enemy) = 0;

    std::set<std::pair<uint, uint>> bombingAttempts;
    bool wasAnAttempt(const std::pair<uint, uint> &cell) const;

    void wasHit(const std::pair<uint, uint> &position);
    std::set<std::pair<uint, uint>> hitByTheEnemey;
    bool isHit(const std::pair<uint, uint> &cell) const;

    void printHeader() const;
    void printSeparator() const;

    bool wasAttacked(const std::pair<uint, uint> &position) const;
    bool wasDamaged(const std::pair<uint, uint> &position) const;

    virtual std::pair<uint, uint> chooseAttackPosition() = 0;
    // Try to match an attack with a cell from a ship, causing damage
    void takeDamage(const std::pair<uint, uint> &position);
    bool isDead() const;
};
} // namespace players
#endif
