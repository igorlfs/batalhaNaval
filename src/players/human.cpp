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
    char col = 'A';
    for (int i = 0; i < ROWS; ++i) {
        this->printSeparator();
        std::cout << ' ' << col << " │ ";
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
insertAgain:
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
        goto insertAgain;
    } catch (Input::invalidDirectionFormat e) {
        std::cout << "\nEntrada inválida: " << e.str
                  << "\nPor favor, insira a direção no seguinte formato: x\n"
                     "onde 'x' deve ser v ou h\n\n";
        goto insertAgain;
    } catch (Input::invalidDirection e) {
        std::cout << "\nEntrada inválida: " << e.str
                  << "\nVocê só pode escolher entre as direções 'v' e 'h'\n\n";
        goto insertAgain;
    }
}
uint parseLetter(const char letter) { return (uint)letter - 65; }
std::pair<uint, uint> human::chooseShipPosition(const ships::ship &ship) const {
insertAgain:
    try {
        std::regex expectedFormat("[A-Z][0-9]");
        std::string readLine;
        std::cout
            << "Escolha a posição de " << ship.getName()
            << "\nTamanho: " << ship.getSize()
            << "\nUma posição válida é composta por uma letra MAIÚSCULA e um "
               "número (necessariamente nessa ordem) juntos (sem espaços "
               "entre eles)\n"
               "Exemplos de posições válidas são: A2, C5, D4\n";
        std::getline(std::cin, readLine);
        if (std::cin.eof()) throw Input::interrupt();
        if (readLine.size() == 0) throw Input::emptyLine();
        if (!std::regex_match(readLine, expectedFormat))
            throw Input::invalidPositionFormat{readLine};
        std::stringstream ss(readLine);
        char row;
        uint column;
        ss >> row >> column;
        std::pair<uint, uint> position = {parseLetter(row), column - 1};
        if (((ship.getDirection() && ship.getSize() + position.second > ROWS) ||
             (!ship.getDirection() && ship.getSize() + position.first > COLS)))
            throw Input::shipOutOfBounds();
        if (isOverlaping(ship, position)) throw Input::shipOverlap();
        return position;
    } catch (Input::interrupt e) {
        std::cout << "\n\nA entrada de dados foi interrompida. Saindo.\n\n";
        exit(1);
    } catch (Input::emptyLine e) {
        std::cout << "\nNão foi informado nenhum dado."
                  << "\nPor favor, insira uma posição.\n\n";
        goto insertAgain;
    } catch (Input::invalidPositionFormat e) {
        std::cout << "\nEntrada inválida: " << e.str
                  << "\nPor favor, atente-se aos exemplos de entrada\n\n";
        goto insertAgain;
    } catch (Input::shipOutOfBounds e) {
        std::cout
            << "\nEntrada inválida: " << e.str
            << "\nO navio é muito grande para ser inserido nesta posição.\n\n";
        goto insertAgain;
    } catch (Input::shipOverlap e) {
        std::cout
            << "\nEntrada inválida: " << e.str
            << "\nVocê não pode inserir um navio em cima de outro navio.\n\n";
        goto insertAgain;
    }
}
void human::removeShipFromGrid(ships::ship *ship) {
    std::vector<std::pair<uint, uint>> shipPos = ship->getLocation();
    for (unsigned k = 0; k < shipPos.size(); ++k) {
        this->grid[shipPos[k].first][shipPos[k].second] = EMPTY;
    }
    ship->clearCells();
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
