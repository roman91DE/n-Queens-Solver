#include "threadedannealing.h"
#include <thread>
#include <future>
#include <cassert>
#include <iostream>
#include <chrono>
#include "simulatedannealing.h"


MA::MA (int _board_size, float _t_start, float _t_end, float _alpha) 
: board_size(_board_size), t_start(_t_start), t_end(_t_end), t_cur(_t_start),alpha(_alpha) {

    num_threads = std::thread::hardware_concurrency();
    assert (num_threads>0);
    std::cout << "\nRunning "<< num_threads << " Threads in parallel\n";

}


void MA::run_threads() {

    for (unsigned int i{0}; i<num_threads; ++i) {
        vec.push_back(std::async(std::launch::async, &SA::run_return_only, SA(board_size,t_start, t_end,alpha)));   
    }
    unsigned int counter{0};
    for (unsigned int j{0}; j<num_threads; ++j) {
        Solution s = vec[j].get();
        if (s.fitness() == 0) {
            std::cout << "\nSolution " << ++counter << ":\n";
            s.print();
        }
    }
    std::cout << counter << " of " << num_threads << " threads returned an optimal Solution\n";
}


void MA::multithreaded_annealing() {

    int board_size{4};
    char def;
    float t_start{100000000.0}, t_end{0.9}, alpha{0.999};

    std::cout << "Solving n-Queens Problem using a Multithreaded Simulated Annealing Algorithm\n-------\nEnter Board Size n=";
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
    std::cout << "\nStarting multithreaded Simulated Annealing Algorithms\n";
    MA ma = MA(board_size, t_start, t_end, alpha);

    auto t0 = std::chrono::high_resolution_clock::now();
    ma.run_threads();
    auto t = std::chrono::high_resolution_clock::now();
    int time_consumed = std::chrono::duration_cast <std::chrono::milliseconds>(t - t0).count();
    std::cout << "Total Time consumed to find all solutions: " << time_consumed << " miliseconds\n";    
    
    return;
}
