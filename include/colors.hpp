// https://stackoverflow.com/a/17469726
#ifndef COLORS_H
#define COLORS_H
#include <ostream>
namespace Color {
// "Abbreviate" reseting attributes
static const std::string RESET = "\e[0m";
enum Codes {
    FG_BLACK = 30,
    FG_RED = 31,
    FG_GREEN = 32,
    FG_YELLOW = 33,
    FG_BLUE = 34,
    FG_MAGENTA = 35,
    FG_CYAN = 36,
    BG_RED = 41,
    BG_GREEN = 42,
    BG_BLUE = 44,
    FG_WHITE = 97,
};
class Modifier {
    Codes code;

  public:
    Modifier(Codes pCode) : code(pCode) {}
    friend std::ostream &operator<<(std::ostream &os, const Modifier &mod) {
        return os << "\033[" << mod.code << "m";
    }
};
} // namespace Color
#endif
