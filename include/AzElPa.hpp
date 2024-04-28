//$Header$
//------------------------------------------------------------------------------
// AzElPa
//------------------------------------------------------------------------------
/**
 * @file AzElPa.hpp
 * @author Javier Jiménez Santana
 * @date 28/04/2024
 */
//------------------------------------------------------------------------------

#ifndef _AZELPA_
#define _AZELPA_

#include "matrix.hpp"
#include "SAT_Const.hpp"

void AzElPa(Matrix s, double &Az, double &El, Matrix &dAds, Matrix &dEds);

#endif