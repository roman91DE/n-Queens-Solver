#include "solution.h"
#include "population.h"
#include "evolution.h"
#include <iostream>




int main() {
    int boardSize       = 40;
    int mainPopSize     = 80;
    int breadingPopSize = 20;
    int tournamentSize  = 4;
    int maxGenereations = 10000;
    int eliteSize       = 4;
    float mutateRate    = .08;
    float crossoverRate = .95;
    bool logResults     = true;


    EA ea = EA(boardSize, mainPopSize, breadingPopSize, tournamentSize, maxGenereations, eliteSize, mutateRate, crossoverRate);
    ea.run(logResults);

    return 0;
}