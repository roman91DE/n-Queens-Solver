#ifndef EAHEADER
#define EAHEADER

#include "solution.h"
#include "population.h"


class EA {
    private:
        // parameters
        int board_dimension;
        int main_pop_size;
        int breading_pop_size;
        int tournament_size;
        int max_generations;
        int elite_size;
        float m_rate;
        float c_rate;
        // 
        Population main_pop;
        int cur_generation;
        float average_fit;
        int best_fit;

    public:
        EA(int _board, int _main, int _breading, int _tournament, int _generations, int _elite, float _mr, float _cr);
        void run(bool log);
};







#endif
