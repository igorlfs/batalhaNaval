#include "human.hpp"
#include "handleInput.hpp"
#include <iostream>
#include <regex>
using namespace players;
human::human() {
    this->initializeGrid();
    this->initializeShips();
    for (int i = 0; i < TOTAL_SHIPS; ++i) {
        /* restartPosition: */
        this->printContructionGrid();
        this->ships[i]->setDirection(chooseDirection(*this->ships[i]));
        this->ships[i]->setCells(choosePosition(*this->ships[i]));
        this->insertShipInGrid(*this->ships[i]);
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
insertDirectionAgain:
    try {
        // regex: a letter between an arbitraty number of spaces
        std::regex expectedFormat("\\s*\\w\\s*");
        char direction;
        std::string readLine;
        std::cout
            << "Escolha a direção de " << ship.getName()
            << "\nTamanho: " << ship.getSize()
            << "\nVocê pode escolher entre vertical (v) ou horizontal (h): ";
        std::getline(std::cin, readLine);
        if (std::cin.eof()) throw Input::interrupt();
        if (readLine.size() == 0) throw Input::emptyLine();
        if (!std::regex_match(readLine, expectedFormat))
            throw Input::invalidDirectionFormat{readLine};
        std::stringstream ss(readLine);
        ss >> direction;
        if (direction != 'v' && direction != 'h')
            throw Input::invalidDirection{readLine};
        return direction;
    } catch (Input::interrupt e) {
        std::cout << "\n\nA entrada de dados foi interrompida. Saindo.\n\n";
        exit(1);
    } catch (Input::emptyLine e) {
        std::cout << "\nNão foi informado nenhum dado."
                  << "\nPor favor, insira uma direção.\n\n";
        goto insertDirectionAgain;
    } catch (Input::invalidDirectionFormat e) {
        std::cout << "\nEntrada inválida: " << e.str
                  << "\nPor favor, insira a direção no seguinte formato: x\n"
                     "onde 'x' deve ser v ou h\n\n";
        goto insertDirectionAgain;
    } catch (Input::invalidDirection e) {
        std::cout << "\nEntrada inválida: " << e.str
                  << "\nVocê só pode escolher entre as direções 'v' e 'h'\n\n";
        goto insertDirectionAgain;
    }
}
std::pair<uint, uint> human::chooseShipPosition(const ships::ship &ship) const {
    std::pair<uint, uint> position;
    std::cout << "Escolha a posição do '" << ship.getName() << "': ";
    do {
        std::cin >> position.first >> position.second;
    } while (this->isOutOfBounds(ship, position) == true ||
             this->isOverlaping(ship, position) == true);
    return position;
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
    std::pair<uint, uint> position;
    do {
        std::cin >> position.first >> position.second;
    } while (this->isOutOfBounds(ship, position) == true ||
             this->isOverlaping(ship, position) == true);
    return position;
}
std::pair<uint, uint> human::chooseAttackPosition() {
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
bool human::isAttackRepeated(const std::pair<uint, uint> &position) const {
    if (this->alreadyAttacked.find(position) != this->alreadyAttacked.end()) {
        std::cout << "Você já atacou aqui! Escolha outro lugar: ";
        return true;
    }
    return false;
}
