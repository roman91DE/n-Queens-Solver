#include "solution.h"
#include "population.h"
#include <iostream>


// int main() {

//     Solution mom = Solution(10,0.5,0.999);
//     Solution dad = Solution(10,0.5,0.999);
//     mom.debug_print();
//     mom.print();

//     dad.debug_print();
//     dad.print();

//     Solution child = Solution::onepoint_crossover(mom, dad);
//     child.debug_print();
//     child.print();

//     return 0;
// }


int main() {
    Population p = Population(6,10,true, .5,.5);
    std::cout << "Before sorting:\n";
    p.print_fit_debug();
    p.sort();
    std::cout << "After sorting:\n";
    p.print_fit_debug();
    std::cout << "Average Fitness;" << p.calc_avr() << std::endl;
    std::cout << "Random Solution: \n";
    Solution zv = p.rand_select();
    zv.debug_print();
    return 0;

}