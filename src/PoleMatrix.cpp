//$Source$
//------------------------------------------------------------------------------
// PoleMatrix.cpp
//------------------------------------------------------------------------------
/**
 * @file PoleMatrix.cpp
 * @author Javier Jiménez Santana
 * @date 04/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/PoleMatrix.hpp"

//------------------------------------------------------------------------------
//  Matrix PoleMatrix(double xp, double yp)
//------------------------------------------------------------------------------
/**
 * Trasformación de coordenadas pseudo fijas a fijas de la Tierra para una 
 * fecha dada
 *
 * @param xp Coordenada del polo
 * @param yp Coordenada del polo
 * @return Matriz de polo
 */
//------------------------------------------------------------------------------
Matrix PoleMatrix(double xp, double yp)
{
    return R_y(-xp) * R_x(-yp);
}

