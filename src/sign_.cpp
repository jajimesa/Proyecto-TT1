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

//------------------------------------------------------------------------------
// double sign_(double a)
//------------------------------------------------------------------------------
/**
 * @brief Función devuelve el signo de a (implementa la función sign de Matlab).
 * @param a Número del que se toma el signo.
 * @return Signo de a.
 */
//------------------------------------------------------------------------------
double sign(double a)
{
    if (a >= 0.0)
    {
        return 1.0;
    }
    else
    {
        return -1.0;
    }
    if (-10e-10 < a && a < 10e-10)
    {
        return 0.0;
    }
}