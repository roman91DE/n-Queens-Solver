#include "backtracking.h"
#include <iostream>


Backtracking::Backtracking(int _board_size)
: board_size(_board_size), sol{Solution(board_size)} {}


void Backtracking::run() {
    char input;
    if (sol.is_solved()) {
        std::cout << "Found Solution!\n" << "len=" << sol.vec.size() << "\n";
        std::cout << sol.to_string() << "__sol__\n";
        std::cout << "Continue Backtracking?\n";
        std::cin >> input;
        return;
    }
    for (unsigned int i{0}; i<board_size; ++i) {
        if (sol.vec[i] == -1) {
            for (unsigned int n{0}; n<board_size; ++n) {
                if (sol.is_possible(n)) {
                    sol.place_queen(n,i);
                    sol.debug_print();
                    run();
                    sol.remove_queen(i);
                    return;
                }
            }
        }
    }
    return;
}