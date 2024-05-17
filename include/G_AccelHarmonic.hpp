//$Header$
//------------------------------------------------------------------------------
// G_AccelHarmonic
//------------------------------------------------------------------------------
/**
 * @file G_AccelHarmonic.hpp
 * @author Javier Jiménez Santana
 * @date 16/05/2024
 */
//------------------------------------------------------------------------------

#ifndef _G_ACCELHARMONIC_
#define _G_ACCELHARMONIC_

#include "matrix.hpp"
#include "AccelHarmonic.hpp"

Matrix G_AccelHarmonic(Matrix r, Matrix U, int n_max, int m_max);

#endif