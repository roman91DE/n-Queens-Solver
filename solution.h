#ifndef SOLUTIONHEADER
#define SOLUTIONHEADER


#include <vector>
#include <string>


class Solution{

    private:

        std::vector <int> vec;
        int dimension, fit;
        float m_rate, c_rate;
        bool backtracking_sol;
        

    public:
    
        Solution(int _dimension, float _m_rate, float _c_rate);
        Solution(const std::vector <int> &v, int _dimension, float _m_rate, float _c_rate);
        Solution (const Solution &other);
        Solution();

        std::string to_string() const;
        void print() const;
        void debug_print() const;

        void swap_mutation();
        static Solution onepoint_crossover(const Solution &mother, const Solution &father);
        
        int fitness() const;

        int get_dimension() const;
        float get_c_rate() const;
        float get_m_rate() const;

        void set_mutation_rate(float _m_rate);

        bool operator<(const Solution &other);
        bool operator>(const Solution &other);
        bool operator==(const Solution &other);
        bool operator!=(const Solution &other);
        bool operator<=(const Solution &other);
        bool operator>=(const Solution &other);


        // backtracking 

        Solution(int _dimension);
        bool is_possible(int num) const;
        void place_queen(int pos, int indx);
        void remove_queen(int indx);
        bool is_solved() const;

        friend class Population;
        friend class Backtracking;
        friend class SA;
};

#endif