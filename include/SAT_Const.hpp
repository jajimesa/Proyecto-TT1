//$Header$
//------------------------------------------------------------------------------
// SAT_Const
//------------------------------------------------------------------------------
/**
 * @file SAT_Const.hpp
 * @author Javier Jiménez Santana
 * @date 25/04/2024
 */
//------------------------------------------------------------------------------

#ifndef _SAT_CONST_
#define _SAT_CONST_

#include <cmath>

class Const {
public:
    // Matlab
    static constexpr double eps = 2.22044604925031e-16;    // Precision de la máquina

    // Mathematical constants
    static constexpr double pi = M_PI;                     // Pi
    static constexpr double pi2 = 2 * M_PI;                // 2pi
    static constexpr double Rad = M_PI / 180;              // Radians per degree
    static constexpr double Deg = 180 / M_PI;              // Degrees per radian
    static constexpr double Arcs = 3600 * 180 / M_PI;      // Arcseconds per radian

    // General
    static constexpr double MJD_J2000 = 51544.5;           // Modified Julian Date of J2000
    static constexpr double T_B1950 = -0.500002108;        // Epoch B1950
    static constexpr double c_light = 299792458.0;         // Speed of light  [m/s]; DE430
    static constexpr double AU = 149597870700.0;           // Astronomical unit [m]; DE430

    // Physical parameters of the Earth, Sun and Moon

    // Equatorial radius and flattening
    static constexpr double R_Earth = 6378.1363e3;         // Earth's radius [m]; DE430
    static constexpr double f_Earth = 1.0 / 298.257223563; // Flattening; WGS-84
    static constexpr double R_Sun = 696000e3;              // Sun's radius [m]; DE430
    static constexpr double R_Moon = 1738e3;               // Moon's radius [m]; DE430

    // Earth rotation (derivative of GMST at J2000; differs from inertial period by precession)
    static constexpr double omega_Earth = 15.04106717866910 / 3600 * Rad; // [rad/s]; WGS-84

    // Gravitational coefficients
    static constexpr double GM_Earth = 398600.435436e9;                      // [m^3/s^2]; DE430
    static constexpr double GM_Sun = 132712440041.939400e9;                  // [m^3/s^2]; DE430
    static constexpr double GM_Moon = GM_Earth / 81.30056907419062;          // [m^3/s^2]; DE430
    static constexpr double GM_Mercury = 22031.780000e9;                     // [m^3/s^2]; DE430
    static constexpr double GM_Venus = 324858.592000e9;                      // [m^3/s^2]; DE430
    static constexpr double GM_Mars = 42828.375214e9;                        // [m^3/s^2]; DE430
    static constexpr double GM_Jupiter = 126712764.800000e9;                 // [m^3/s^2]; DE430
    static constexpr double GM_Saturn = 37940585.200000e9;                   // [m^3/s^2]; DE430
    static constexpr double GM_Uranus = 5794548.600000e9;                    // [m^3/s^2]; DE430
    static constexpr double GM_Neptune = 6836527.100580e9;                   // [m^3/s^2]; DE430
    static constexpr double GM_Pluto = 977.0000000000009e9;                  // [m^3/s^2]; DE430

    // Solar radiation pressure at 1 AU 
    static constexpr double P_Sol = 1367 / c_light; // [N/m^2] (~1367 W/m^2); IERS 96
};

#endif