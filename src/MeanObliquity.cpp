//$Source$
//------------------------------------------------------------------------------
// MeanObliquity
//------------------------------------------------------------------------------
/**
 * @file MeanObliquity.cpp
 * @author Javier Jiménez Santana
 * @date 27/04/2024
 */
//------------------------------------------------------------------------------

#include "MeanObliquity.hpp"

//------------------------------------------------------------------------------
//  double MeanObliquity(double Mjd_TT)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la oblicuidad media de la eclíptica.
 *
 * @param Mjd_TT Fecha juliana modificada (Tiempo Terrestre).
 *
 * @return Oblicuidad media de la eclíptica [rad].
 */
//------------------------------------------------------------------------------
double MeanObliquity(double Mjd_TT)
{
    double T = (Mjd_TT - Const::MJD_J2000) / 36525;

    double MOblq = Const::Rad * (84381.448 / 3600 - (46.8150 + (0.00059 - 0.001813 * T) * T) * T / 3600);

    return MOblq;
}