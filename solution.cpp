#include "solution.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>

// construct a random Solution with input parameters
Solution::Solution(int _dimension,  float _m_rate, float _c_rate)
    : dimension(_dimension), m_rate(_m_rate), c_rate(_c_rate), backtracking_sol(false) {
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
: dimension(_dimension), m_rate(_m_rate), c_rate(_c_rate), vec(v) , backtracking_sol(false){
    fit = fitness();
}

// copy construct Solution
Solution::Solution(const Solution &other) 
    : vec(other.vec), dimension(other.dimension), fit (other.fit), m_rate(other.m_rate), c_rate(other.c_rate), backtracking_sol(false) {}




// returns string of the Solution represented on a board
std::string Solution::to_string() const{
    std::string s{};
    bool b{true};
    for (unsigned int i=0; i<dimension; ++i) {
        for (unsigned int j=0; j<dimension; ++j) {
            b = !(b);
            if (vec[i] == j)    s += 'Q';
            else { 
                if (b)  s+=' ';
                else    s+='.';
                }
        }
        s += '\n';
        b = !(b);
    }
    return s;
}


// stdout string repr of board
void Solution::print() const{
    if (!(backtracking_sol)) {
        std::cout << to_string() << "\nRemaining Conflicts = " + std::to_string(-fit) + "\n-----\n";
        }
    else {
        std::cout << "\n" << to_string() << "\n"; 
        }
}


// stdout underlying vector solution and fitness
void Solution::debug_print() const {
    if (!(backtracking_sol)) {
        for (unsigned int i = 0; i<dimension; ++i) {
            std::cout <<  vec[i] << ' ';
            }
        std::cout << "Fitness = " << fit <<'\n';}
    else {
        for (unsigned int j{0}; j<dimension; ++j) {
            if (vec[j] != -1){
                std::cout << vec[j] << ' ';
            }
        }
    }
}

// mutate by swapping gene with another random gene
void Solution::swap_mutation() {

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution <float> fl_distr(0,1);
    std::uniform_int_distribution <int> int_distr(0,dimension-1);
    
    for (unsigned int i=0; i<dimension; ++i) {
        if (fl_distr(g) < m_rate) {
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
            else if (vec[i] == vec[j]) {
                --fitness;
            }
        }
    }
    return fitness;
}

int Solution::get_dimension() const {
    return dimension;
}

float Solution::get_c_rate() const {
    return c_rate;
}

float Solution::get_m_rate() const {
    return m_rate;
}

Solution Solution::onepoint_crossover(const Solution &mother, const Solution &father) {

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution <float> fl_distr(0,1);
    std::uniform_int_distribution <int> int_distr(0,mother.get_dimension()-1);

    std::vector <int> child_genotype{};

    if (fl_distr(g) < mother.get_c_rate()) {
        std::vector <int> child_genotype{};
        int zv = int_distr(g);
        
        for (unsigned int i=0; i<zv; ++i) {
            child_genotype.push_back(mother.vec[i]);
        }
        for (unsigned int y=zv; y<father.get_dimension(); y++) {
            int gene = father.vec[y];
            bool add = true;
            for (unsigned int x=0; x<child_genotype.size(); ++x) {
                if (gene == child_genotype[x]) {
                    add = false;
                    break;
                }
            }
            if (add) {
                child_genotype.push_back(gene);
            }
        }
        for (unsigned int y=0; y<zv; y++) {
            int gene = father.vec[y];
            bool add = 1;
            for (unsigned int x=0; x<child_genotype.size(); ++x) {
                if (gene == child_genotype[x]) {
                    add = 0;
                    break;
                }
            }
            if (add) {
                child_genotype.push_back(gene);
                }
            }   
        return Solution(child_genotype, child_genotype.size(), mother.get_m_rate(), father.get_c_rate());
    }
    // below crossover rate
    else {
        if (fl_distr(g) > .5) {
            return Solution(mother);
        } 
        else {
            return Solution(father);
        }
    }
}

void Solution::set_mutation_rate(float _m_rate) {
    m_rate = _m_rate;
}

// operator overloading

bool Solution::operator<(const Solution &other) {
    return (fit<other.fit);
}

bool Solution::operator>(const Solution &other) {
    return (fit>other.fit);
}

bool Solution::operator==(const Solution &other) {
    return (fit==other.fit);
}

bool Solution::operator!=(const Solution &other) {
    return (fit!=other.fit);
}

bool Solution::operator<=(const Solution &other) {
    return (fit<=other.fit);
}

bool Solution::operator>=(const Solution &other) {
    return (fit>=other.fit);
}


/*
Backtracking methods
*/

// create an empty solution for backtracking algorithm
Solution::Solution(int _dimension) 
: dimension(_dimension), m_rate(0.0), c_rate(0.0), fit(0) , backtracking_sol(true){
    for (unsigned int i{0}; i<dimension; ++i) {
        vec.push_back(-1);      // -1 encodes an empty position in our notation
    }
}

// checks if num can be placed on first open position
bool Solution::is_possible(int num) const {
    int limit = 0;
    while (true) {
        if (vec[limit] != -1) { ++limit; }
        else { break; }
    }
    for (unsigned int i{0}; i<limit; ++i) {
        if (vec[i] == num) { return false; }
        if ( ((vec[i] - num) == (i-limit))  ||  ((vec[i] - num) == -(i-limit)) ) { return false; }
    }
    // std::cout << "__is possible -> true__\n"; 
    return true;
}

void Solution::place_queen(int pos, int indx) {
    vec[indx] = pos;
    // std::cout << "__placed queen__\n"; 
}

void Solution::remove_queen(int indx) {
    vec[indx] = -1;
    // std::cout << "__removed queen__\n"; 
}


bool Solution::is_solved() const {
    if (!(backtracking_sol)) {
        std::cout << "Error - The method is_solved() may only be called on Solutions with member backtracking_sol = true\n";
        return false;
    }
    unsigned int count{0};
    for (auto &it:vec) {
        if (it != -1)     { ++count; }
    }
    return (count==dimension);
}