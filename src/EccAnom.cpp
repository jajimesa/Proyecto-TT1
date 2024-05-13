//$Source$
//------------------------------------------------------------------------------
// EccAnom
//------------------------------------------------------------------------------
/**
 * @file EccAnom.cpp
 * @author Javier Jiménez Santana
 * @date 27/04/2024
 */
//------------------------------------------------------------------------------

#include "../include/EccAnom.hpp"

//------------------------------------------------------------------------------
//  double EccAnom(double M, double e)
//------------------------------------------------------------------------------
/**
 * Calcula la anomalía excéntrica para órbitas elípticas.
 *
 * @param M Anomalía media en [rad]
 * @param e Excentricidad de la órbita [0,1]
 * @return Eccentric anomaly in [rad]
 */
//------------------------------------------------------------------------------
double EccAnom(double M, double e)
{
    double E, f;
    int maxit, i;

    maxit = 15;
    i = 1;

    // Valor inicial
    M = mod(M, 2.0 * Const::pi);

    if (e < 0.8)
    {
        E = M;
    }
    else
    {
        E = Const::pi;
    }

    f = E - e * sin(E) - M;
    E = E - f / (1.0 - e * cos(E));

    // Iteración
    while (fabs(f) > 1e2 * Const::eps)
    {
        f = E - e * sin(E) - M;
        E = E - f / (1.0 - e * cos(E));
        i++;
        if (i == maxit)
        {
            exit(EXIT_FAILURE); // Convergence problems in EccAnom
        }
    }

    return E;
}
