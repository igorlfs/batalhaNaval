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
static constexpr int ROWS = 6;
static constexpr int COLS = 6;
class player {
  private:
    static constexpr int SHIP_TYPES = 5;
    static constexpr int NUM_EACH_SHIP[SHIP_TYPES] = {1, 1, 1, 1, 2};

    // Lembre-se de inicializar as funções virtuais!
    // O linkador espera que elas estejam definidas em algum momento do programa
    // Um jeito de fazer isso é usando esse '= 0'
    virtual bool isOutOfBounds(const ships::ship &ship,
                               const std::pair<uint, uint> &pos) const = 0;
    virtual bool isOverlaping(const ships::ship &ship,
                              const std::pair<uint, uint> &pos) const = 0;
    virtual std::pair<uint, uint>
    choosePosition(const ships::ship &ship) const = 0;

  protected:
    static constexpr int TILES = ROWS * COLS;
    static constexpr double MAX_OCCUPABLE = 0.8;

    static constexpr int TOTAL_SHIPS = 6;

    static constexpr char EMPTY = ' ';

    // Segundo a wikipédia, o jogo original conta com
    // 1 carrier, 2 battleships, 3 destroyers, 4 submarines, 5 patrolBoats
    // (mas isso fica meio chato de colocar no terminal)
    ships::ship *ships[TOTAL_SHIPS];

    void initializeBoard();
    void initializeShips();

    bool isThereEnoughSpace() const;

    void addShipToGrid(const ships::ship &ship);

    virtual bool
    isAttemptRepeated(const std::pair<uint, uint> &position) const = 0;

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
};
} // namespace players
#endif
