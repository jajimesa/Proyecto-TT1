//$Source$
//------------------------------------------------------------------------------
// sign_
//------------------------------------------------------------------------------
/**
 * @file sign_.cpp
 * @author Javier Jiménez Santana
 * @date 21/04/2024
 */
//------------------------------------------------------------------------------

#include "../include/sign_.hpp"

//------------------------------------------------------------------------------
// double sign_(double a, double b)
//------------------------------------------------------------------------------
/**
 * @brief Función devuelve el valor absoluto de a con el signo de b.
 * @param b Número del que se toma el signo.
 * @return Valor absoluto de a con el signo de b.
 */
//------------------------------------------------------------------------------
double sign_(double a, double b)
{
    if (b >= 0.0)
    {
        return abs(a);
    }
    else
    {
        return -abs(a);
    }
}