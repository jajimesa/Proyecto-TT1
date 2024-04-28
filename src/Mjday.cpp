//$Source$
//------------------------------------------------------------------------------
// Mjday
//------------------------------------------------------------------------------
/**
 * @file Mjday.cpp
 * @author Javier Jiménez Santana
 * @date 27/04/2024
 */
//------------------------------------------------------------------------------

#include "../include/Mjday.hpp"

//------------------------------------------------------------------------------
// double Mjday(int yr, int mon, int day, int hr, int min, double sec)
//------------------------------------------------------------------------------
/**
 * @brief Función que calcula el número juliano modificado de una fecha.
 * @param yr Año.
 * @param mon Mes.
 * @param day Día.
 * @param hr Hora en tiempo universal.
 * @param min Minuto. en tiempo universal.
 * @param sec Segundos en tiempo universal. 
 * @return "Modified Julian Date" de la fecha.
 */
//------------------------------------------------------------------------------

double Mjday(int yr, int mon, int day, int hr = 0, int min = 0, double sec = 0) {
    
    double jd, Mjd;

    jd = 367.0 * yr 
        - floor( (7 * (yr + floor( (mon + 9) / 12.0) ) ) * 0.25 )
        + floor( 275 * mon / 9.0 )
        + day + 1721013.5
        + ( (sec/60.0 + min ) / 60.0 + hr ) / 24.0;

    Mjd = jd - 2400000.5;

    return Mjd;
}
