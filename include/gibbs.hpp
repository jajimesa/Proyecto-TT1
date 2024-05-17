//$Header$
//------------------------------------------------------------------------------
// gibbs.hpp
//------------------------------------------------------------------------------
/**
 * @file gibbs.hpp
 * @author Javier Jiménez Santana
 * @date 15/05/2024
 */
//------------------------------------------------------------------------------

#ifndef _GIBSS_
#define _GIBSS_

#include "matrix.hpp"
#include "global.hpp"
#include "unit.hpp"
#include "angl.hpp"
#include "SAT_Const.hpp"

void gibbs(Matrix r1, Matrix r2, Matrix r3,
            Matrix &v2, double &theta, double &theta1, double &copa, std::string &error);

#endif