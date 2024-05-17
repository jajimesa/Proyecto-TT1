//$Header$
//------------------------------------------------------------------------------
// anglesg.hpp
//------------------------------------------------------------------------------
/**
 * @file anglesg.hpp
 * @author Javier Jiménez Santana
 * @date 15/05/2024
 */
//------------------------------------------------------------------------------
#ifndef _ANGLESG_
#define _ANGLESG_

#include "Matrix.hpp"
#include "global.hpp"
#include "Geodetic.hpp"
#include "LTC.hpp"
#include "IERS.hpp"
#include "timediff.hpp"
#include "PrecMatrix.hpp"
#include "PoleMatrix.hpp"
#include "SAT_Const.hpp"
#include "NutMatrix.hpp"
#include "GHAMatrix.hpp"
#include "angl.hpp"
#include "roots.hpp"
#include "gibbs.hpp"
#include "hgibbs.hpp"

void anglesg(double az1, double az2, double az3, 
            double el1, double el2, double el3,
            double Mjd1, double Mjd2, double Mjd3,
            Matrix Rs1, Matrix Rs2, Matrix Rs3,
            Matrix &r2, Matrix &v2);

#endif
