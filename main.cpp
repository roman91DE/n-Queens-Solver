#include "solution.h"
#include "population.h"
#include "evolution.h"
#include <iostream>




int main() {
    EA ea = EA(6,40, 10, 2, 10000,0.05,0.95);
    //std::cout << "Constructor works\n";
    ea.run(true);
    return 0;
}