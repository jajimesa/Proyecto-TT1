//$Header$
//------------------------------------------------------------------------------
// VarEqn.hpp
//------------------------------------------------------------------------------
/**
 * @file VarEqn.hpp
 * @author Javier Jiménez Santana
 * @date 16/05/2024
 */
//------------------------------------------------------------------------------

#ifndef _VAREQN_
#define _VAREQN_

#include "matrix.hpp"
#include "AccelHarmonic.hpp"
#include "G_AccelHarmonic.hpp"
#include "IERS.hpp"
#include "timediff.hpp"
#include "PrecMatrix.hpp"
#include "NutMatrix.hpp"
#include "PoleMatrix.hpp"
#include "GHAMatrix.hpp"

Matrix VarEqn(double x, Matrix yPhi);
void VarEqn(double t, double *y, double *yp);

#endif