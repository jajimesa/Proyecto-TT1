//$Source$
//------------------------------------------------------------------------------
// AccelPointMass
//------------------------------------------------------------------------------
/**
 * @file AccelPointMass.cpp
 * @author Javier Jiménez Santana
 * @date 21/04/2024
 */
//------------------------------------------------------------------------------

#include "../include/AccelPointMass.hpp"

//------------------------------------------------------------------------------
// double AccelPointMass(double r, double s, double GM)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la aceleración de un satélite en presencia de un cuerpo puntual.
 *
 * @param r Vector de posición del satélite.
 * @param s Vector de posición del cuerpo puntual.
 * @param GM Constante gravitacional por la masa del cuerpo puntual.
 *
 * @return Vector de aceleración del satélite.
 */
//------------------------------------------------------------------------------
Matrix AccelPointMass(Matrix r, Matrix s, double GM) 
{
    // Relative position vector of satellite w.r.t. point mass
    Matrix d = r - s;

    // Acceleration
    Matrix a = (d / pow(d.norm(), 3) + s / pow(s.norm(), 3)) * (-GM);

    return a;
}