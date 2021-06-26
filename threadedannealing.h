#ifndef MAHEADER
#define MAHEADER

#include "simulatedannealing.h"
#include "threadedannealing.h"
#include "solution.h"
#include <vector>
#include <thread>
#include <future>


class MA{

    private:
        unsigned int num_threads;
        std::vector < std::future <Solution> > vec;
        int board_size;
        float t_start, t_end, t_cur;
        float alpha;
    public:
        MA (int _board_size, float _t_start, float _t_end, float _alpha);
        void run_threads();
        static void multithreaded_annealing();
};


#endif