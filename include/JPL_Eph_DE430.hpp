//$Header$
//------------------------------------------------------------------------------
// JPL_Eph_DE430
//------------------------------------------------------------------------------
/**
 * @file JPL_Eph_DE430.hpp
 * @author Javier Jiménez Santana
 * @date 12/05/2024
 */
//------------------------------------------------------------------------------

#ifndef _JPL_EPH_DE430_
#define _JPL_EPH_DE430_

#include "global.hpp"
#include "Cheb3D.hpp"
#include "matrix.hpp"

void JPL_Eph_DE430(double Mjd_TDB,
    Matrix &r_Mercury, Matrix &r_Venus, Matrix &r_Earth, Matrix &r_Mars,
    Matrix &r_Jupiter, Matrix &r_Saturn, Matrix &r_Uranus, Matrix &r_Neptune,
    Matrix &r_Pluto, Matrix &r_Moon, Matrix &r_Sun);

#endif