//$Source$
//------------------------------------------------------------------------------
// NutMatrix
//------------------------------------------------------------------------------
/**
 * @file NutMatrix.cpp
 * @author Javier Jiménez Santana
 * @date 04/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/NutMatrix.hpp"

//------------------------------------------------------------------------------
//  Matrix NutMatrix(double Mjd_TT)
//------------------------------------------------------------------------------
/**
 * Transformación de la media a la verdadera ecuador y equinoccio.
 *
 * @param Mjd_TT Fecha Juliana modificada (Tiempo Terrestre).
 * @return Matriz de nutación.
 */
//------------------------------------------------------------------------------
Matrix NutMatrix(double Mjd_TT)
{
    // Oblicuidad media de la eclíptica
    double eps = MeanObliquity(Mjd_TT);

    // Nutación en longitud y oblicuidad
    double dpsi = 0.0;
    double deps = 0.0;
    NutAngles(Mjd_TT, dpsi, deps);

    // Transformación de la media al verdadero ecuador y equinoccio
    return R_x(-eps - deps) * R_z(-dpsi) * R_x(eps);
}