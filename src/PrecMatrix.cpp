//$Source$
//------------------------------------------------------------------------------
// PrecMatrix.cpp
//------------------------------------------------------------------------------
/**
 * @file PrecMatrix.hpp
 * @author Javier Jiménez Santana
 * @date 04/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/PrecMatrix.hpp"

//------------------------------------------------------------------------------
// Matrix PrecMatrix(double Mjd_1, double Mjd_2)
//------------------------------------------------------------------------------
/**
 * Transformación de precesión de coordenadas ecuatoriales.
 *
 * @param Mjd_1  Época dada (Modified Julian Date TT)
 * @param Mjd_2  Época a precesar (Modified Julian Date TT)
 *
 * @return  Matriz de transformación de precesión
 */
//------------------------------------------------------------------------------
Matrix PrecMatrix(double Mjd_1, double Mjd_2)
{
    double T  = (Mjd_1 - Const::MJD_J2000) / 36525;
    double dT = (Mjd_2 - Mjd_1) / 36525;

    // Ángulos de precesión
    double zeta = ((2306.2181 + (1.39656 - 0.000139 * T) * T) +
                   ((0.30188 - 0.000344 * T) + 0.017998 * dT) * dT) * dT / Const::Arcs;
    double z = zeta + ((0.79280 + 0.000411 * T) + 0.000205 * dT) * dT * dT / Const::Arcs;
    double theta = ((2004.3109 - (0.85330 + 0.000217 * T) * T) -
                    ((0.42665 + 0.000217 * T) + 0.041833 * dT) * dT) * dT / Const::Arcs;

    // Matriz de precesión
    return R_z(-z) * R_y(theta) * R_z(-zeta);
}
