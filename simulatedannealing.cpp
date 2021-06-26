#include "simulatedannealing.h"
#include <cmath>
#include <cassert>
#include <iostream>
#include <random>


SA::SA(int _board_size, float _t_start, float _t_end, float _alpha) 
: board_size(_board_size), t_start(_t_start), t_end(_t_end), t_cur(_t_start),alpha(_alpha),
 cur_sol(Solution()), best_sol(), cur_fit(1000), best_fit(1000){

    // solutions are initialized with empty dummy objects first...
    float m_rate = 1/float(board_size);     // mutate one gene on average
    cur_sol = Solution(board_size, m_rate, 1.0);
    best_sol = Solution(cur_sol);
    cur_fit = cur_sol.fitness();
    best_fit = best_sol.fitness();
    
    assert (t_start > _t_end);
    assert ((alpha > 0.0) && (alpha <1.0));

    run();

}

void SA::cooling() {
    t_cur *= alpha;
}

void SA::run() {

    std::random_device rd;
    std::mt19937 g;
    std::uniform_real_distribution <float> fl_distr (0,1);
    std::uniform_int_distribution <int> int_dist (0, board_size-1);

    int rounds_no_improv{0};

    while ((t_cur > t_end) && (best_fit < 0)) {

        assert (best_fit >= cur_fit);

        cooling();

        if (rounds_no_improv > 5) {
            cur_sol = best_sol;
            cur_fit = best_fit;
            rounds_no_improv = 0;
        }
        

        Solution new_sol = Solution(cur_sol);

        new_sol.permutation();
        int temp_fit = new_sol.fit;

        std::cout << "Temperature: " << t_cur << "\tCurrent Fit: " << cur_fit << "\tNew Fit: "<< temp_fit <<  "\tBest Fit: " << best_fit << "\n";

        // new solution is better
        if ( temp_fit >= cur_fit ) {
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
            ++rounds_no_improv;

            int f_y = -temp_fit;
            int f_x = -cur_fit;

            float p = exp(-( (f_y - f_x) / t_cur));
            // std::cout << "Probability = " << p <<"\n";
            if (fl_distr(g) > (p)) {
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
    char def;
    float t_start{100000000.0}, t_end{0.9}, alpha{0.999};

    std::cout << "Solving n-Queens Problem using a Simulated Annealing Algorithm\n-------\nEnter Board Size n=";
    std::cin >> board_size;
    std::cout << "\nUse Default Parameters[y/N]? ";
    std::cin >> def;
    if ((def == 'N') || (def == 'n')) {
        std::cout << "\nSet real valued Starting Temperature = ";
            std::cin >> t_start;
            std::cout << "\nSet real valued End Temperature = ";
            std::cin >> t_end;
            std::cout << "\nSet real valued factor for geometric cooling  = ";
            std::cin >> alpha;
    }
    std::cout << "\nStarting Simulated Annealing Algorithm\n";
    SA sa = SA(board_size, t_start, t_end, alpha);
    return;
}



Solution SA::run_return_only() {

    std::random_device rd;
    std::mt19937 g;
    std::uniform_real_distribution <float> fl_distr (0,1);
    std::uniform_int_distribution <int> int_dist (0, board_size-1);

    int rounds_no_improv{0};

    while ((t_cur > t_end) && (best_fit < 0)) {

        assert (best_fit >= cur_fit);

        cooling();

        if (rounds_no_improv > 5) {
            cur_sol = best_sol;
            cur_fit = best_fit;
            rounds_no_improv = 0;
        }
        

        Solution new_sol = Solution(cur_sol);

        new_sol.permutation();
        int temp_fit = new_sol.fit;

        std::cout << "Temperature: " << t_cur << "\tCurrent Fit: " << cur_fit << "\tNew Fit: "<< temp_fit <<  "\tBest Fit: " << best_fit << "\n";

        // new solution is better
        if ( temp_fit >= cur_fit ) {
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
            ++rounds_no_improv;

            int f_y = -temp_fit;
            int f_x = -cur_fit;

            float p = exp(-( (f_y - f_x) / t_cur));
            // std::cout << "Probability = " << p <<"\n";
            if (fl_distr(g) > (p)) {
                cur_sol = new_sol;
                cur_fit = temp_fit;
            }
        }
    }
    std::cout << "Termination condition reached\nBest Solution:\n";
    if (best_sol.fit == 0) {
        return best_sol;
    }
    return;
}


