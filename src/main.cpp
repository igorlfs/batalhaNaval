#include "color.hpp"
#include "computer.hpp"
#include "human.hpp"
#include "input.hpp"
#include <iostream>
void printTrackingGrid(const Players::player &tracked,
                       const Players::player &traking);
void printPrimaryGrid(const Players::player &defender,
                      const Players::player &enemy);
void waitForEnter();
void welcome() {
    std::cout
        << "Olá, jogador!\n"
        << "Nessa implementação do Batalha Naval, você enfrenta o computador!\n"
        << "Não se preocupe, ele não é um oponenete muito sagaz!\n\n"
        << "O jogo é dividido em duas etapas:\n"
        << "1) Colocar seus navios no SEU campo.\n"
        << "(você escolhe uma direção e uma posição onde ficará a cabeça)\n"
        << "2) Escolher posições para tentar destruir os navios inimigos.\n\n"
        << "O seu oponente terá as mesmas tarefas que você.\n"
        << "Quando ele te atacar, você vai acompanhar o estado do seu campo!\n"
        << "Tudo certo?\n";
}
int main() {
    // TODO: tests?
    welcome();
    waitForEnter();
    Players::human person;
    Players::computer cpu;
    for (int i = 0; i < Players::TILES; ++i) {
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
void printTrackingGrid(const Players::player &tracked,
                       const Players::player &traking) {
    std::cout << "\nIsso é o que você já sabe do campo inimigo:\n\n";
    tracked.printHeader();
    char column = 'A';
    for (int i = 0; i < Players::ROWS; ++i) {
        tracked.printSeparator();
        std::cout << ' ' << column << Color::Modifier(Color::FG_CYAN) << " │ "
                  << Color::RESET;
        for (int j = 0; j < Players::COLS; ++j) {
            if (traking.wasAttacked({i, j})) {
                (tracked.wasDamaged({i, j}))
                    ? std::cout << Color::Modifier(Color::FG_GREEN) << 'H'
                                << Color::RESET
                    : std::cout << Color::Modifier(Color::FG_RED) << 'X'
                                << Color::RESET;
            } else
                std::cout << Color::Modifier(Color::FG_BLUE) << Players::EMPTY
                          << Color::RESET;
            if (j != Players::COLS - 1)
                std::cout << Color::Modifier(Color::FG_CYAN) << " │ "
                          << Color::RESET;
        }
        ++column;
        std::cout.put('\n');
    }
}
void printPrimaryGrid(const Players::player &person,
                      const Players::player &enemy) {
    std::cout << "\nO inimigo te atacou!\nSeu campo está assim agora:\n\n";
    person.printHeader();
    char column = 'A';
    for (int i = 0; i < Players::ROWS; ++i) {
        person.printSeparator();
        std::cout << ' ' << column << Color::Modifier(Color::FG_CYAN) << " │ "
                  << Color::RESET;
        for (int j = 0; j < Players::COLS; ++j) {
            if (enemy.wasAttacked({i, j})) {
                (person.wasDamaged({i, j}))
                    ? std::cout << Color::Modifier(Color::FG_GREEN) << 'H'
                                << Color::RESET
                    : std::cout << Color::Modifier(Color::FG_RED) << 'X'
                                << Color::RESET;
            } else if (person.grid[i][j] == Players::EMPTY) {
                std::cout << Color::Modifier(Color::FG_BLUE) << Players::EMPTY
                          << Color::RESET;
            } else {
                std::cout << Color::Modifier(Color::FG_YELLOW)
                          << person.grid[i][j] << Color::RESET;
            }
            if (j != Players::COLS - 1)
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
