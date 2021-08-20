#include "player.hpp"
#include <iostream>
void player::initializeBoard() {
  for (int i = 0; i < ROWS; ++i) {
    for (int j = 0; j < COLS; ++j) {
      this->board[i][j] = EMPTY;
    }
  }
}
void player::printHeader() const {
  // Print natural counting header (starting at 1)
  for (int i = 0; i < COLS + 1; ++i) {
    (i == 0)      ? std::cout << "  "
    : (i == COLS) ? std::cout << 'X'
                  : std::cout << i - 1;
    if (i != COLS) {
      std::cout << " │ ";
    }
  }
  std::cout << std::endl;
}
void player::printSeparator() const {
  for (int i = 0; i < COLS + 1; ++i) {
    if (i == 0) {
      std::cout << "───┼";
    } else if (i == COLS) {
      std::cout << "───";
    } else {
      std::cout << "───┼";
    }
  }
  std::cout << std::endl;
}
void player::printBoard() const {
  this->printHeader();
  char col = '0';
  for (int i = 0; i < ROWS; ++i) {
    this->printSeparator();
    std::cout << ' ' << col;
    std::cout << " │ ";
    for (int j = 0; j < COLS; ++j) {
      std::cout << this->board[i][j];
      if (j != COLS - 1) {
        std::cout << " │ ";
      }
    }
    ++col;
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
char chooseDirection(const ships::ship &ship) {
readDirection:
  std::cout << "Escolha a direção de '" << ship.getName() << "'(v/h): ";
  char direc;
  std::cin >> direc;
  if (direc != 'v' && direc != 'h') {
    goto readDirection;
  }
  return direc;
}
std::pair<int, int> player::choosePosition(const ships::ship &ship) const {
  std::cout << "Escolha a posição do '" << ship.getName() << "': ";
  std::pair<int, int> pos;
  do {
    std::cin >> pos.first >> pos.second;
  } while (this->isOutOfBounds(ship, pos) == true ||
           this->isOverlaping(ship, pos) == true);
  return pos;
}
bool player::isOutOfBounds(const ships::ship &ship,
                           const std::pair<int, int> &pos) const {
  if ((ship.getDirection() && ship.getSize() + pos.second > ROWS) ||
      (!ship.getDirection() && ship.getSize() + pos.first > COLS)) {
    std::cout << "Navio não cabe aqui, escolha outra posição: ";
    return 1;
  }
  return 0;
}
bool player::isOverlaping(const ships::ship &ship,
                          const std::pair<int, int> &pos) const {
  ships::ship testShip = ship;
  testShip.setPosition(pos);
  std::vector<std::pair<int, int>> positionCandidate = testShip.getPosition();
  for (unsigned k = 0; k < positionCandidate.size(); ++k) {
    if (this->board[positionCandidate[k].first][positionCandidate[k].second] !=
        EMPTY) {
      std::cout << "Você não pode inserir um navio em cima de outro navio.\n"
                   "Por favor, escolha outra posição: ";
      return 1;
    }
  }
  return 0;
}
void player::clearShip(ships::ship *ship) {
  std::vector<std::pair<int, int>> shipPos = ship->getPosition();
  for (unsigned k = 0; k < shipPos.size(); ++k) {
    this->board[shipPos[k].first][shipPos[k].second] = EMPTY;
  }
  ship->clearLocation();
}
void player::updateBoard(ships::ship &ship) {
  std::vector<std::pair<int, int>> shipPos = ship.getPosition();
  char shipName = ship.getName()[0];
  for (unsigned k = 0; k < shipPos.size(); ++k) {
    this->board[shipPos[k].first][shipPos[k].second] = shipName;
  }
}
player::player() {
  this->initializeBoard();
  this->ships[0] = new ships::carrier;
  this->ships[1] = new ships::battleship;
  this->ships[2] = new ships::destroyer;
  this->ships[3] = new ships::submarine;
  this->ships[4] = new ships::patrolBoat;
  this->ships[5] = new ships::patrolBoat;
  for (int i = 0; i < TOTAL_SHIPS; ++i) {
  restartPosition:
    this->printBoard();
    this->ships[i]->setDirection(chooseDirection(*this->ships[i]));
    this->ships[i]->setPosition(choosePosition(*this->ships[i]));
    this->updateBoard(*this->ships[i]);
    this->printBoard();
    std::cout << "Você está feliz com a posição atual do barco? (S/n)\n"
                 "Digite 'n' para selecionar uma nova orientação/posição: ";
    char changePos;
    std::cin >> changePos;
    if (changePos == 'n') {
      this->clearShip(this->ships[i]);
      goto restartPosition;
    }
  }
}
player::~player() {
  for (int i = 0; i < TOTAL_SHIPS; ++i) {
    delete ships[i];
  }
}
