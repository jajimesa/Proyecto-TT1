//$Header$
//------------------------------------------------------------------------------------------
// hgibbs.cpp
//------------------------------------------------------------------------------------------
/**
 * @file hgibbs.cpp
 * @author Javier Jiménez Santana
 * @date 15/05/2024
 */
//------------------------------------------------------------------------------------------

#include "../include/hgibbs.hpp"

//------------------------------------------------------------------------------------------
// void hgibbs(Matrix r1, Matrix r2, Matrix r3, double Mjd1, double Mjd2, double Mjd3,
//             Matrix &v2, double &theta, double &theta1, double &copa, std::string &error)
//------------------------------------------------------------------------------------------
/**
 * @brief Implementa la aproximación de Herrick-Gibbs para la determinación de órbita.
 *
 * @param r1 Vector de posición #1 en IJK [m].
 * @param r2 Vector de posición #2 en IJK [m].
 * @param r3 Vector de posición #3 en IJK [m].
 * @param Mjd1 Fecha juliana modificada del 1er avistamiento.
 * @param Mjd2 Fecha juliana modificada del 2º avistamiento.
 * @param Mjd3 Fecha juliana modificada del 3er avistamiento.
 * @param v2 [out] Vector de velocidad en IJK en r2 [m/s].
 * @param theta [out] Ángulo entre vectores [rad].
 * @param theta1 [out] Ángulo entre vectores [rad].
 * @param copa [out] Ángulo de coplanaridad [rad].
 * @param error [out] Indicador de éxito.
 */
//------------------------------------------------------------------------------------------
void hgibbs(Matrix r1, Matrix r2, Matrix r3, double Mjd1, double Mjd2, double Mjd3,
            Matrix &v2, double &theta, double &theta1, double &copa, std::string &error)
{
    error =  "ok\0";
    theta = 0.0;
    theta1 = 0.0;
    double magr1 = r1.norm();
    double magr2 = r2.norm();
    double magr3 = r3.norm();

    v2.trueCopy(Matrix::zeros(1, 3));

    double tolangle = 0.01745329251994;
    double dt21 = (Mjd2 - Mjd1) * 86400.0;
    double dt31 = (Mjd3 - Mjd1) * 86400.0;
    double dt32 = (Mjd3 - Mjd2) * 86400.0;

    Matrix p = r2.cross(r3);
    Matrix pn = unit(p);
    Matrix r1n = unit(r1);
    copa = asin(pn.dot(r1n));

    if (abs(r1n.dot(pn)) > 0.017452406)
    {
        error = "not coplanar\0";
    }

    theta = angl(r1, r2);
    theta1 = angl(r2, r3);

    if ((theta > tolangle) | (theta1 > tolangle))
    {
        error = "angl > 1ø \0";
    }

    double term1 = -dt32 * (1.0 / (dt21 * dt31) + Const::GM_Earth / (12.0 * magr1 * magr1 * magr1));
    double term2 = (dt32 - dt21) * (1.0 / (dt21 * dt32) + Const::GM_Earth / (12.0 * magr2 * magr2 * magr2));
    double term3 = dt21 * (1.0 / (dt32 * dt31) + Const::GM_Earth / (12.0 * magr3 * magr3 * magr3));

    v2.trueCopy(r1 * term1 + r2 * term2 + r3 * term3);
}