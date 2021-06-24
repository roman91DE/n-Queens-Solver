#ifndef BACKTRACKINGHEADER
#define BACKTRACKINGHEADER

#include "solution.h"


class Backtracking {
    
    private:
        Solution sol;
        int board_size;

    public:
        Backtracking(int _board_size);
        void run();
};


#endif