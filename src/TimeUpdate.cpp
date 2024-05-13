//$Source$
//------------------------------------------------------------------------------
// TimeUpdate
//------------------------------------------------------------------------------
/**
 * @file TimeUpdate.cpp
 * @author Javier Jiménez Santana
 * @date 04/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/TimeUpdate.hpp"

//------------------------------------------------------------------------------
//  double TimeUpdate(double P, double Phi, double Qdt)
//------------------------------------------------------------------------------
/**
 * Actualiza la matriz de covarianza del error de estado.
 *
 * @param P  Matriz de covarianza
 * @param Phi  Matriz de propagación
 * @param Qdt  Covarianza del ruido de proceso
 *
 * @return  Matriz de covarianza actualizada
 */
//------------------------------------------------------------------------------
Matrix TimeUpdate(Matrix P, Matrix Phi, double Qdt = 0.0)
{
    return Phi*P*Phi + Qdt;
}
