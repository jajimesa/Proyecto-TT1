//$Header$
//------------------------------------------------------------------------------
// Cheb3D
//------------------------------------------------------------------------------
/**
 * @file Cheb3D.hpp
 * @author Javier Jiménez Santana
 * @date 28/04/2024
 */
//------------------------------------------------------------------------------

#ifndef _CHEB3D_
#define _CHEB3D_

#include "matrix.hpp"

Matrix Cheb3D(double t, int N, double Ta, double Tb, Matrix Cx, Matrix Cy, Matrix Cz);

#endif