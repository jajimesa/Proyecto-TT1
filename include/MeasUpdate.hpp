//$Header$
//------------------------------------------------------------------------------
// MeasUpdate
//------------------------------------------------------------------------------
/**
 * @file MeasUpdate.hpp
 * @author Javier Jiménez Santana
 * @date 05/05/2024
 */
//------------------------------------------------------------------------------

#ifndef _MEASUPDATE_
#define _MEASUPDATE_

#include "matrix.hpp"

// Implementación correcta
void MeasUpdate(Matrix z, Matrix g, Matrix s, Matrix G, Matrix& P, int n,
                Matrix& K, Matrix& x);

// Implementación incorrecta (es la que se usa en el proyecto Matlab)
void MeasUpdate(double z, double g, double s, Matrix G, Matrix& P, int n,
                Matrix& K, Matrix& x);

#endif
