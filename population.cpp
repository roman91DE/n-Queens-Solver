#include "population.h"
#include "solution.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <random>
#include <cstdio>

Population::Population(int _dimension, int _size, bool init, float m_rate, float c_rate)
: dimension(_dimension), population_size(_size) {
    if (init) {
        for (unsigned int i{0}; i<population_size; ++i) {
            vec.push_back(Solution(dimension, m_rate, c_rate));
            }
    }
    average_fit = calc_avr();
}


void Population::sort() {
    std::sort(vec.rbegin(), vec.rend());
}


void Population::print_fit_debug() const{
    for (unsigned int i{0}; i<population_size; ++i) {
        printf("Fitness of Solution %d: %d\n", i, vec[i].fit);
    }
}

float Population::calc_avr() {
    int sum{0};
    for (auto &it:vec) {
        sum+= it.fit;
    }
    return (float(sum) / float(population_size));
}

const Solution& Population::rand_select() const {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution <int> distr(0,population_size-1);
    return vec[distr(g)];
}

