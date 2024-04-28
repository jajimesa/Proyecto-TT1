//$Source$
//------------------------------------------------------------------------------
// AzElPa
//------------------------------------------------------------------------------
/**
 * @file AzElPa.cpp
 * @author Javier Jiménez Santana
 * @date 28/04/2024
 */
//------------------------------------------------------------------------------

#include "../include/AzElPa.hpp"

//------------------------------------------------------------------------------
// void AzElPa(double s, double &Az, double &El, double &dAds, double &dEds)
//------------------------------------------------------------------------------
/**
 * @brief Calcula el azimut, la elevación y las derivadas parciales respecto a las
 * coordenadas locales tangentes.
 * @param s [in] Coordenadas locales tangentes (sistema Este-Norte-Zenit).
 * @param Az [out] Azimut [rad].
 * @param El [out] Elevación [rad].
 * @param dAds [out] Derivadas parciales del azimut respecto a s.
 * @param dEds [out] Derivadas parciales de la elevación respecto a s.
 */
//------------------------------------------------------------------------------
void AzElPa(Matrix s, double &Az, double &El, Matrix &dAds, Matrix &dEds)
{
    double rho = sqrt(s(1, 1) * s(1, 1) + s(1, 2) * s(1, 2));
    Az = atan2(s(1, 1), s(1, 2));

    if (Az < 0.0) 
    {
        Az = Az + Const::pi2;
    }

    El = atan(s(1, 3) / rho);

    // Partials
    dAds(1, 1) = s(1, 2) / (rho * rho);
    dAds(1, 2) = -s(1, 1) / (rho * rho);
    dAds(1, 3) = 0.0;

    double aux = s.dot(s);
    dEds(1, 1) = (-s(1, 1) * s(1, 3) / rho) / aux;
    dEds(1, 2) = (-s(1, 2) * s(1, 3) / rho) / aux;
    dEds(1, 3) = (rho) / aux;
}
