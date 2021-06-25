#include "simulatedannealing.h"
#include <cmath>
#include <cassert>
#include <iostream>
#include <random>


SA::SA(int _board_size, float _t_start, float _t_end, float _alpha) 
: board_size(_board_size), t_start(_t_start), t_end(_t_end), t_cur(_t_start),alpha(_alpha),
 cur_sol(Solution()), best_sol(), cur_fit(1000), best_fit(1000) {
    // solutions are initialized with empty dummy objects first...
    float m_rate = 1/float(board_size);     // mutate one gene on average
    cur_sol = Solution(board_size, m_rate, 1.0);
    best_sol = Solution(cur_sol);
    cur_fit = cur_sol.fitness();
    best_fit = best_sol.fitness();
    
    assert (t_start>_t_end);
    assert ((alpha > 0.0));

    run();
}

void SA::cooling() {
    t_cur -= alpha;
}


void SA::run() {

    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_real_distribution <float> fl_distr(0,1);
    float m_rate = 0.2;

    while ((t_cur > t_end) && (best_fit < 0)) {

        assert (best_fit >= cur_fit);

        cooling();
        
        std::cout << "Current Temp: " << t_cur << "\tCurrent Fitness: " << cur_fit << "\tBest Fitness: " << best_fit << "\tM-Rate: " << m_rate << "\n";

        Solution new_sol = cur_sol;
        m_rate *= .999999;

        new_sol.set_mutation_rate(m_rate);
        new_sol.swap_mutation();
        int temp_fit = new_sol.fitness();

        // new solution is better
        if ( temp_fit > cur_fit) {
            cur_sol = new_sol;
            cur_fit = temp_fit;
            if (cur_fit > best_fit) {
                best_sol = cur_sol;
                best_fit = cur_fit;
            }
            continue;
        }
        // new solution is worse
        else {
            float p = (exp(-(temp_fit-cur_fit) / t_cur));
            if (fl_distr(g) < p) {
                cur_sol = new_sol;
                cur_fit = temp_fit;
            }
        }
    }
    std::cout << "Termination condition reached\nBest Solution:\n";
    best_sol.print();
    return;
}


void SA::simulated_annealing() {

    int board_size{4};
    float t_start, t_end, alpha;

    std::cout << "Solving n-Queens Problem using a Simulated Annealing Algorithm\n-------\nEnter Board Size n=";
    std::cin >> board_size;
    std::cout << "\nSet real valued Starting Temperature = ";
    std::cin >> t_start;
    std::cout << "\nSet real valued End Temperature = ";
    std::cin >> t_end;
    std::cout << "\nSet real valued linear cooling per Iteration = ";
    std::cin >> alpha;

    std::cout << "\nStarting Simulated Annealing Algorithm\n";
    SA sa = SA(board_size, t_start, t_end, alpha);
    return;
}


