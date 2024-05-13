//$Header$
//------------------------------------------------------------------------------
// NutMatrix
//------------------------------------------------------------------------------
/**
 * @file NutMatrix.hpp
 * @author Javier Jiménez Santana
 * @date 04/05/2024
 */
//------------------------------------------------------------------------------

#ifndef _NUTMATRIX_
#define _NUTMATRIX_

#include "matrix.hpp"
#include "MeanObliquity.hpp"
#include "NutAngles.hpp"
#include "R_x.hpp"
#include "R_z.hpp"

Matrix NutMatrix(double Mjd_TT);

#endif

