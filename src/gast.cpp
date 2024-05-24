//$Source$
//------------------------------------------------------------------------------
// gast.cpp
//------------------------------------------------------------------------------
/**
 * @file gast.cpp
 * @author Javier Jiménez Santana
 * @date 15/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/gast.hpp"

//------------------------------------------------------------------------------
// double gast(double Mjd_UT1)
//------------------------------------------------------------------------------
/**
 * @brief Tiempo aparente sidéreo de Greenwich.
 *
 * @param Mjd_UT1 Fecha Juliana modificada UT1.
 * @return Tiempo aparente sidéreo de Greenwich [rad].
 */
//------------------------------------------------------------------------------
double gast(double Mjd_UT1)
{
    return mod(gmst(Mjd_UT1) + EqnEquinox(Mjd_UT1), 2*Const::pi);
}