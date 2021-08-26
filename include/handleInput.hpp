#ifndef HANDLE_INPUT_H
#define HANDLE_INPUT_H
#include <iostream>
#include <regex>
#include <string>
namespace Input {
// regex: a letter between an arbitraty number of spaces
struct interrupt {};
struct emptyLine {};
struct invalidDirectionFormat {
    std::string str;
};
struct invalidDirection {
    std::string str;
};
struct invalidPositionFormat {
    std::string str;
};
struct shipOutOfBounds {};
struct shipOverlap {};
} // namespace Input
#endif
