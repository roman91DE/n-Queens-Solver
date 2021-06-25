#include "solution.h"
#include "population.h"
#include "evolution.h"
#include "backtracking.h"
#include <iostream>


int main() {
    bool terminate{false};
    int choice{0};

    while (!(terminate)) {
        std::cout << "\nSolving the n-Queens Problem\n---------\nChoose method of computation:\n"
                  << "1 - Evolutionary Algorithm\n2 - Backtracking Algorithm \n3 - Exit Programm\n";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            EA::evolutionary_algorithm();
            break;
        
        case 2:
            Backtracking::exhaustive_backtracking();
            break;

        case 3:
            terminate = true;
            break;

        default:
            std::cout << "Invalid Input, please try again\n";
            break;
        }  
    }
}