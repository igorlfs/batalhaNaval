#include "human.hpp"
#include "color.hpp"
#include "input.hpp"
#include <iostream>
#include <regex>
using namespace Players;
human::human() {
    this->initializeGrid();
    this->initializeShips();
    for (int i = 0; i < TOTAL_SHIPS; ++i) {
        this->printContructionGrid();
        this->ships[i]->setDirection(chooseDirection(*this->ships[i]));
        this->ships[i]->setCells(chooseShipPosition(*this->ships[i]));
        this->insertShipInGrid(*this->ships[i]);
    }
}
void human::printContructionGrid() const {
    this->printHeader();
    char col = 'A';
    for (int i = 0; i < ROWS; ++i) {
        this->printSeparator();
        std::cout << ' ' << col << Color::Modifier(Color::FG_CYAN) << " │ "
                  << Color::RESET;
        for (int j = 0; j < COLS; ++j) {
            (this->grid[i][j] == EMPTY)
                ? std::cout << Color::Modifier(Color::FG_BLUE) << EMPTY
                            << Color::RESET
                : std::cout << Color::Modifier(Color::FG_YELLOW)
                            << this->grid[i][j] << Color::RESET;
            if (j != COLS - 1) {
                std::cout << Color::Modifier(Color::FG_CYAN) << " │ "
                          << Color::RESET;
            }
        }
        ++col;
        std::cout.put('\n');
    }
    std::cout.put('\n');
}
char human::chooseDirection(const Ships::ship &ship) const {
insertAgain:
    try {
        // regex: a letter between an arbitrary number of spaces
        std::regex expectedFormat("\\s*\\w\\s*");
        char direction;
        std::string readLine;
        std::cout
            << "Escolha a direção de " << ship.getName()
            << "\nTamanho: " << ship.getSize()
            << "\nVocê pode escolher entre vertical (v) ou horizontal (h): ";
        std::getline(std::cin, readLine);
        if (std::cin.eof()) throw Input::interrupt();
        if (readLine.empty()) throw Input::emptyLine();
        if (!std::regex_match(readLine, expectedFormat))
            throw Input::invalidDirectionFormat{readLine};
        std::stringstream ss(readLine);
        ss >> direction;
        if (direction != Ships::directions[0] &&
            direction != Ships::directions[1])
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
                  << "\nA direção deve ser uma letra minúscula, a inicial da "
                     "direção desejada\n\n";
        goto insertAgain;
    } catch (Input::invalidDirection e) {
        std::cout << "\nEntrada inválida: " << e.str
                  << "\nVocê só pode escolher entre as direções vertical e "
                     "horizontal\n\n";
        goto insertAgain;
    }
}
uint parseLetter(const char letter) {
    // Subtract 65 from a letter to create the following map
    // A -> 0; B -> 1; C -> 2 ...
    return (uint)letter - 65;
}
pair<uint, uint> getPosition() {
insertPositionAgain:
    try {
        std::regex expectedFormat("[A-Z][1-9][0-9]*");
        std::string readLine;
        std::getline(std::cin, readLine);
        if (std::cin.eof()) throw Input::interrupt();
        if (readLine.empty()) throw Input::emptyLine();
        if (!std::regex_match(readLine, expectedFormat))
            throw Input::invalidPositionFormat{readLine};
        std::stringstream ss(readLine);
        char row;
        uint column;
        ss >> row >> column;
        return {parseLetter(row), column - 1};
    } catch (Input::interrupt e) {
        std::cout << "\n\nA entrada de dados foi interrompida. Saindo.\n\n";
        exit(1);
    } catch (Input::emptyLine e) {
        std::cout << "\nNão foi informado nenhum dado."
                  << "\nPor favor, insira uma posição.\n\n";
        goto insertPositionAgain;
    } catch (Input::invalidPositionFormat e) {
        std::cout << "\nEntrada inválida: " << e.str
                  << "\nPor favor, atente-se aos exemplos de entrada.\n\n";
        goto insertPositionAgain;
    }
}
pair<uint, uint> human::chooseShipPosition(const Ships::ship &ship) const {
    std::cout << "Escolha a posição de " << ship.getName()
              << "\nTamanho: " << ship.getSize()
              << "\nUma posição válida é composta por uma letra MAIÚSCULA e um "
                 "número (necessariamente nessa ordem) juntos (sem espaços "
                 "entre eles).\n"
                 "O número deve ser natural (excluindo o 0).\n"
                 "Exemplos de posições válidas são: A2, C5, D4\n";
insertAgain:
    try {
        pair<uint, uint> position = getPosition();
        if (isOutOfBounds(ship, position)) throw Input::shipOutOfBounds();
        if (isOverlaping(ship, position)) throw Input::shipOverlap();
        return position;
    } catch (Input::shipOutOfBounds e) {
        std::cout
            << "\nO navio é muito grande para ser inserido nesta posição.\n\n";
        goto insertAgain;
    } catch (Input::shipOverlap e) {
        std::cout
            << "\nVocê não pode inserir um navio em cima de outro navio.\n\n";
        goto insertAgain;
    }
}
void human::removeShipFromGrid(Ships::ship *ship) {
    std::vector<pair<uint, uint>> shipPos = ship->getLocation();
    for (unsigned k = 0; k < shipPos.size(); ++k) {
        this->grid[shipPos[k].first][shipPos[k].second] = EMPTY;
    }
    ship->clearCells();
}
pair<uint, uint> human::chooseAttackPosition() {
    std::cout << "\nEscolha em qual posição deseja atacar: ";
insertAgain:
    try {
        pair<uint, uint> position = getPosition();
        if (position.first >= ROWS || position.second >= COLS)
            throw Input::attackOutOfBounds();
        if (this->alreadyAttacked.find(position) != this->alreadyAttacked.end())
            throw Input::attackRepeated();
        this->alreadyAttacked.insert(position);
        return position;
    } catch (Input::attackOutOfBounds e) {
        std::cout << "\nOops. Essa posição não está no campo inimigo.\n\n";
        goto insertAgain;
    } catch (Input::attackRepeated e) {
        std::cout << "\nOops. Você já atacou essa posição.\n\n";
        goto insertAgain;
    }
}
