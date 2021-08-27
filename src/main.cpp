#include "colors.hpp"
#include "computer.hpp"
#include "handleInput.hpp"
#include "human.hpp"
#include <iostream>
// Remove these functions from main and implement them as member functions
void printTrackingGrid(const players::player &tracked,
                       const players::player &traking);
// Might wanna find a hacky way to merge this function with
// printContructionGrid()
void printPrimaryGrid(const players::player &defender,
                      const players::player &enemy);
void waitForEnter();
int main() {
    // TODO:
    //
    // Simplify getting position
    // Explain how to play the game
    // change namespaces to use Uppercase
    // Fix magic chars; use true/false insted of 1/0;
    players::human person;
    players::computer cpu;
    for (int i = 0; i < players::TILES; ++i) {
        printTrackingGrid(cpu, person);
        cpu.takeDamage(person.chooseAttackPosition());
        if (cpu.isDead()) {
            std::cout << "Parabéns jogador, você derrotou o computador!\n";
            break;
        }
        person.takeDamage(cpu.chooseAttackPosition());
        printPrimaryGrid(person, cpu);
        if (person.isDead()) {
            std::cout << "\nO computador venceu! Mais sorte na próxima vez!\n";
            break;
        }
    }
    return 0;
}
void printTrackingGrid(const players::player &tracked,
                       const players::player &traking) {
    std::cout << "\nIsso é o que você já sabe do campo inimigo:\n\n";
    tracked.printHeader();
    char column = 'A';
    for (int i = 0; i < players::ROWS; ++i) {
        tracked.printSeparator();
        std::cout << ' ' << column << Color::Modifier(Color::FG_CYAN) << " │ "
                  << Color::RESET;
        for (int j = 0; j < players::COLS; ++j) {
            if (traking.wasAttacked({i, j})) {
                (tracked.wasDamaged({i, j}))
                    ? std::cout << Color::Modifier(Color::FG_GREEN) << 'H'
                                << Color::RESET
                    : std::cout << Color::Modifier(Color::FG_RED) << 'X'
                                << Color::RESET;
            } else
                std::cout << Color::Modifier(Color::FG_BLUE) << players::EMPTY
                          << Color::RESET;
            if (j != players::COLS - 1)
                std::cout << Color::Modifier(Color::FG_CYAN) << " │ "
                          << Color::RESET;
        }
        ++column;
        std::cout.put('\n');
    }
}
void printPrimaryGrid(const players::player &person,
                      const players::player &enemy) {
    std::cout << "\nO inimigo te atacou!\nSeu campo está assim agora:\n\n";
    person.printHeader();
    char column = 'A';
    for (int i = 0; i < players::ROWS; ++i) {
        person.printSeparator();
        std::cout << ' ' << column << Color::Modifier(Color::FG_CYAN) << " │ "
                  << Color::RESET;
        for (int j = 0; j < players::COLS; ++j) {
            if (enemy.wasAttacked({i, j})) {
                (person.wasDamaged({i, j}))
                    ? std::cout << Color::Modifier(Color::FG_GREEN) << 'H'
                                << Color::RESET
                    : std::cout << Color::Modifier(Color::FG_RED) << 'X'
                                << Color::RESET;
            } else if (person.grid[i][j] == players::EMPTY) {
                std::cout << Color::Modifier(Color::FG_BLUE) << players::EMPTY
                          << Color::RESET;
            } else {
                std::cout << Color::Modifier(Color::FG_YELLOW)
                          << person.grid[i][j] << Color::RESET;
            }
            if (j != players::COLS - 1)
                std::cout << Color::Modifier(Color::FG_CYAN) << " │ "
                          << Color::RESET;
        }
        ++column;
        std::cout.put('\n');
    }
    waitForEnter();
}
void waitForEnter() {
    std::cout << "\nAperte enter para continuar.";
    try {
        std::cin.get();
        if (std::cin.eof()) throw Input::interrupt();
    } catch (Input::interrupt e) {
        std::cout << "\n\nA entrada de dados foi interrompida. Saindo.\n\n";
        exit(1);
    }
}
