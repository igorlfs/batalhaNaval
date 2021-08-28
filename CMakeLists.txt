cmake_minimum_required(VERSION 3.21.1)

project(main)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall")

# enable debugging
# https://stackoverflow.com/a/47045466
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

add_executable(main ./src/main.cpp ./src/players/player.cpp ./src/players/human.cpp ./src/players/computer.cpp ./src/ship.cpp)

target_include_directories(main $ENV{INCLUDE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/include/ships ${CMAKE_CURRENT_SOURCE_DIR}/include/players)

# generate file required by Language Server Protocol
# 
# Can be a little buggy (ie, won't generate said file)
# if given no parameters (ie, set(CMAKE_EXPORT_COMPILE_COMMANDS ON))
# requires a workaround provided by the following answer:
# https://stackoverflow.com/a/66560758
#
# However, even with said workaround, it still won't generate the file
# when running cmake for the first time in a project. Running cmake 
# subsequently will generate the file.
# 
# Perhaps when I in fact learn cmake I'll find a better workaround.
# Perhaps should use set everything before and then do other things?
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
