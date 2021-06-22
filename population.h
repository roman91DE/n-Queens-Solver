#ifndef POPULATIONHEADER
#define POPULATIONHEADER


#include "solution.h"
#include <vector>
#include <string>


class Population{

    private:
        std::vector<Solution> vec;
        int population_size, dimension;
        float average_fit;

    public:
        Population(int _dimension, int _size, bool init, float m_rate, float c_rate);
        void sort();
        float calc_avr();
        const Solution& rand_select() const;
        void print_fit_debug() const;
        

    friend class Solution;
    friend class EA;

};


#endif