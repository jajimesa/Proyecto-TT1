//$Header$
//------------------------------------------------------------------------------
// timediff
//------------------------------------------------------------------------------
/**
 * @file timediff.hpp
 * @author Javier Jiménez Santana
 * @date 28/04/2024
 */
//------------------------------------------------------------------------------

#ifndef _TIMEDIFF_
#define _TIMEDIFF_

void timediff(double UT1_UTC, double TAI_UTC,
                double &UT1_TAI, double &UTC_GPS, double &UT1_GPS,
                    double &TT_UTC, double &GPS_UTC);

#endif