#ifndef EAHEADER
#define EAHEADER

#include "solution.h"
#include "population.h"


class EA {
    private:
    
        // set by user
        int board_dimension;
        int time_limit;

        // default parameters
        const int main_pop_size;
        const int breading_pop_size;
        const int tournament_size;
        const int elite_size;
        const float m_rate;
        const float c_rate;

        // member variable
        Population main_pop;

        // stats
        int cur_generation;
        float average_fit;
        int best_fit;

    public:
        EA(int _board, int _main, int _breading, int _tournament, int _seconds, int _elite, float _mr, float _cr);
        void run(bool log);
        static void evolutionary_algorithm();
};







#endif
