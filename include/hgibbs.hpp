//$Header$
//------------------------------------------------------------------------------
// hgibbs.hpp
//------------------------------------------------------------------------------
/**
 * @file hgibbs.hpp
 * @author Javier Jiménez Santana
 * @date 15/05/2024
 */
//------------------------------------------------------------------------------

#ifndef _HGIBBS_
#define _HGIBBS_

#include "matrix.hpp"
#include "SAT_Const.hpp"
#include "unit.hpp"
#include "angl.hpp"
#include "elements.hpp"

void hgibbs(Matrix r1, Matrix r2, Matrix r3, double Mjd1, double Mjd2, double Mjd3,
            Matrix &v2, double &theta, double &theta1, double &copa, std::string &error);

#endif