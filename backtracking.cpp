#include "backtracking.h"
#include <iostream>
#include <chrono>


Backtracking::Backtracking(int _board_size)
: board_size(_board_size), sol{Solution(board_size)}, solution_counter(0) {
    sol = Solution(board_size);
}


void Backtracking::run() {
    char flag;
    if (sol.is_solved()) {
        ++solution_counter;
        std::cout << "Solution " << solution_counter;
        sol.print();
        return;
    }
    for (unsigned int i{0}; i<board_size; ++i) {
        if (sol.vec[i] == -1) {
            for (unsigned int n{0}; n<board_size; ++n) {
                if (sol.is_possible(n)) {
                    sol.place_queen(n,i);
                    run();
                    sol.remove_queen(i);
                }
            }
            return;
        }
    }
    std::cin >> flag;
}

void Backtracking::exhaustive_backtracking() {

    int boardSize;

    std::cout << "\nSolve the n-Queens problems using an exhaustive Backtracking Algorithm\n-----"
              << "\nEnter Board Size: ";
    std::cin >> boardSize;
    std::cout << "\nStarting exhaustive Search\n";

    Backtracking b = Backtracking(boardSize);
    auto t0 = std::chrono::high_resolution_clock::now();
    b.run();
    auto t = std::chrono::high_resolution_clock::now();
    int time_consumed = std::chrono::duration_cast <std::chrono::milliseconds>(t - t0).count();
    std::cout << "Total Time consumed to find all solutions: " << time_consumed << " miliseconds\n";
}