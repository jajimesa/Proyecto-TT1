//$Header$
//------------------------------------------------------------------------------
// accel.hpp
//------------------------------------------------------------------------------
/**
 * @file accel.hpp
 * @author Javier Jiménez Santana
 * @date 16/05/2024
 */
//------------------------------------------------------------------------------

#ifndef _ACCEL_
#define _ACCEL_

#include "SAT_Const.hpp"
#include "global.hpp"
#include "matrix.hpp"
#include "timediff.hpp"
#include "IERS.hpp"
#include "PrecMatrix.hpp"
#include "NutMatrix.hpp"
#include "PoleMatrix.hpp"
#include "GHAMatrix.hpp"
#include "Mjday_TDB.hpp"
#include "JPL_Eph_DE430.hpp"
#include "AccelHarmonic.hpp"
#include "AccelPointMass.hpp"

Matrix Accel(double x, Matrix Y);
void Accel(double t, double *y, double *yp);

#endif

