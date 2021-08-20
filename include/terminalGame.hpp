#ifndef TERMINAL_GAME_H
#define TERMINAL_GAME_H

class terminalGame {
public:
  static constexpr int ROWS = 10;
  static constexpr int COLUMNS = 10;

  static constexpr char EMPTY = ' ';

  terminalGame();
  void printBoard() const;
  bool checkValidMove(const int &moveColunm) const;
  void updateBoard(const int &moveColunm, const char &playerColor);
  bool checkWin(const char &playerColor) const;
  void setPlayers(const char &player, const int &i);
  char getPlayers(const int &i) const;

private:
  char arena[ROWS][COLUMNS];
  char players[2];
};
#endif
