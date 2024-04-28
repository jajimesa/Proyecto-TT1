//$Source$
//------------------------------------------------------------------------------
// Geodetic.cpp
//------------------------------------------------------------------------------
/**
 * @file Geodetic.cpp
 * @author Javier Jiménez Santana
 * @date 28/04/2024
 */
//------------------------------------------------------------------------------

#include "../include/Geodetic.hpp"

//------------------------------------------------------------------------------
//  void Geodetic(Matrix r, double &lon, double &lat, double &h)
//------------------------------------------------------------------------------
/**
 * @brief Coordenadas geoédicas (Longitud [rad], latitud [rad], altitud [m])
 * a partir de un vector de posición dado (r [m]).
 * @param r Vector de posición [m].
 * @param lon Longitud [rad].
 * @param lat Latitud [rad].
 * @param h Altitud [m].
 */
void Geodetic(Matrix r, double &lon, double &lat, double &h)
{
    double R_equ, f, epsRequ, e2, X, Y, Z, rho2, dZ, ZdZ, Nh, SinPhi, N, dZ_new;
    R_equ = Const::R_Earth;
    f = Const::f_Earth;

    // epsRequ = eps*R_equ; // Convergence criterion
    epsRequ = 0; // TODO borrar
    
    e2 = f * (2.0 - f); // Square of eccentricity

    X = r(1, 1); // Cartesian coordinates
    Y = r(1, 2);
    Z = r(1, 3);
    rho2 = X * X + Y * Y; // Square of distance from z-axis

    // Check validity of input data
    if (Matrix::norm(r) == 0.0)
    {
        exit(EXIT_FAILURE); // Invalid input in Geodetic constructor
        lon = 0.0;
        lat = 0.0;
        h = -R_equ;
    }

    // Iteration
    dZ = e2 * Z;

    while (true)
    {
        ZdZ = Z + dZ;
        Nh = sqrt(rho2 + ZdZ * ZdZ);
        SinPhi = ZdZ / Nh; // Sine of geodetic latitude
        N = R_equ / sqrt(1.0 - e2 * SinPhi * SinPhi);
        dZ_new = N * e2 * SinPhi;
        if (abs(dZ - dZ_new) < epsRequ)
        {
            break;
        }
        dZ = dZ_new;
    }

    // Longitude, latitude, altitude
    lon = atan2(Y, X);
    lat = atan2(ZdZ, sqrt(rho2));
    h = Nh - N;
}
