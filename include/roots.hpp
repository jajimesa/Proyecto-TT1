//$Header$
//------------------------------------------------------------------------------
// roots.hpp
//------------------------------------------------------------------------------
/**
 * @file roots.hpp
 * @author Javier Jiménez Santana
 * @date 15/05/2024
 */
//------------------------------------------------------------------------------
#ifndef _ROOTS_
#define _ROOTS_

#include "Matrix.hpp"
#include "rpoly.hpp"

Matrix roots(Matrix poly);
bool isReal(double Re, double Im);

#endif