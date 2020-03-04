# Sudoku Solver sample
I worked on this as a leetcode practice and decided to write it as offline
program for ease of access. This solver *should* find the correct solution if
it exists. I haven't run it through an exhaustive list of sudoku puzzles to
look for edges cases though.

# Demo
This demo requires a Linux environment. If on Windows, checkout MSYS2
[here](https://www.msys2.org/). This demo requires g++ compiler.
clang.

On a Linux system, run `./compile.sh sudoku-solver.cpp < solver-input[2].txt`.

Each solver input text file contains the puzzle on the first line and the
solution on the second line for validation.

# Explanation
`main()` reads 81 numbers representing the puzzle to be solved from stdin and formats that into a 2D vector for
input into the solver. It then reads 81 numbers representing the solved puzzle
for validating the solver.

The solver relies on recursing via `Solution::solverHelper` to do depth-first
search in the solution tree.  It tracks board index from top-left to
bottom-right in the solverHelper too.

The solver relies on `Solution::isValidSudoku` to validate that a solution is possible.

