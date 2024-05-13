//$Source$
//------------------------------------------------------------------------------
// LTC
//------------------------------------------------------------------------------
/**
 * @file LTC.cpp
 * @author Javier Jiménez Santana
 * @date 05/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/EqnEquinox.hpp"

//------------------------------------------------------------------------------
// double EqnEquinox (double Mjd_TT)
//------------------------------------------------------------------------------
/**
 * Computación de la ecuación de los equinoccios.
 *
 * @param Mjd_TT Fecha Juliana modificada (Tiempo Terrestre).
 * @return Ecuación de los equinoccios.
 */
//------------------------------------------------------------------------------
double EqnEquinox (double Mjd_TT)
{
    // Nutation in longitude and obliquity
    double dpsi = 0.0;
    double deps = 0.0;
    NutAngles(Mjd_TT, dpsi, deps);

    // Equation of the equinoxes
    return dpsi * cos(MeanObliquity(Mjd_TT));
}