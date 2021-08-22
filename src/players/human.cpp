#include "human.hpp"
#include <iostream>
using namespace players;
human::human() {
    this->initializeBoard();
    this->initializeShips();
    for (int i = 0; i < TOTAL_SHIPS; ++i) {
        /* restartPosition: */
        this->printContructionGrid();
        this->ships[i]->setDirection(chooseDirection(*this->ships[i]));
        this->ships[i]->setCells(choosePosition(*this->ships[i]));
        this->addShipToGrid(*this->ships[i]);
        /* this->printGrid(); */
        /* std::cout<<"Você está feliz com a posição atual do barco? (S/n)\n" */
        /*            "Digite 'n' para selecionar uma nova orientação/posição:
         * "; */
        /* char changePos; */
        /* std::cin >> changePos; */
        /* if (changePos == 'n') { */
        /*   this->clearShip(this->ships[i]); */
        /*   goto restartPosition; */
        /* } */
    }
}
void human::printContructionGrid() const {
    this->printHeader();
    char col = '0';
    for (int i = 0; i < ROWS; ++i) {
        this->printSeparator();
        std::cout << ' ' << col;
        std::cout << " │ ";
        for (int j = 0; j < COLS; ++j) {
            std::cout << this->grid[i][j];
            if (j != COLS - 1) {
                std::cout << " │ ";
            }
        }
        ++col;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
char human::chooseDirection(const ships::ship &ship) const {
    char direc;
    do {
        std::cout << "Escolha a direção de '" << ship.getName() << "'(v/h): ";
        std::cin >> direc;
    } while (direc != 'v' && direc != 'h');
    return direc;
}
void human::clearShip(ships::ship *ship) {
    std::vector<std::pair<uint, uint>> shipPos = ship->getLocation();
    for (unsigned k = 0; k < shipPos.size(); ++k) {
        this->grid[shipPos[k].first][shipPos[k].second] = EMPTY;
    }
    ship->clearCells();
}
bool human::isOutOfBounds(const ships::ship &ship,
                          const std::pair<uint, uint> &pos) const {
    if ((ship.getDirection() && ship.getSize() + pos.second > ROWS) ||
        (!ship.getDirection() && ship.getSize() + pos.first > COLS)) {
        std::cout << "Navio não cabe aqui, escolha outra posição: ";
        return 1;
    }
    return 0;
}
bool human::isOverlaping(const ships::ship &ship,
                         const std::pair<uint, uint> &pos) const {
    ships::ship testShip = ship;
    testShip.setCells(pos);
    std::vector<std::pair<uint, uint>> positionCandidate =
        testShip.getLocation();
    for (unsigned k = 0; k < positionCandidate.size(); ++k) {
        if (this->grid[positionCandidate[k].first]
                      [positionCandidate[k].second] != EMPTY) {
            std::cout
                << "Você não pode inserir um navio em cima de outro navio.\n"
                   "Por favor, escolha outra posição: ";
            return 1;
        }
    }
    return 0;
}
std::pair<uint, uint> human::choosePosition(const ships::ship &ship) const {
    std::cout << "Escolha a posição do '" << ship.getName() << "': ";
    std::pair<uint, uint> position;
    do {
        std::cin >> position.first >> position.second;
    } while (this->isOutOfBounds(ship, position) == true ||
             this->isOverlaping(ship, position) == true);
    return position;
}
void human::attack(player &enemy) {
    std::pair<uint, uint> attackPosition;
    std::cout << "Escolha onde deseja atacar: ";
    do {
        std::cin >> attackPosition.first >> attackPosition.second;
    } while (isAttackOutOfBounds(attackPosition) == false ||
             isAttemptRepeated(attackPosition) == true);
    bombingAttempts.insert(attackPosition);
    enemy.wasHit(attackPosition);
}
bool human::isAttackOutOfBounds(
    const std::pair<uint, uint> &attackCandidate) const {
    if (attackCandidate.first >= ROWS || attackCandidate.second >= COLS) {
        std::cout << "Oops. Essa posição não está no campo inimigo\n"
                     "Escolha outra posição: ";
        return false;
    }
    return true;
}
bool human::isAttemptRepeated(const std::pair<uint, uint> &position) const {
    if (this->bombingAttempts.find(position) != this->bombingAttempts.end()) {
        std::cout << "Você já atacou nessa posição!\n"
                     "Por favor, escolha outra posição: ";
        return true;
    }
    return false;
}
