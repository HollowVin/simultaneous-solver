#include <iostream>
#include "simultaneous-equation.hpp"

int main()
{
    vector vector1 = {4, 1, 3, 2, 9};
    vector vector2 = {3, 5, 1, 0, 1};
    vector vector3 = {7, 6, 1, 2, 10};
    vector vector4 = {-4, 1, 2, -5, 2};

    matrix matrix_equations = {vector1, vector2, vector3, vector4};
    SimultaneousEquation equations(matrix_equations);
    vector solutions = equations.solve_gauss();

    for (int i = 0; i < solutions.size(); i++)
    {
        std::cout << solutions[i] << std::endl;
    }

    return 0;
}