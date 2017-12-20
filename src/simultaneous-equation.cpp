#include "simultaneous-equation.hpp"

SimultaneousEquation::SimultaneousEquation(matrix equations): equations(equations) {}

vector SimultaneousEquation::solve_gauss()
{
    matrix triangular = triangular_matrix(equations);

    if (triangular == equations)
    {
        
    }
}

matrix SimultaneousEquation::triangular_matrix(const matrix& mat)
{
    matrix triangular = mat;
    
    for (int i = 0; i < mat.size(); i++)
    {
        if (mat[i][0] != 1) 
        { 
            if (!set_pivot(triangular, i))
            {
                return mat;
            } 

            sum_vectors_by_scalar(triangular, triangular[i], i + 1);
        }
    }

    return triangular;
}

bool SimultaneousEquation::set_pivot(matrix& mat, int row)
{
    if (mat[row][0] == 0)
    {
        int row_switch = find_nonzero_row(mat, row);

        if (row_switch > -1) { switch_rows(mat, row, row_switch); }
        else { return false; }
    }

    for (int i = 0; i < mat[row].size(); i++)
    {
        mat[row][i] /= mat[row][0];
    }

    return true;
}

int SimultaneousEquation::find_nonzero_row(const matrix& mat, int start = 0)
{
    int row = -1;

    for (int i = start; i < mat.size(); i++)
    {
        if (mat[i][0] != 0) { return row; }
    }

    return row;
}

void SimultaneousEquation::switch_rows(matrix& mat, int row1, int row2)
{
    vector temp = mat[row1];
    mat[row1] = mat[row2];
    mat[row2] = temp;
}

void SimultaneousEquation::sum_vectors_by_scalar(matrix& mat, const vector& vec, int start)
{
    for (int i = start; i < mat.size(); i++)
    {
        vector scalar_vector = multiply_vector_by_scalar(vec, mat[i][0]);
        vector sum_vector = sum_vectors(vec, scalar_vector);
        mat[i] = sum_vector;
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