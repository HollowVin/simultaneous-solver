#include "simultaneous-equation.hpp"

SimultaneousEquation::SimultaneousEquation(matrix equations): equations(equations) {}

vector SimultaneousEquation::solve_gauss()
{
    matrix triangular = triangular_matrix(equations);
    return triangular.empty() ? vector() : backwards_solve(triangular);
}

matrix SimultaneousEquation::triangular_matrix(const matrix& mat)
{
    matrix triangular = mat;
    
    for (int i = 0; i < mat.size(); i++)
    {
        if (triangular[i][i] != 1)
        { 
            if (!set_pivot(triangular, i))
            {
                return matrix();
            }
        }

        reduce_rows_below(triangular, i);
    }

    return triangular;
}

bool SimultaneousEquation::set_pivot(matrix& mat, int row)
{
    if (mat[row][row] == 0)
    {
        int row_switch = find_nonzero_row_below(mat, row);

        if (row_switch > -1)    { switch_rows(mat, row, row_switch); }
        else                    { return false; }
    }

    double pivot_value = mat[row][row];

    for (int i = 0; i < mat[row].size(); i++)
    {
        mat[row][i] /= pivot_value;
    }

    return true;
}

int SimultaneousEquation::find_nonzero_row_below(const matrix& mat, int row)
{
    int nonzero_row = -1;

    for (int i = row; i < mat.size(); i++)
    {
        if (mat[i][row] != 0) { return i; }
    }

    return nonzero_row;
}

void SimultaneousEquation::switch_rows(matrix& mat, int row1, int row2)
{
    vector temp = mat[row1];
    mat[row1] = mat[row2];
    mat[row2] = temp;
}

void SimultaneousEquation::reduce_rows_below(matrix& mat, int row)
{
    for (int i = row + 1; i < mat.size(); i++)
    {
        vector scalar_vector = multiply_vector_by_scalar(mat[row], -mat[i][row]);
        mat[i] = sum_vectors(mat[i], scalar_vector);
    }
}

vector SimultaneousEquation::multiply_vector_by_scalar(const vector& vec, double scalar)
{
    vector scalar_vector = vec;

    for (int i = 0; i < scalar_vector.size(); i++)
    {
        scalar_vector[i] *= scalar;
    }

    return scalar_vector;
}

vector SimultaneousEquation::sum_vectors(const vector& vec1, const vector& vec2)
{
    vector sum_vector;

    for (int i = 0; i < vec1.size(); i++)
    {
        sum_vector.push_back(vec1[i] + vec2[i]);
    }

    return sum_vector;
}

vector SimultaneousEquation::backwards_solve(const matrix& mat)
{
    vector solutions(mat.size());
    int diagonal_position = mat.size() - 1;
    
    for (int i = diagonal_position; i >= 0; i--)
    {
        double solution = mat[i][diagonal_position + 1];
        
        for (int j = diagonal_position; j > i; j--)
        {
            solution -= mat[i][j] * solutions[j];
        }

        solutions[i] = solution;
    }

    return solutions;
}