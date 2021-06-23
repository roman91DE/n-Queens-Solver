
#include "evolution.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>


EA::EA(int _board, int _main, int _breading, int _tournament, int _seconds, int _elite, float _mr, float _cr)
: board_dimension(_board), main_pop_size(_main), breading_pop_size(_breading),tournament_size(_tournament),
  time_seconds(_seconds), m_rate(_mr), elite_size(_elite), c_rate(_cr),
  main_pop(Population(board_dimension, main_pop_size, m_rate, c_rate)), cur_generation(0) {
    main_pop.sort();
    average_fit = main_pop.calc_avr();
    best_fit = main_pop.vec[0].fitness();
}

void EA::run(bool log) {

    std::ofstream log_file;
    clock_t t;
    t = clock();


    if (log) {
        log_file.open("ea_log.csv");
        log_file  << "Evolutionary Algorithm - " << board_dimension << " Queens\n"
                  << "generation,best_fit,average_fit\n" <<  cur_generation << "," 
                  << best_fit << "," << average_fit << "\n"; 
    }

    // main loop: run if no solution is found and generation max isnt reached
    while (((t/CLOCKS_PER_SEC)<time_seconds) && (best_fit<0)) {

        // std::cout << "Current Generation:" << cur_generation << "\n";

        Population elite_pool = Population();
        int ind = 0;
        while (elite_pool.get_size() < elite_size) {
            elite_pool.add_solution(main_pop.vec[ind]);
            ++ind;
        }
        
        Population breading_pool = Population();
        while (breading_pool.get_size() < breading_pop_size) {

            Population tournament_pool = Population();
            while (tournament_pool.get_size() < tournament_size) {
                tournament_pool.add_solution(main_pop.rand_select());
            }
            tournament_pool.sort();
            breading_pool.add_solution(tournament_pool.vec[0]);
        }

        main_pop = Population();
        for (auto &it:elite_pool.vec) {
            main_pop.add_solution(it);
        }
        while (main_pop.get_size() < main_pop_size) {
            Solution child = Solution::onepoint_crossover(breading_pool.rand_select(), breading_pool.rand_select());
            child.swap_mutation();
            main_pop.add_solution(child);
        }

        main_pop.sort();
        best_fit = main_pop.vec[0].fitness();
        average_fit = main_pop.calc_avr();
        ++cur_generation;

        if (!(cur_generation%10)) {

            std::cout << "Generation: " << cur_generation << "  Best Fitness: " << best_fit 
                      << "  Average Fitness: " << average_fit << "\n"; 
        }



        if (log) {log_file <<  cur_generation << "," << best_fit << "," << average_fit << "\n"; }

    }

    if (log) {
        log_file.close();
    }
    std::cout << "\nFinished after " << cur_generation << " generations\n";
    main_pop.best_select().print();
}


