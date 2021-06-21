#pragma once

#include <vector>
#include <string>

class Solution{

    private:
        std::vector <int> vec;
        int dimension;
        float m_rate, c_rate;
    public:
        Solution(int _dimension, float _m_rate, float _c_rate);
        Solution(const std::vector <int> &v, int _dimension, float _m_rate, float _c_rate);
        std::string to_string() const;
        void print() const;
        void debug_print() const;
        void swap_mutation();
        int fitness() const;
};