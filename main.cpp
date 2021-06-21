#include "solution.h"


int main() {

    Solution mom = Solution(10,0.5,0.999);
    Solution dad = Solution(10,0.5,0.999);
    mom.debug_print();
    dad.debug_print();

    Solution child = Solution::onepoint_crossover(mom, dad);
    child.debug_print();
    
    return 0;
}