#include "computer.hpp"
#include "human.hpp"
#include <iostream>
void printAttackBoard(const players::player &defender,
                      const players::player &attacker);
void printDefenseBoard(const players::player &defender,
                       const players::player &attacker);
int main() {
  // TODO:
  //
  // Change ship's state when attacking
  // Was target hit?
  //
  // Win condition
  // Consider using unsigned for pairs
  // Correct input
  // Colors
  players::human person;
  players::computer cpu;
  players::computer cpu2;
  while (1) {
    printAttackBoard(cpu, person);
    person.attack();
    cpu.attack();
    printDefenseBoard(person, cpu);
  }
  return 0;
}
void printAttackBoard(const players::player &defender,
                      const players::player &attacker) {
  defender.printHeader();
  char col = '0';
  for (int i = 0; i < players::ROWS; ++i) {
    defender.printSeparator();
    std::cout << ' ' << col;
    std::cout << " │ ";
    for (int j = 0; j < players::COLS; ++j) {
      if (attacker.wasAnAttempt({i, j})) {
        std::cout << 'x';
      } else {
        std::cout << 'o';
      }
      if (j != players::COLS - 1) {
        std::cout << " │ ";
      }
    }
    ++col;
    std::cout << std::endl;
  }
  std::cout << std::endl;
  // Stop execution to analize stuff
  std::cin >> col;
}
void printDefenseBoard(const players::player &defender,
                       const players::player &attacker) {
  defender.printHeader();
  char col = '0';
  for (int i = 0; i < players::ROWS; ++i) {
    defender.printSeparator();
    std::cout << ' ' << col;
    std::cout << " │ ";
    for (int j = 0; j < players::COLS; ++j) {
      if (attacker.wasAnAttempt({i, j})) {
        std::cout << 'x';
      } else {
        std::cout << defender.board[i][j];
      }
      if (j != players::COLS - 1) {
        std::cout << " │ ";
      }
    }
    ++col;
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
