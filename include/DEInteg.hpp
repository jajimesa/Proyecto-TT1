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

Matrix DEInteg(void (*f)(double t, double *y, double *yp), double t, double tout, double relerr, double abserr, int neqn, 
                Matrix &y, double *yArr, double *work, int *iwork);

#endif