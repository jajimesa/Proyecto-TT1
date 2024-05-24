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

void MeasUpdate(Matrix z, Matrix g, Matrix s, Matrix G, Matrix& P, int n,
                Matrix& K, Matrix& x)
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

//-------------------------------------------------------------------------------------
// void MeasUpdate(Double z, Double g, Double s, Matrix G, int n,
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
void MeasUpdate(double z, double g, double s, Matrix G, Matrix& P, int n,
                Matrix& K, Matrix& x)
{
    int m = 1; // m = z.n_column
    Matrix Inv_W = Matrix::zeros(m,m);

    Inv_W(1,1) = s*s;    // Inverse weight (measurement covariance)  

    // Kalman gain
    K.copy((P * G.transpose() * (1/(G * P * G.transpose() + Inv_W(1, 1))(1, 1))).transpose());    // No uso la función inverse porque es una matriz 1x1

    // State update
    x.copy(K * (z - g) + x);

    // Covariance update
    std::cout << "P_antes: " << std::endl << P << std::endl;
    std::cout << "K: " << std::endl << K << std::endl;
    std::cout << "G: " << std::endl << G << std::endl;
    std::cout << "K_por_G: " << std::endl << K.transpose() * G << std::endl;
    std::cout << "eye_menos_lo_demas: " << std::endl << Matrix::eye(n) -  K.transpose() * G << std::endl;
    P.copy((Matrix::eye(n) - K.transpose() * G)* P);
    std::cout << "P_despues: " << std::endl << P << std::endl;
}