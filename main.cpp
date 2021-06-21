#include "solution.h"


int main() {

    Solution s = Solution(10,.1, .9);
    s.debug_print();
    for (unsigned int j=0; j<10; ++j) {
        s.swap_mutation();
        s.debug_print();

    }
    return 0;
}