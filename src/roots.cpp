//$Source$
//------------------------------------------------------------------------------
// roots.cpp
//------------------------------------------------------------------------------
/**
 * @file roots.cpp
 * @author Javier Jiménez Santana
 * @date 15/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/roots.hpp"

//------------------------------------------------------------------------------
// Matrix roots(Matrix poly)
//------------------------------------------------------------------------------
/**
 * @brief Computación de las raíces de un polinomio.
 *
 * @param poly Polinomio.
 * @return Raíces del polinomio.
 */
//------------------------------------------------------------------------------
Matrix roots(Matrix poly)
{
    int degree = poly.n_column - 1;

    double *coefficients = new double[poly.n_column];
    for (int i = 0; i < poly.n_column; ++i)
    {
        coefficients[i] = poly.data[0][i]; // Suponiendo que poly es una matriz fila
    }

    double *zeror = new double[degree];
    double *zeroi = new double[degree];
    int num_roots = rpoly(coefficients, degree, zeror, zeroi);

    // Matriz de raíces
    Matrix roots(1, num_roots * 2); // Cada raíz tiene una parte real y una imaginaria

    // Llenar la matriz de raíces
    for (int i = 0; i < num_roots; ++i)
    {
        roots.data[0][2 * i] = zeror[i];
        roots.data[0][2 * i + 1] = zeroi[i];
    }

    delete[] coefficients;
    delete[] zeror;
    delete[] zeroi;

    return roots;   // Tiene el doble de columnas que el número de raíces, hay que cogerlas de dos en dos
}

//------------------------------------------------------------------------------
// bool isReal(double Re, double Im)
//------------------------------------------------------------------------------
/**
 * @brief Comprobación de si un número complejo es real.
 *
 * @param Re Parte real.
 * @param Im Parte imaginaria.
 * @return true si el número es real, false en caso contrario.
 */
//------------------------------------------------------------------------------
bool isReal(double Re, double Im)
{
    return abs(Im < 1.0e-10);
}