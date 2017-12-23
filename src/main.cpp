#include <iostream>
#include "simultaneous-equation.hpp"

int main()
{
    vector vector1 = {1, 0, 0, 0, 0};
    vector vector2 = {0, 1, 1, 1, 0};
    vector vector3 = {0, 1, 0, 0, 0};
    vector vector4 = {0, 0, 0, 0, 0};

    matrix matrix_equations = {vector1, vector2, vector3, vector4};
    SimultaneousEquation equations(matrix_equations);
    vector solutions = equations.solve_gauss();

    if (solutions.empty())
    {
        std::cout << "La matriz ingresada no tiene soluciones válidas" << std::endl;
    }

    else
    {
        for (int i = 0; i < solutions.size(); i++)
        {
            std::cout << solutions[i] << std::endl;
        }
    }

    return 0;
}