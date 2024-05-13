//$Header$
//------------------------------------------------------------------------------
// AccelHarmonic
//------------------------------------------------------------------------------
/**
 * @file AccelHarmonic.hpp
 * @author Javier Jiménez Santana
 * @date 05/05/2024
 */
//------------------------------------------------------------------------------

#ifndef _ACCELHARMONIC_
#define _ACCELHARMONIC_

#include "SAT_Const.hpp"
#include "Legendre.hpp"
#include "matrix.hpp"
#include "global.hpp"

Matrix AccelHarmonic(Matrix r, Matrix E, int n_max, int m_max);

#endif