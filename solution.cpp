#include "solution.h"

#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

// construct a random Solution with input parameters
Solution::Solution(int _dimension,  float _m_rate, float _c_rate)
    : dimension(_dimension), m_rate(_m_rate), c_rate(_c_rate) {
    for (unsigned int i=0; i<dimension; ++i) {
        vec.push_back(i);
    }
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(vec.begin(), vec.end(), g);
    fit = fitness();

} 

// construct a Solution from an input vector
Solution::Solution(const std::vector <int> &v, int _dimension, float _m_rate, float _c_rate) 
: dimension(_dimension), m_rate(_m_rate), c_rate(_c_rate), vec(v) {
    fit = fitness();
}


// returns string of the Solution represented on a board
std::string Solution::to_string() const{
    std::string s{};
    for (unsigned int i=0; i<dimension; ++i) {
        for (unsigned int j=0; j<dimension; ++j) {
            if (vec[i] == j) {s += 'Q';}
            else { s+= '.';}
        }
        s += '\n';
    }
    return s;
}

// stdout Solution represented on a board
void Solution::print() const{
    std::cout << to_string();
}


// stdout underlying vector
void Solution::debug_print() const {
    for (unsigned int i = 0; i<dimension; ++i) {
        std::cout <<  vec[i] << ' ';
    }
    std::cout << '\n';
}

// mutate by swapping gene with another gene
void Solution::swap_mutation() {

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution <float> fl_distr(0,1);
    std::uniform_int_distribution <int> int_distr(0,dimension-1);
    
    for (unsigned int i=0; i<dimension; ++i) {
        if (fl_distr(g) <= m_rate) {
            int zv = int_distr(g);
            if (zv != i) {
                int temp = vec[i];
                vec[i] = vec[zv];
                vec[zv] = temp;
            }
        }
    }
    fit = fitness();
}

int Solution::fitness() const {
    int fitness{0};
    for (unsigned int i=0; i<dimension-1; ++i) {
        for (unsigned int j=i+1; j<dimension; ++j ) {
            if ( (vec[i] - vec[j] == i-j) || (vec[i] - vec[j] == -i+j) ) {
                --fitness;
            }
        }
    }
    return fitness;
}