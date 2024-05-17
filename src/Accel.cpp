//$Source$
//------------------------------------------------------------------------------
// accel.cpp
//------------------------------------------------------------------------------
/**
 * @file accel.cpp
 * @author Javier Jiménez Santana
 * @date 16/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/accel.hpp"

//------------------------------------------------------------------------------
// Matrix Accel(double x, Matrix Y)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la aceleración de un satélite en órbita terrestre debido a
 * - el campo de gravedad armónico de la Tierra,
 * - las perturbaciones gravitacionales del Sol y la Luna,
 * - la presión de radiación solar y
 * - la arrastre atmosférico.
 * 
 * @param x Tiempo en segundos.
 * @param Y Vector de estado del satélite en el sistema ICRF/EME2000.
 * @return Aceleración (a=d^2r/dt^2) en el sistema ICRF/EME2000.
 */
//------------------------------------------------------------------------------
Matrix Accel(double x, Matrix Y)
{
    Matrix eopdata = *Global::eopdata;
    
    double x_pole = 0;
    double y_pole = 0;
    double UT1_UTC = 0;
    double LOD = 0;
    double dpsi = 0;
    double deps = 0;
    double dx_pole = 0;
    double dy_pole = 0;
    double TAI_UTC = 0;
    IERS(eopdata, Global::AuxParam.Mjd_UTC + x/86400.0, 'l',
            x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC);

    double UT1_TAI = 0;
    double UTC_GPS = 0;
    double UT1_GPS = 0;
    double TT_UTC = 0;
    double GPS_UTC = 0;
    timediff(UT1_UTC, TAI_UTC, UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC);
    
    double Mjd_UT1 = Global::AuxParam.Mjd_UTC + x/86400.0 + UT1_UTC/86400.0;
    double Mjd_TT = Global::AuxParam.Mjd_UTC + x/86400.0 + TT_UTC/86400.0;

    Matrix P = PrecMatrix(Const::MJD_J2000, Mjd_TT);
    Matrix N = NutMatrix(Mjd_TT);
    Matrix T = N * P;
    Matrix E = PoleMatrix(x_pole, y_pole) * GHAMatrix(Mjd_UT1) * T;

    double MJD_TDB = Mjday_TDB(Mjd_TT);
    Matrix r_Mercury(1, 3);
    Matrix r_Venus(1, 3);
    Matrix r_Earth(1, 3);
    Matrix r_Mars(1, 3);
    Matrix r_Jupiter(1, 3);
    Matrix r_Saturn(1, 3);
    Matrix r_Uranus(1, 3);
    Matrix r_Neptune(1, 3);
    Matrix r_Pluto(1, 3);
    Matrix r_Moon(1, 3);
    Matrix r_Sun(1, 3);
    JPL_Eph_DE430(MJD_TDB, r_Mercury, r_Venus, r_Earth,
                    r_Mars, r_Jupiter, r_Saturn, r_Uranus,
                        r_Neptune, r_Pluto, r_Moon, r_Sun);

    // Acceleration due to harmonic gravity field
    Matrix a = AccelHarmonic(Y.subvectorFromRow(1, 1, 3), E, Global::AuxParam.n, Global::AuxParam.m);

    // Luni-solar perturbations
    if (Global::AuxParam.sun != 0)
    {
        a.trueCopy(a + AccelPointMass(Y.subvectorFromRow(1, 1, 3), r_Sun, Const::GM_Sun));
    }
    
    if (Global::AuxParam.moon != 0)
    {
        a.trueCopy(a + AccelPointMass(Y.subvectorFromRow(1, 1, 3), r_Moon, Const::GM_Moon));
    }

    // Planetary perturbations
    if (Global::AuxParam.planets != 0)
    {
        a.trueCopy(a + AccelPointMass(Y.subvectorFromRow(1, 1, 3), r_Mercury, Const::GM_Mercury));
        a.trueCopy(a + AccelPointMass(Y.subvectorFromRow(1, 1, 3), r_Venus, Const::GM_Venus));
        a.trueCopy(a + AccelPointMass(Y.subvectorFromRow(1, 1, 3), r_Mars, Const::GM_Mars));
        a.trueCopy(a + AccelPointMass(Y.subvectorFromRow(1, 1, 3), r_Jupiter, Const::GM_Jupiter));
        a.trueCopy(a + AccelPointMass(Y.subvectorFromRow(1, 1, 3), r_Saturn, Const::GM_Saturn));
        a.trueCopy(a + AccelPointMass(Y.subvectorFromRow(1, 1, 3), r_Uranus, Const::GM_Uranus));
        a.trueCopy(a + AccelPointMass(Y.subvectorFromRow(1, 1, 3), r_Neptune, Const::GM_Neptune));
        a.trueCopy(a + AccelPointMass(Y.subvectorFromRow(1, 1, 3), r_Pluto, Const::GM_Pluto));
    }

    Matrix dY = Matrix::zeros(1, 1);
    dY.trueCopy(Matrix::concatenateRows(Y.subvectorFromRow(1, 4, 6), a));
    return dY;
}