//$Source$
//-------------------------------------------------------------------------------------------
// gibbs.cpp
//-------------------------------------------------------------------------------------------
/**
 * @file gibbs.cpp
 * @author Javier Jiménez Santana
 * @date 15/05/2024
 */
//-------------------------------------------------------------------------------------------

#include "../include/gibbs.hpp"

//-------------------------------------------------------------------------------------------
// void gibbs(Matrix r1, Matrix r2, Matrix r3,
//             Matrix &v2, double &theta, double &theta1, double &copa, std::string &error)
//-------------------------------------------------------------------------------------------
/**
 * @brief Solución del problema de determinación de órbita usando el método de Gibbs.
 *
 * @param r1 Vector de posición en IJK en t1 [m].
 * @param r2 Vector de posición en IJK en t2 [m].
 * @param r3 Vector de posición en IJK en t3 [m].
 * @param v2 [out] Vector de velocidad en IJK en t2 [m/s].
 * @param theta [out] Ángulo entre los vectores [rad].
 * @param theta1 [out] Ángulo entre los vectores [rad].
 * @param copa [out] Ángulo de coplanaridad [rad].
 * @param error [out] Flag indicando el estado de la operación.
 */
//-------------------------------------------------------------------------------------------
void gibbs(Matrix r1, Matrix r2, Matrix r3,
            Matrix &v2, double &theta, double &theta1, double &copa, std::string &error)
{
    double small = 0.00000001;
    theta = 0.0;
    error = "ok\0";
    theta1 = 0.0;

    double magr1 = r1.norm();
    double magr2 = r2.norm();
    double magr3 = r3.norm();

    v2.trueCopy(Matrix::zeros(1, 3));

    Matrix p = r2.cross(r3);
    Matrix q = r3.cross(r1);
    Matrix w = r1.cross(r2);
    Matrix pn = unit(p);
    Matrix r1n = unit(r1);
    copa = asin(pn.dot(r1n));

    if (abs(r1n.dot(pn)) > 0.017452406)
    {
        error = "not coplanar\0";
    }

    Matrix d = p + q + w;
    double magd = d.norm();
    Matrix n = p * magr1 + q * magr2 + w * magr3;
    double magn = n.norm();
    Matrix nn = unit(n);
    Matrix dn = unit(d);

    if ((abs(magd) < small) || (abs(magn) < small) || (nn.dot(dn) < small))
    {
        error = "impossible\0";
    }
    else
    {
        theta = angl(r1, r2);
        theta1 = angl(r2, r3);

        double r1mr2 = magr1 - magr2;
        double r3mr1 = magr3 - magr1;
        double r2mr3 = magr2 - magr3;
        Matrix s = r3 * r1mr2 + r2 * r3mr1 + r1 * r2mr3;
        Matrix b = d.cross(r2);
        double l = sqrt(Const::GM_Earth / (magd * magn));
        double tover2 = l / magr2;
        v2.trueCopy(b * tover2 + s * l);
    }
}