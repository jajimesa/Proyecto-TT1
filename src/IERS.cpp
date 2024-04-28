//$Source$
//-----------------------------------------------------------------------------------
// IERS
//-----------------------------------------------------------------------------------
/**
 * @file IERS.cpp
 * @author Javier Jiménez Santana
 * @date 25/04/2024
 */
//-----------------------------------------------------------------------------------
#include "../include/IERS.hpp"

#include <map>
#include <string>

//-----------------------------------------------------------------------------------
// void IERS(Matrix &eop, double Mjd_UTC, char interp, 
//            double &x_pole, double &y_pole, double &UT1_UTC,
//              double &LOD, double &dpsi, double &deps, double &dx_pole, 
//                 double &dy_pole, double &TAI_UTC)
//-----------------------------------------------------------------------------------
/**
 * @brief Función que calcula los parámetros de rotación de la Tierra de la IERS.
 *
 * @param eop [in] Matriz con los parámetros de rotación de la Tierra.
 * @param Mjd_UTC [in] Fecha en formato MJD.
 * @param interp [in] Método de interpolación.
 * @param x_pole [out] Coordenada x del polo [rad].
 * @param y_pole [out] Coordenada y del polo [rad].
 * @param UT1_UTC [out] Diferencia de tiempo UT1-UTC [s].
 * @param LOD [out] Longitud del día [s].
 * @param dpsi [out] Variación de la longitud del polo [rad].
 * @param deps [out] Variación de la oblicuidad [rad].
 * @param dx_pole [out] Variación de la coordenada x del polo [rad].
 * @param dy_pole [out] Variación de la coordenada y del polo [rad].
 * @param TAI_UTC [out] Diferencia de tiempo TAI-UTC [s].
 */
//-----------------------------------------------------------------------------------
void IERS(Matrix &eop, double Mjd_UTC, char interp, 
            double &x_pole, double &y_pole, double &UT1_UTC,
            double &LOD, double &dpsi, double &deps, double &dx_pole, 
            double &dy_pole, double &TAI_UTC)
{
    if (interp == 'n')
    {
        int mjd = static_cast<int>(floor(Mjd_UTC));
        int i = 0;
        for (; i < eop.n_column; ++i)
        {
            if (mjd == static_cast<int>(eop(4, i + 1)))
            {
                break;
            }
        }
        // Setting of IERS Earth rotation parameters
        // (UT1-UTC [s], TAI-UTC [s], x ["], y ["])
        x_pole = eop(5, i + 1) / Const::Arcs; // Pole coordinate [rad]
        y_pole = eop(6, i + 1) / Const::Arcs; // Pole coordinate [rad]
        UT1_UTC = eop(7, i + 1);              // UT1-UTC time difference [s]
        LOD = eop(8, i + 1);                  // Length of day [s]
        dpsi = eop(9, i + 1) / Const::Arcs;
        deps = eop(10, i + 1) / Const::Arcs;
        dx_pole = eop(11, i + 1) / Const::Arcs; // Pole coordinate [rad]
        dy_pole = eop(12, i + 1) / Const::Arcs; // Pole coordinate [rad]
        TAI_UTC = eop(13, i + 1);               // TAI-UTC time difference [s]
    }
    else if (interp == 'l')
    {
        int mjd = static_cast<int>(floor(Mjd_UTC));
        int i = 0;  // Luego me obligará a sumar uno
        for (; i < eop.n_column; ++i)
        {
            if (mjd == static_cast<int>(eop(4, i + 1)))
            {
                break;
            }
        }
        double mfme = 1440 * (Mjd_UTC - floor(Mjd_UTC));
        double fixf = mfme / 1440;
        // Setting of IERS Earth rotation parameters
        // (UT1-UTC [s], TAI-UTC [s], x ["], y ["])
        x_pole = (eop(5, i + 1) + (eop(5, i + 2) - eop(5, i + 1)) * fixf) / Const::Arcs; // Pole coordinate [rad]
        y_pole = (eop(6, i + 1) + (eop(6, i + 2) - eop(6, i + 1)) * fixf) / Const::Arcs; // Pole coordinate [rad]
        UT1_UTC = (eop(7, i + 1) + (eop(7, i + 2) - eop(7, i + 1)) * fixf);              // UT1-UTC time difference [s]
        LOD = (eop(8, i + 1) + (eop(8, i + 2) - eop(8, i + 1)) * fixf);                  // Length of day [s]
        dpsi = (eop(9, i + 1) + (eop(9, i + 2) - eop(9, i + 1)) * fixf) / Const::Arcs;
        deps = (eop(10, i + 1) + (eop(10, i + 2) - eop(10, i + 1)) * fixf) / Const::Arcs;
        dx_pole = (eop(11, i + 1) + (eop(11, i + 2) - eop(11, i + 1)) * fixf) / Const::Arcs; // Pole coordinate [rad]
        dy_pole = (eop(12, i + 1) + (eop(12, i + 2) - eop(12, i + 1)) * fixf) / Const::Arcs; // Pole coordinate [rad]
        TAI_UTC = eop(13, i + 1);                                                            // TAI-UTC time difference [s]
    }
}
