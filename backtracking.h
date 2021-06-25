#ifndef BACKTRACKINGHEADER
#define BACKTRACKINGHEADER

#include "solution.h"


class Backtracking {
    
    private:
        Solution sol;
        int board_size;
        int solution_counter;

    public:
        Backtracking(int _board_size);
        void run();
        static void exhaustive_backtracking();
};


#endif