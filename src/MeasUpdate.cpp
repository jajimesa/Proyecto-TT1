//$Source$
//-------------------------------------------------------------------------------------
// MeasUpdate
//-------------------------------------------------------------------------------------
/**
 * @file MeasUpdate.hpp
 * @author Javier Jiménez Santana
 * @date 05/05/2024
 */
//-------------------------------------------------------------------------------------

#include "../include/MeasUpdate.hpp"

//-------------------------------------------------------------------------------------
// void MeasUpdate(Matrix z, Matrix g, Matrix s, Matrix G, int n,
//                 Matrix& K, Matrix& x, Matrix& P)
//-------------------------------------------------------------------------------------
/**
 * @brief Actualiza el estado y la covarianza del filtro de Kalman.
 * @param z Vector de medidas.
 * @param g Vector de medidas estimadas.
 * @param s Vector de desviaciones estándar de las medidas.
 * @param G Matriz de sensibilidad de las medidas.
 * @param n Número de estados.
 * @param K [out] Ganancia de Kalman.
 * @param x [out] Estado actualizado.
 * @param P [out] Covarianza actualizada.
 */
//-------------------------------------------------------------------------------------
#include <iostream>

void MeasUpdate(Matrix z, Matrix g, Matrix s, Matrix G, int n,
                Matrix& K, Matrix& x, Matrix& P)
{
    int m = z.n_column;
    Matrix Inv_W = Matrix::zeros(m,m);

    for(int i=1; i<=m; i++)
    {
        Inv_W(i,i) = s(1,i)*s(1,i);    // Inverse weight (measurement covariance)  
    }

    // Kalman gain
    //std::cout << "Empieza el primer producto" << std::endl;
    K.copy(P * G.transpose() * (Inv_W + G * P * G.transpose()).inverse());  // Son todo productos y sumas de matrices cuadradas
    //std::cout << "Primer producto funciona" << std::endl;

    // State update
    Matrix aux = (z - g).transpose();   // Matriz fila se convierte a columna
    //std::cout << aux << std::endl;
    //std::cout << "Transpuesta de matriz fila funciona" << std::endl;

    x.copy(K * aux + x);    // K * aux se convierte en matriz fila y se puede sumar a x
    //std::cout << "Ultimo producto funciona" << std::endl;

    // Covariance update
    P.copy((Matrix::eye(n) - K * G) * P);   // Son todo productos y sumas de matrices cuadradas
}