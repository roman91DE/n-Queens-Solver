#include "solution.h"

#ifndef SAHEADER
#define SAHEADER


class SA{

    private:
        Solution cur_sol, best_sol;
        int cur_fit, best_fit;
        int board_size;
        float t_start, t_end, t_cur;
        float alpha;


    public:
        SA(int _board_size, float _t_start, float _t_end, float _alpha);
        void run();
        void run_threaded();
        Solution run_return_only();
        void cooling();
        static void simulated_annealing();

};

#endif
