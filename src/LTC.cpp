//$Source$
//------------------------------------------------------------------------------
// LTC
//------------------------------------------------------------------------------
/**
 * @file LTC.cpp
 * @author Javier Jiménez Santana
 * @date 05/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/LTC.hpp"

//------------------------------------------------------------------------------
// Matrix LTC(double lon, double lat)
//------------------------------------------------------------------------------
/**
 * @brief Transformación del sistema del meridiano de Greenwich a las
 * coordenadas locales tangentes.
 * @param lon Longitud geodésica Este [rad].
 * @param lat Latitud geodésica [rad].
 * @return Matriz de rotación del ecuador terrestre y el meridiano de Greenwich
 * al sistema de coordenadas local tangente (Este-Norte-Zenit).
 */
//------------------------------------------------------------------------------
Matrix LTC(double lon, double lat)
{
    Matrix M = R_y(-1.0*lat)*R_z(lon);

    for(int j=1; j<=3; j++)
    {
        double Aux = M(1,j); 
        M(1,j) = M(2,j); 
        M(2,j) = M(3,j); 
        M(3,j) = Aux;
    }

    return M;
}