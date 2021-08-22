#include "computer.hpp"
#include "human.hpp"
#include <iostream>
void printTrackingGrid(const players::player &tracked,
                       const players::player &traking);
void printPrimaryGrid(const players::player &defender,
                      const players::player &enemy);
int main() {
    // TODO:
    //
    // Correct input
    // Colors
    //
    // Fix magic chars
    // Improve interrupting execution;
    // Message displaying when a ship was destryoed
    // Win condition
    // Explain how to play the game
    players::human person;
    players::computer cpu;
    while (1) {
        printTrackingGrid(cpu, person);
        person.attack(cpu);
        cpu.attack(person);
        printPrimaryGrid(person, cpu);
    }
    return 0;
}
void printTrackingGrid(const players::player &tracked,
                       const players::player &traking) {
    tracked.printHeader();
    char col = '0';
    for (int i = 0; i < players::ROWS; ++i) {
        tracked.printSeparator();
        std::cout << ' ' << col << " │ ";
        for (int j = 0; j < players::COLS; ++j) {
            if (traking.wasAnAttempt({i, j})) {
                (tracked.isHit({i, j})) ? std::cout << 'H' : std::cout << 'X';
            } else
                std::cout << 'O'; // Use empty char?
            if (j != players::COLS - 1)
                std::cout << " │ ";
        }
        ++col;
        std::cout << std::endl;
    }
    std::cout << std::endl;
    // Stop execution to analize stuff
    std::cin >> col;
}
void printPrimaryGrid(const players::player &person,
                      const players::player &enemy) {
    person.printHeader();
    char col = '0';
    for (int i = 0; i < players::ROWS; ++i) {
        person.printSeparator();
        std::cout << ' ' << col << " │ ";
        for (int j = 0; j < players::COLS; ++j) {
            if (enemy.wasAnAttempt({i, j})) {
                (person.isHit({i, j})) ? std::cout << 'H' : std::cout << 'X';
            } else
                std::cout << person.grid[i][j];
            if (j != players::COLS - 1)
                std::cout << " │ ";
        }
        ++col;
        std::cout << std::endl;
    }
    std::cout << std::endl;
    // Stop execution to analize stuff
    std::cin >> col;
}
