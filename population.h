#ifndef POPULATIONHEADER
#define POPULATIONHEADER


#include "solution.h"
#include <vector>
#include <string>


class Population{

    private:
        std::vector<Solution> vec;
        float average_fit;
    public:
        Population(int _dimension, int _size, float m_rate, float c_rate);
        Population();
        void add_solution(const Solution &_solution);
        void sort();
        float calc_avr();
        const Solution& rand_select() const;
        const Solution& best_select();
        void print_fit_debug() const;
        int get_size() const;
        

    friend class EA;

};


#endif