//$Source$
//------------------------------------------------------------------------------
// Frac
//------------------------------------------------------------------------------
/**
 * @file Frac.cpp
 * @author Javier Jiménez Santana
 * @date 21/04/2024
 */
//------------------------------------------------------------------------------

#include "../include/Frac.hpp"

//------------------------------------------------------------------------------
// double Frac(double x)
//------------------------------------------------------------------------------
/**
 * @brief Función que calcula la parte fraccionaria de un número.
 * @param x Número del que se quiere calcular la parte fraccionaria.
 * @return Parte fraccionaria de x.
 */
//------------------------------------------------------------------------------
double Frac(double x) {
    return x - floor(x);
}