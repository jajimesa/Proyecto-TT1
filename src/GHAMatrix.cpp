//$Source$
//------------------------------------------------------------------------------
// GHAMatrix.cpp
//------------------------------------------------------------------------------
/**
 * @file GHAMatrix.cpp
 * @author Javier Jiménez Santana
 * @date 15/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/GHAMatrix.hpp"

//------------------------------------------------------------------------------
// Matrix GHAMatrix(double Mjd_UT1)
//------------------------------------------------------------------------------
/**
 * @brief Transformación de la verdadera equinoccial y ecuador a la ecuatorial de la
 * Tierra y el sistema del meridiano de Greenwich.
 *
 * @param Mjd_UT1 Fecha Juliana modificada UT1.
 * @return Matriz de ángulos de la hora de Greenwich.
 */
//------------------------------------------------------------------------------
Matrix GHAMatrix(double Mjd_UT1)
{
    return R_z(gast(Mjd_UT1));
}