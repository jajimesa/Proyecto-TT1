//$Source$
//------------------------------------------------------------------------------
// AccelHarmonic
//------------------------------------------------------------------------------
/**
 * @file AccelHarmonic.cpp
 * @author Javier Jiménez Santana
 * @date 05/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/AccelHarmonic.hpp"

//------------------------------------------------------------------------------
// Matrix AccelHarmonic(Matrix r, Matrix E, int n_max, int m_max)
//------------------------------------------------------------------------------
/**
 * Computación de la aceleración debida al campo gravitatorio armónico del
 * cuerpo central.
 *
 * @param r Vector de posición del satélite en el sistema inercial.
 * @param E Matriz de transformación al sistema fijo al cuerpo.
 * @param n_max Grado máximo.
 * @param m_max Orden máximo (m_max<=n_max; m_max=0 para zonales, solamente).
 * @return Aceleración (a=d^2r/dt^2).
 */
//------------------------------------------------------------------------------
Matrix AccelHarmonic(Matrix r, Matrix E, int n_max, int m_max)
{
    Matrix Cnm = *Global::Cnm;
    Matrix Snm = *Global::Snm;

    double r_ref, gm, d, latgc, lon, dUdr, dUdlatgc, dUdlon, q3, q2, q1, b1, b2, b3, r2xy, ax, ay, az;

    r_ref = 6378.1363e3;   // Earth's radius [m]; GGM03S
    gm    = 398600.4415e9; // [m^3/s^2]; GGM03S

    // Body-fixed position
    Matrix r_bf = E * r.transpose();    // Para convertir r en columna, resultado matriz fila

    // Auxiliary quantities
    d = r_bf.norm();                     // distance
    latgc = asin(r_bf(1, 3) / d);
    lon = atan2(r_bf(1, 2), r_bf(1, 1));

    Matrix pnm = Matrix::zeros(n_max + 1, n_max + 1);
    Matrix dpnm = Matrix::zeros(n_max + 1, n_max + 1);
    
    // TODO: borrar y descomentar legendre
    pnm(1, 1) = 1;
    pnm(1, 2) = 0;
    pnm(1, 3) = 0;
    pnm(2, 1) = 0.365023097412765;
    pnm(2, 2) = 1.6931503590512;
    pnm(2, 3) = 0;
    pnm(3, 1) = -0.969065058706688;
    pnm(3, 2) = 0.797884903186598;
    pnm(3, 3) = 1.85048442124237;

    dpnm(1, 1) = 0;
    dpnm(1, 2) = 0;
    dpnm(1, 3) = 0;
    dpnm(2, 1) = 1.6931503590512;
    dpnm(2, 2) = -0.365023097412765;
    dpnm(2, 3) = 0;
    dpnm(3, 1) = 1.38197719091136;
    dpnm(3, 2) = 3.52895433876207;
    dpnm(3, 3) = -0.797884903186598;
    Legendre(n_max, m_max, latgc, pnm, dpnm);

    dUdr = 0;
    dUdlatgc = 0;
    dUdlon = 0;
    q3 = 0;
    q2 = q3;
    q1 = q2;
    for (int n = 0; n <= n_max; n++)
    {
        b1 = (-gm / pow(d, 2)) * pow(r_ref / d, n) * (n + 1);
        b2 = (gm / d) * pow(r_ref / d, n);
        b3 = (gm / d) * pow(r_ref / d, n);
        for (int m = 0; m <= m_max; m++)
        {
            q1 += pnm(n + 1, m + 1) * (Cnm(n + 1, m + 1) * cos(m * lon) + Snm(n + 1, m + 1) * sin(m * lon));
            q2 += dpnm(n + 1, m + 1) * (Cnm(n + 1, m + 1) * cos(m * lon) + Snm(n + 1, m + 1) * sin(m * lon));
            q3 += m * pnm(n + 1, m + 1) * (Snm(n + 1, m + 1) * cos(m * lon) - Cnm(n + 1, m + 1) * sin(m * lon));
        }
        dUdr += q1 * b1;
        dUdlatgc += q2 * b2;
        dUdlon += q3 * b3;
        q3 = 0;
        q2 = q3;
        q1 = q2;
    }

    // Body-fixed acceleration
    r2xy = pow(r_bf(1, 1), 2) + pow(r_bf(1, 2), 2);

    ax = (1 / d * dUdr - r_bf(1, 3) / (pow(d, 2) * sqrt(r2xy)) * dUdlatgc) * r_bf(1, 1) - (1 / r2xy * dUdlon) * r_bf(1, 2);
    ay = (1 / d * dUdr - r_bf(1, 3) / (pow(d, 2) * sqrt(r2xy)) * dUdlatgc) * r_bf(1, 2) + (1 / r2xy * dUdlon) * r_bf(1, 1);
    az = 1 / d * dUdr * r_bf(1, 3) + sqrt(r2xy) / pow(d, 2) * dUdlatgc;

    Matrix a_bf(1, 3);
    a_bf(1, 1) = ax;
    a_bf(1, 2) = ay;
    a_bf(1, 3) = az;

    // Inertial acceleration
    Matrix a = E.transpose() * a_bf.transpose();

    return a;
}