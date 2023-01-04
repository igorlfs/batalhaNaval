# Directories
BUILD_DIR = obj
SRC_DIR = src
LIB_DIR = include

# Compiler
CXX = clang++

# Flags: Compile, more warnings, use C++20, enable debugging symbols and include path
CXXFLAGS = -c -Wall -Wextra -Wshadow -Wpedantic -std=c++20 -g -fstandalone-debug -I$(LIB_DIR)

# Binaries
TARGET = binary
TESTS = tests

# Source
CPP_SOURCE = $(wildcard $(SRC_DIR)/ship.cpp $(SRC_DIR)/players/*)
 
# Headers
HPP_SOURCE = $(wildcard $(LIB_DIR)/* $(LIB_DIR)/ships/* $(LIB_DIR)/players/*)
SHIPS = $(wildcard $(LIB_DIR)/ships/*)
 
# Objects
OBJ = $(subst .cpp,.o,$(subst $(SRC_DIR),$(BUILD_DIR),$(CPP_SOURCE)))
 
# Compilation and linking
all: obj $(TARGET)

$(TARGET): $(OBJ) $(BUILD_DIR)/main.o
	$(CXX) $^ -o $@

$(BUILD_DIR)/ship.o: ./$(SRC_DIR)/ship.cpp $(SHIPS)
	$(CXX) $< $(CXXFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(LIB_DIR)/%.hpp
	$(CXX) $< $(CXXFLAGS) -o $@
 
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(HPP_SOURCE)
	$(CXX) $< $(CXXFLAGS) -o $@

obj:
	@ test -d $(BUILD_DIR) && true || mkdir -p $(BUILD_DIR)/players
 
clean:
	@ test -d $(BUILD_DIR) && rm -rf ./$(BUILD_DIR)/* *~ || echo "Nothing to clean"
	@ test -d $(BUILD_DIR) && rmdir $(BUILD_DIR)
 
.PHONY: all clean obj
