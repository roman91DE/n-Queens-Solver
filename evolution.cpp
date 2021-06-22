
#include "evolution.h"
#include <fstream>


EA::EA(int _board, int _main, int _breading, int _tournament, int _generations, float _mr, float _cr)
: board_dimension(_board), main_pop_size(_main), breading_pop_size(_breading),
tournament_size(_tournament), max_generations(_generations), m_rate(_mr), c_rate(_cr),
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
        
        Population breading_pool = Population(board_dimension, 0, false, m_rate, c_rate);
        while (breading_pool.vec.size() < breading_pop_size) {

            Population tournament_pool = Population(board_dimension, 0, false, m_rate, c_rate);
            while (tournament_pool.vec.size() < tournament_pool.population_size) {
                tournament_pool.vec.push_back(main_pop.rand_select());
                ++tournament_pool.population_size;
            }
            tournament_pool.sort();
            breading_pool.vec.push_back(tournament_pool.vec[0]);
            ++breading_pool.population_size;
        }

        main_pop = Population(board_dimension, 0, false, m_rate, c_rate);
        while (main_pop.vec.size() < main_pop_size) {
            Solution child = Solution::onepoint_crossover(breading_pool.rand_select(), breading_pool.rand_select());
            child.swap_mutation();
            main_pop.vec.push_back(child);
            ++main_pop.population_size;
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
}


