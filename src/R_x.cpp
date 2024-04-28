//$Source$
//------------------------------------------------------------------------------
// R_x
//------------------------------------------------------------------------------
/**
 * @file R_x.cpp
 * @author Javier Jiménez Santana
 * @date 18/04/2024
 */
//------------------------------------------------------------------------------

#include "../include/R_x.hpp"

//------------------------------------------------------------------------------
// Matrix R_x(double angle)
//------------------------------------------------------------------------------
/**
 * @brief Función que genera una matriz de rotación en el eje x.
 * @param angle Ángulo de rotación en radianes.
 * @return Matriz de rotación en el eje x.
 */
//------------------------------------------------------------------------------
Matrix R_x(double angle) {
    double C, S;
    C = cos(angle);
    S = sin(angle);
    Matrix rotmat = Matrix::zeros(3,3);

    rotmat(1,1) = 1.0;  rotmat(1,2) =    0.0;  rotmat(1,3) = 0.0;
    rotmat(2,1) = 0.0;  rotmat(2,2) =      C;  rotmat(2,3) =   S;
    rotmat(3,1) = 0.0;  rotmat(3,2) = -1.0*S;  rotmat(3,3) =   C;
    
    return rotmat;
}