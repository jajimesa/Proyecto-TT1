//$Header$
//---------------------------------------------------------------------------------------------------------------
// DEInteg.hpp
//---------------------------------------------------------------------------------------------------------------
/**
 * @file DEInteg.hpp
 * @author Javier Jiménez Santana
 * @date 17/05/2024
 */
//---------------------------------------------------------------------------------------------------------------

#ifndef _DEINTEG_
#define _DEINTEG_

#include "Matrix.hpp"
#include "ode.hpp"

Matrix DEInteg(Matrix (*func)(double, Matrix), double t, double tout, double relerr, double abserr, Matrix &y);

#endif