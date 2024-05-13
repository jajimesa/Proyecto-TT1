//$Header$
//------------------------------------------------------------------------------
// PrecMatrix.hpp
//------------------------------------------------------------------------------
/**
 * @file PrecMatrix.hpp
 * @author Javier Jiménez Santana
 * @date 04/05/2024
 */
//------------------------------------------------------------------------------

#ifndef _PRECMATRIX_
#define _PRECMATRIX_

#include "matrix.hpp"
#include "SAT_Const.hpp"
#include "R_z.hpp"
#include "R_y.hpp"
#include "R_x.hpp"

Matrix PrecMatrix(double Mjd_1, double Mjd_2);

#endif