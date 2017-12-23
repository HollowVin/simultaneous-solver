#include "simultaneous-equation.hpp"

SimultaneousEquation::SimultaneousEquation(matrix equations): equations(equations) {}

vector SimultaneousEquation::solve_gauss()
{
    matrix triangular = triangular_matrix(equations);

    if (triangular == equations)
    {
        return vector(); // is it good or bad to return an empty vector as a way to signal failure?
        // these return values on failures for these functions don't really seem appropriate
    }
    
    return backwards_solve(triangular);
}

matrix SimultaneousEquation::triangular_matrix(const matrix& mat)
{
    matrix triangular = mat;
    
    for (int i = 0; i < mat.size(); i++)
    {
        if (triangular[i][i] != 1) // if at least one variable is present, the lack of an ability to set the pivot at any point is not bad
        { 
            if (!set_pivot(triangular, i)) // condition for an invalid equations matrix
            {
                return mat; // perhaps make this be handled better than just returning the original matrix
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
        int row_switch = find_nonzero_row(mat, row);

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

void SimultaneousEquation::reduce_rows_below(matrix& mat, int pivot)
{
    for (int i = pivot + 1; i < mat.size(); i++)
    {
        vector scalar_vector = multiply_vector_by_scalar(mat[pivot], -mat[i][pivot]);
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
    int last_term_position = mat.size() - 1;
    
    for (int i = mat.size() - 1; i >= 0; i--)
    {
        double solution = mat[i][last_term_position + 1];
        
        for (int j = last_term_position; j > i; j--)
        {
            solution -= mat[i][j] * solutions[j];
        }

        solutions[i] = solution;
    }

    return solutions;
}