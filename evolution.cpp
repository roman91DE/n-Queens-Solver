
#include "evolution.h"
#include <fstream>
#include <iostream>


EA::EA(int _board, int _main, int _breading, int _tournament, int _generations, int _elite, float _mr, float _cr)
: board_dimension(_board), main_pop_size(_main), breading_pop_size(_breading),tournament_size(_tournament),
  max_generations(_generations), m_rate(_mr), elite_size(_elite), c_rate(_cr),
  main_pop(Population(board_dimension, main_pop_size, true, m_rate, c_rate)), cur_generation(0) {
    main_pop.sort();
    average_fit = main_pop.calc_avr();
    best_fit = main_pop.vec[0].fitness();
}

void EA::run(bool log) {

    std::ofstream log_file;

    if (log) {
        log_file.open("ea_log.csv");
        log_file  << "Evolutionary Algorithm - " << board_dimension << " Queens\n"
                  << "generation,best_fit,average_fit\n" <<  cur_generation << "," 
                  << best_fit << "," << average_fit << "\n"; 
    }

    // main loop: run if no solution is found and generation max isnt reached
    while ((cur_generation<max_generations) && (best_fit<0)) {

        // std::cout << "Current Generation:" << cur_generation << "\n";

        Population elite_pool = Population(board_dimension, 0, false, m_rate, c_rate);
        int ind = 0;
        while (elite_pool.get_size() < elite_size) {
            elite_pool.vec.push_back(main_pop.vec[ind]);
            ++ind;
        }
        
        Population breading_pool = Population(board_dimension, 0, false, m_rate, c_rate);
        while (breading_pool.get_size() < breading_pop_size) {

            Population tournament_pool = Population(board_dimension, 0, false, m_rate, c_rate);
            while (tournament_pool.get_size() < tournament_size) {
                tournament_pool.vec.push_back(main_pop.rand_select());
            }
            tournament_pool.sort();
            breading_pool.vec.push_back(tournament_pool.vec[0]);
        }

        main_pop = Population(board_dimension, 0, false, m_rate, c_rate);
        for (auto &it:elite_pool.vec) {
            main_pop.vec.push_back(it);
        }
        while (main_pop.get_size() < main_pop_size) {
            Solution child = Solution::onepoint_crossover(breading_pool.rand_select(), breading_pool.rand_select());
            child.swap_mutation();
            main_pop.vec.push_back(child);
        }

        main_pop.sort();
        best_fit = main_pop.vec[0].fitness();
        average_fit = main_pop.calc_avr();
        ++cur_generation;

        if (log) {log_file <<  cur_generation << "," << best_fit << "," << average_fit << "\n"; }

    }

    if (log) {
        log_file.close();
    }
    main_pop.vec[0].print();
    std::cout << "\nFinished after " << cur_generation << " generations\n";
}


