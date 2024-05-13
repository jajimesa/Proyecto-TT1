//$Header$
//------------------------------------------------------------------------------
// TimeUpdate
//------------------------------------------------------------------------------
/**
 * @file TimeUpdate.hpp
 * @author Javier Jiménez Santana
 * @date 04/05/2024
 */
//------------------------------------------------------------------------------

#ifndef _TIMEUPDATE_
#define _TIMEUPDATE_

#include "Matrix.hpp"

Matrix TimeUpdate(Matrix P, Matrix Phi, double Qdt);

#endif