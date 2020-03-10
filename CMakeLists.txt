cmake_minimum_required(VERSION 3.10.2)

project(SudokuSolver CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")

include_directories(
    ${PROJECT_SOURCE_DIR}
)

set(SRCS
    "sudoku-solver.cpp"
    "solution.cpp"
)

set(BIN_NAME solver)

add_executable(solver
    ${SRCS}
)

add_custom_command(TARGET ${BIN_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${BIN_NAME} ${PROJECT_SOURCE_DIR}/${BIN_NAME}
)
