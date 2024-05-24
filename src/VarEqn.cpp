//$Source$
//------------------------------------------------------------------------------
// VarEqn.cpp
//------------------------------------------------------------------------------
/**
 * @file VarEqn.cpp
 * @author Javier Jiménez Santana
 * @date 16/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/VarEqn.hpp"

//------------------------------------------------------------------------------
// Matrix VarEqn(double x, Matrix yPhi)
//------------------------------------------------------------------------------
/**
 * @brief Calcula las ecuaciones variacionales, es decir, la derivada del vector 
 * de estado y la matriz de transición de estado.
 *
 * @param x Tiempo desde la época en [s].
 * @param yPhi Vector de dimensión (6+36) que comprende el vector de estado (y
 * y la matriz de transición de estado (Phi) en orden de almacenamiento
 * por columnas.
 * @return Derivada de yPhi.
 */
//------------------------------------------------------------------------------
Matrix VarEqn(double x, Matrix yPhi)
{
    Matrix eopdata = *Global::eopdata;
    Param AuxParam = Global::AuxParam;

    double x_pole = 0.0;
    double y_pole = 0.0;
    double UT1_UTC = 0.0;
    double LOD = 0.0;
    double dpsi = 0.0;
    double deps = 0.0;
    double dx_pole = 0.0;
    double dy_pole = 0.0;
    double TAI_UTC = 0.0;
    IERS(eopdata, AuxParam.Mjd_UTC, 'l', x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC);
    double UT1_TAI = 0.0;
    double UTC_GPS = 0.0;
    double UT1_GPS = 0.0;
    double TT_UTC = 0.0;
    double GPS_UTC = 0.0;
    timediff(UT1_UTC, TAI_UTC, UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC);
    double Mjd_UT1 = AuxParam.Mjd_TT + (UT1_UTC - TT_UTC) / 86400.0;

    //std::cout << "x_pole: " << x_pole << std::endl;
    //std::cout << "y_pole: " << y_pole << std::endl;
    //std::cout << "UT1_UTC: " << UT1_UTC << std::endl;
    //std::cout << "LOD: " << LOD << std::endl;
    //std::cout << "dpsi: " << dpsi << std::endl;
    //std::cout << "deps: " << deps << std::endl;
    //std::cout << "dx_pole: " << dx_pole << std::endl;
    //std::cout << "dy_pole: " << dy_pole << std::endl;
    //std::cout << "TAI_UTC: " << TAI_UTC << std::endl;
    //std::cout << "UT1_TAI: " << UT1_TAI << std::endl;
    //std::cout << "UTC_GPS: " << UTC_GPS << std::endl;
    //std::cout << "UT1_GPS: " << UT1_GPS << std::endl;
    //std::cout << "TT_UTC: " << TT_UTC << std::endl;
    //std::cout << "GPS_UTC: " << GPS_UTC << std::endl;
    //std::cout << "Mjd_UT1: " << Mjd_UT1 << std::endl;

    // Transformation matrix
    Matrix P = PrecMatrix(Const::MJD_J2000, AuxParam.Mjd_TT + x / 86400.0);
    Matrix N = NutMatrix(AuxParam.Mjd_TT + x / 86400.0);
    Matrix T = N * P;
    Matrix EpoleMatrix = PoleMatrix(x_pole, y_pole);
    Matrix EghaMatrix = GHAMatrix(Mjd_UT1);
    Matrix E = PoleMatrix(x_pole, y_pole) * GHAMatrix(Mjd_UT1) * T;

    //std::cout << "P: " << std::endl << P << std::endl;
    //std::cout << "N: " << std::endl << N << std::endl;
    //std::cout << "T: " << std::endl << T << std::endl;
    //std::cout << "EpoleMatrix: " << std::endl << EpoleMatrix << std::endl;
    //std::cout << "EghaMatrix: " << std::endl << EghaMatrix << std::endl;
    //std::cout << "E: " << std::endl << E << std::endl;

    // State vector components
    Matrix r = yPhi.subvectorFromRow(1, 1, 3);
    Matrix v = yPhi.subvectorFromRow(1, 4, 6);
    Matrix Phi = Matrix::zeros(6, 6);

    //std::cout << "r: " << r << std::endl;
    //std::cout << "v: " << v << std::endl;

    // State transition matrix
    Matrix yPhiAux = Matrix(1, 6);
    for (int j = 1; j <= 6; j++) {
        yPhiAux.copy(yPhi.subvectorFromRow(1, 6*j+1, 6*j+6)); // la fila que copio
        for (int i = 1; i <= 6; i++) {
            Phi(i, j) = yPhiAux(1, i); // la columna que copio
        }
    }
    //std::cout << "Phi: " << std::endl << Phi << std::endl;

    // Acceleration and gradient
    Matrix a = AccelHarmonic(r, E, AuxParam.n, AuxParam.m);
    Matrix G = G_AccelHarmonic(r, E, AuxParam.n, AuxParam.m);

    //std::cout << "a: " << a << std::endl;
    //std::cout << "G: " << std::endl << G << std::endl;

    // Time derivative of state transition matrix
    Matrix yPhip = Matrix::zeros(1, 42);
    Matrix dfdy = Matrix::zeros(6, 6);

    for (int i = 1; i <= 3; i++)
    {
        for (int j = 1; j <= 3; j++)
        {
            dfdy(i, j) = 0.0;                 // dv/dr(i,j)
            dfdy(i + 3, j) = G(i, j);         // da/dr(i,j)
            if (i == j)
            {
                dfdy(i, j + 3) = 1.0;
            }
            else
            {
                dfdy(i, j + 3) = 0.0;          // dv/dv(i,j)
            }
            dfdy(i + 3, j + 3) = 0.0;         // da/dv(i,j)
        }
    }

    Matrix Phip = dfdy * Phi;

    //std::cout << "dfdy: " << std::endl << dfdy << std::endl;
    //std::cout << "Phip: " << std::endl << Phip << std::endl;

    // Derivative of combined state vector and state transition matrix
    for (int i = 1; i <= 3; i++)
    {
        yPhip(1, i) = v(1, i);                 // dr/dt(i)
        yPhip(1, i + 3) = a(1, i);             // dv/dt(i)
    }

    for (int i = 1; i <= 6; i++)
    {
        for (int j = 1; j <= 6; j++)
        {
            yPhip(1, 6 * j + i) = Phip(i, j);     // dPhi/dt(i,j)
        }
    }

    return yPhip;
}

//------------------------------------------------------------------------------
// void VarEqn(double t, double *y, double *yp)
//------------------------------------------------------------------------------
/**
 * @brief Envoltorio de la función VarEqn para ser utilizada en DEInteg.
 *
 * @param t Tiempo desde la época en [s].
 * @param y Vector de dimensión (6+36) que comprende el vector de estado (y
 * y la matriz de transición de estado (Phi) en orden de almacenamiento
 * por columnas.
 * @param yp Vector de derivadas de y.
 */
//------------------------------------------------------------------------------
void VarEqn(double t, double *y, double *yp)
{
    Matrix yMatrix = Matrix::doubleArrayToMatrix(y, 1, 42);
    Matrix ypMatrix = VarEqn(t, yMatrix);
    Matrix::matrixToDoubleArray(ypMatrix, yp);
}