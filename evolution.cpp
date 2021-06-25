
#include "evolution.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <chrono>


EA::EA(int _board, int _main, int _breading, int _tournament, int _seconds, int _elite, float _mr, float _cr)
: board_dimension(_board), main_pop_size(_main), breading_pop_size(_breading),tournament_size(_tournament),
  time_limit(_seconds), m_rate(_mr), elite_size(_elite), c_rate(_cr),
  main_pop(Population(board_dimension, main_pop_size, m_rate, c_rate)), cur_generation(0) {
    main_pop.sort();
    average_fit = main_pop.calc_avr();
    best_fit = main_pop.best_select().fitness();
}

void EA::run(bool log) {

    std::ofstream log_file;

    // setting timer variables
    auto t0 = std::chrono::high_resolution_clock::now();
    auto t = std::chrono::high_resolution_clock::now();
    int time_consumed = std::chrono::duration_cast <std::chrono::seconds>(t - t0).count();
    

    if (log) {
        log_file.open("ea_log.csv");
        log_file  << "Evolutionary Algorithm - " << board_dimension << " Queens\n"
                  << "generation,best_fit,average_fit\n" <<  cur_generation << "," 
                  << best_fit << "," << average_fit << "\n"; 
    }

    // main loop: run if no solution is found and generation max isnt reached
    while ((time_consumed<time_limit) && (best_fit<0)) {


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
        best_fit = main_pop.best_select().fitness();
        average_fit = main_pop.calc_avr();
        ++cur_generation;

        if (!(cur_generation%10)) {

            std::cout << "Generation: " << cur_generation << "  Best Fitness: " << best_fit 
                      << "  Average Fitness: " << average_fit << "\n"; 
        }

        t = std::chrono::high_resolution_clock::now();
        time_consumed = std::chrono::duration_cast <std::chrono::seconds>(t - t0).count();

        if (log) {log_file <<  cur_generation << "," << best_fit << "," << average_fit << "\n"; }

    }

    if (log) {
        log_file.close();
    }

    t = std::chrono::high_resolution_clock::now();
    time_consumed = std::chrono::duration_cast <std::chrono::seconds>(t - t0).count();

    std::cout << "\nFinished after " << cur_generation << " generations\n"
              << "Time consumed: " << time_consumed << " seconds\n";

    main_pop.best_select().print();
}



void EA::evolutionary_algorithm() {

    // default paramters
    int boardSize       = 32;
    int mainPopSize     = 250;
    int breadingPopSize = 40;
    int tournamentSize  = 10;
    int time_limit      = 60;
    int eliteSize       = 5;
    float mutateRate    = .025;
    float crossoverRate = .975;
    bool logResults     = false;
    char log;

    // console input/output
    std::cout << "\nSolve the n-Queens problems using an Evolutionaty Algorithm\n-----"
                << "\nEnter Board Size: ";
    std::cin >> boardSize;
    std::cout << "\nEnter the maximum time limit (in seconds):";
    std::cin >> time_limit;
    std::cout << "\nLog stats to external file?[y/n]";
    std::cin >> log;
    if ((log=='y') || (log == 'Y')) {logResults==true;}
    std::cout << "\nStarting Evolution\n";
    
    // init & run algorithm
    EA ea = EA(boardSize, mainPopSize, breadingPopSize, tournamentSize, time_limit, eliteSize, mutateRate, crossoverRate);
    ea.run(logResults);
    }


