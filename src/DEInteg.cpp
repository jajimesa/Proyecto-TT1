//$Source$
//---------------------------------------------------------------------------------------------------------------
// DEInteg.cpp
//---------------------------------------------------------------------------------------------------------------
/**
 * @file DEInteg.cpp
 * @author Javier Jiménez Santana
 * @date 17/05/2024
 */
//-------------------------------------------------------------------------------------------------------------------------------

#include "../include/DEInteg.hpp"

//------------------------------------------------------------------------------------------------------------------------------
// Matrix DEInteg(void (*f)(double t, double *y, double *yp), double t, double tout, double relerr, double abserr, Matrix &y)
//------------------------------------------------------------------------------------------------------------------------------
/**
 * @brief Resuelve un sistema de ecuaciones diferenciales.
 * @param func Función que define el sistema de ecuaciones diferenciales.
 * @param t Tiempo inicial.
 * @param tout Tiempo final.
 * @param relerr Error relativo.
 * @param abserr Error absoluto.
 * @param y [in, out] Matriz de condiciones iniciales y resultado.
 * @return Matriz con el resultado del sistema de ecuaciones diferenciales.
 */
//------------------------------------------------------------------------------------------------------------------------------
Matrix DEInteg(void (*f)(double t, double *y, double *yp), double t, double tout, double relerr, double abserr, Matrix &y)
{
    // Declaración de variables necesarias para la función "de"
    int neqn = y.n_row * y.n_column;
    double* yArr = new double[neqn];
    double* yy = new double[neqn];
    double* wt = new double[neqn];
    double* p = new double[neqn];
    double* yp = new double[neqn];
    double* ypout = new double[neqn];
    double* phi = new double[neqn * 16];
    double alpha[12];
    double beta[12];
    double sig[13];
    double v[12];
    double w[12];
    double g[13];
    bool phase1 = true;
    double psi[12];
    double x = t;
    double h = 0.0;
    double hold = 0.0;
    bool start = true;
    double told = t;
    double delsgn = (tout > t) ? 1.0 : -1.0;
    int ns = 0;
    bool nornd = false;
    int k = 0;
    int kold = 0;
    int isnold = 0;
    int iflag = 1;

    de(f, neqn, yArr, t, tout, relerr, abserr, iflag,
       yy, wt, p, yp, ypout, phi, alpha, beta, sig, v, w, g,
       phase1, psi, x, h, hold, start, told, delsgn, ns, nornd, k, kold, isnold);

    Matrix result = Matrix::doubleArrayToMatrix(yArr, 1, neqn);
    y.trueCopy(result);

    // Limpieza de la memoria
    delete[] yArr;
    delete[] yy;
    delete[] wt;
    delete[] p;
    delete[] yp;
    delete[] ypout;
    delete[] phi;

    return y;
}