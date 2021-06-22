#include "population.h"
#include "solution.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <random>
#include <cstdio>

Population::Population(int _dimension, int _size, bool init, float m_rate, float c_rate)
: dimension(_dimension) {
    if (init) {
        for (unsigned int i{0}; i<_size; ++i) {
            vec.push_back(Solution(dimension, m_rate, c_rate));
            }
    }
    average_fit = calc_avr();
}


int Population::get_size() const {
    return vec.size();
}

void Population::sort() {
    std::sort(vec.rbegin(), vec.rend());
}


void Population::print_fit_debug() const{
    for (unsigned int i{0}; i<get_size(); ++i) {
        printf("Fitness of Solution %d: %d\n", i, vec[i].fit);
    }
}

float Population::calc_avr() {
    int sum{0};
    for (auto &it:vec) {
        sum+= it.fit;
    }
    return (float(sum) / float(get_size()));
}

const Solution& Population::rand_select() const {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution <int> distr(0,get_size()-1);
    return vec[distr(g)];
}

