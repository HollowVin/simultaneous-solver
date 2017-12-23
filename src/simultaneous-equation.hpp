#pragma once
#include <vector>

using vector = std::vector<double>;
using matrix = std::vector<vector>;

class SimultaneousEquation
{
    private:
        matrix equations;

        static matrix triangular_matrix(const matrix&);
        static bool set_pivot(matrix&, int);
        static int find_nonzero_row_below(const matrix&, int);
        static void switch_rows(matrix&, int, int);
        static void reduce_rows_below(matrix&, int);
        static vector multiply_vector_by_scalar(const vector&, double);
        static vector sum_vectors(const vector&, const vector&);
        static vector backwards_solve(const matrix&);
    public:
        SimultaneousEquation(matrix);
        std::vector<double> solve_gauss();

        
};