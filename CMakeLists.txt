cmake_minimum_required(VERSION 3.21.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall")

# generate file required by clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(main)

# enable debugging symbols for gdb when compiling with clang
# https://stackoverflow.com/a/47045466
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

add_executable(main ./src/main.cpp ./src/players/player.cpp ./src/players/human.cpp ./src/players/computer.cpp ./src/ship.cpp)

target_include_directories(main $ENV{INCLUDE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/ships ${CMAKE_CURRENT_SOURCE_DIR}/include/players)
