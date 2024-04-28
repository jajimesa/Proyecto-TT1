//$Source$
//----------------------------------------------------------------------------------------
// Cheb3D
//----------------------------------------------------------------------------------------
/**
 * @file Cheb3D.cpp
 * @author Javier Jiménez Santana
 * @date 28/04/2024
 */
//----------------------------------------------------------------------------------------

#include "../include/Cheb3D.hpp"

//----------------------------------------------------------------------------------------
//  Matrix Cheb3D(double t, int N, double Ta, double Tb, Matrix Cx, Matrix Cy, Matrix Cz)
//----------------------------------------------------------------------------------------
/**
 * Aproximación de Chebyshev de vectores en 3D.
 *
 * @param t Tiempo [s].
 * @param N Número de coeficientes.
 * @param Ta Inicio del intervalo de tiempo [s].
 * @param Tb Fin del intervalo de tiempo [s].
 * @param Cx Coeficientes de Chebyshev para la coordenada x.
 * @param Cy Coeficientes de Chebyshev para la coordenada y.
 * @param Cz Coeficientes de Chebyshev para la coordenada z.
 */
//----------------------------------------------------------------------------------------
Matrix Cheb3D(double t, int N, double Ta, double Tb, Matrix Cx, Matrix Cy, Matrix Cz)
{
    // Check validity
    if ((t < Ta) || (Tb < t))
    {
        exit(EXIT_FAILURE); // Time out of range in Cheb3D::Value
    }

    // Clenshaw algorithm
    double tau = (2 * t - Ta - Tb) / (Tb - Ta);

    Matrix f1 = Matrix::zeros(1, 3);
    Matrix f2 = Matrix::zeros(1, 3);

    // for i=N:-1:2 significa que comienza con i=N y disminuye en uno en cada iteración
    // hasta que alcanza el valor 2.
    for (int i = N; i >= 2; i--)
    {
        Matrix old_f1(1, 3);
        old_f1(1, 1) = f1(1, 1);
        old_f1(1, 2) = f1(1, 2);
        old_f1(1, 3) = f1(1, 3);
        
        Matrix aux(1, 3);
        aux(1, 1) = Cx(1, i);
        aux(1, 2) = Cy(1, i);
        aux(1, 3) = Cz(1, i);

        f1 * (2 * tau) - f2 + aux;
        
        f2(1, 1) = old_f1(1, 1);
        f2(1, 2) = old_f1(1, 2);
        f2(1, 3) = old_f1(1, 3);
    }

    Matrix aux2(1, 3);
    aux2(1, 1) = Cx(1, 1);
    aux2(1, 2) = Cy(1, 1);
    aux2(1, 3) = Cz(1, 1);

    Matrix ChebApp = (f1 * tau) - f2 + aux2;
    return ChebApp;
}