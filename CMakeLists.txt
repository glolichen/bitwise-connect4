cmake_minimum_required(VERSION 3.0.0)
project(connect4 VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=undefined -Wall -Wextra -pedantic")

add_executable(connect4 bitmask.c bitboard.c main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
