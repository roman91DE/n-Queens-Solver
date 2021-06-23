#include "solution.h"
#include "population.h"
#include "evolution.h"
#include <iostream>




int main() {
    int boardSize       = 32;
    int mainPopSize     = 80;
    int breadingPopSize = 20;
    int tournamentSize  = 4;
    int time_limit_sec = 60;
    int eliteSize       = 4;
    float mutateRate    = .05;
    float crossoverRate = .95;
    bool logResults     = false;
    char log;

    std::cout << "\nSolve the n-Queens problems using an Evolutionaty Algorithm\n-----"
              << "\nEnter Board Size: ";
    std::cin >> boardSize;

    std::cout << "\nEnter the maximum time limit (in seconds):";
    std::cin >> time_limit_sec;

    std::cout << "\nLog stats to external file?[y/n]";
    std::cin >> log;
    if ((log=='y') || (log == 'Y')) {logResults==true;}

    std::cout << "\nStarting Evolution\n";
    
    EA ea = EA(boardSize, mainPopSize, breadingPopSize, tournamentSize, time_limit_sec, eliteSize, mutateRate, crossoverRate);
    ea.run(logResults);

    return 0;
}