//$Source$
//-------------------------------------------------------------------------------------------------------------
// elements
//-------------------------------------------------------------------------------------------------------------
/**
 * @file elements.cpp
 * @author Javier Jiménez Santana
 * @date 04/05/2024
 */
//-------------------------------------------------------------------------------------------------------------

#include "../include/elements.hpp"

//-------------------------------------------------------------------------------------------------------------
// void elements(Matrix y, double& p, double& a, double& e, double& i, double& Omega, double& omega, double& M)
//-------------------------------------------------------------------------------------------------------------
/**
 * Calcula los elementos keplerianos osculantes a partir del vector de estado del satélite para órbitas 
 * elípticas.
 *
 * @param y [in] Vector de estado (x,y,z,vx,vy,vz).
 * @param p [out] Semilatus rectum [m].
 * @param a [out] Semieje mayor.
 * @param e [out] Excentricidad.
 * @param i [out] Inclinación [rad].
 * @param Omega [out] Longitud del nodo ascendente [rad].
 * @param omega [out] Argumento del perihelio [rad].
 * @param M [out] Anomalía media [rad].
 */
//-------------------------------------------------------------------------------------------------------------
void elements(Matrix y, double& p, double& a, double& e, double& i, double& Omega, double& omega, double& M)
{
    Matrix r = Matrix(1, 3);
    Matrix v = Matrix(1, 3);

    // r = y(1:3);
    r(1, 1) = y(1, 1);
    r(1, 2) = y(1, 2);
    r(1, 3) = y(1, 3);

    // v = y(4:6);
    v(1, 1) = y(1, 4);
    v(1, 2) = y(1, 5);
    v(1, 3) = y(1, 6);

    Matrix h = r.cross(v); // Areal velocity
    double magh = h.norm();
    p = magh * magh / Const::GM_Earth;
    double H = h.norm();

    Omega = atan2(h(1, 1), -h(1, 2)); // Long. ascend. node
    Omega = mod(Omega, Const::pi2);
    i = atan2(sqrt(h(1, 1) * h(1, 1) + h(1, 2) * h(1, 2)), h(1, 3)); // Inclination
    double u = atan2(r(1, 3) * H, -r(1, 1) * h(1, 2) + r(1, 2) * h(1, 1)); // Arg. of latitude

    double R = r.norm(); // Distance

    a = 1 / (2 / R - v.dot(v) / Const::GM_Earth); // Semi-major axis

    double eCosE = 1 - R / a; // e*cos(E)
    double eSinE = r.dot(v) / sqrt(Const::GM_Earth * a); // e*sin(E)

    double e2 = eCosE * eCosE + eSinE * eSinE;
    e = sqrt(e2); // Eccentricity
    double E = atan2(eSinE, eCosE); // Eccentric anomaly

    M = mod(E - eSinE, Const::pi2); // Mean anomaly

    double nu = atan2(sqrt(1.0 - e2) * eSinE, eCosE - e2); // True anomaly

    omega = mod(u - nu, Const::pi2); // Arg. of perihelion
}