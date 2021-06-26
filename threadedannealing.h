#ifndef MAHEADER
#define MAHEADER

#include "simulatedannealing.h"
#include "threadedannealing.h"
#include "solution.h"
#include <vector>
#include <thread>


class MA{

    private:
        unsigned int num_threads;
        std::vector <std::thread> vec;

    public:
};


#endif