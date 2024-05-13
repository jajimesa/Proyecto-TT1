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

void MeasUpdate(Matrix z, Matrix g, Matrix s, Matrix G, int n,
                Matrix& K, Matrix& x, Matrix& P);

#endif
