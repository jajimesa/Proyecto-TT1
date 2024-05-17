//$Source$
//------------------------------------------------------------------------------
// G_AccelHarmonic
//------------------------------------------------------------------------------
/**
 * @file G_AccelHarmonic.cpp
 * @author Javier Jiménez Santana
 * @date 16/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/G_AccelHarmonic.hpp"

//------------------------------------------------------------------------------
// Matrix G_AccelHarmonic(Matrix r, Matrix U, int n_max, int m_max)
//------------------------------------------------------------------------------
/**
 * @brief Calcula el gradiente del campo gravitatorio armónico de la Tierra.
 * 
 * @param r Vector de posición del satélite en el sistema verdadero de la fecha.
 * @param U Matriz de transformación al sistema fijo al cuerpo.
 * @param n_max Grado del modelo de gravedad.
 * @param m_max Orden del modelo de gravedad.
 * @return Matriz Gradiente (G=da/dr) en el sistema verdadero de la fecha.
 */
//------------------------------------------------------------------------------
Matrix G_AccelHarmonic(Matrix r, Matrix U, int n_max, int m_max)
{
    double d = 1.0;   // Position increment [m]
    
    Matrix G = Matrix::zeros(3, 3);
    Matrix dr = Matrix::zeros(1, 3);

    // Gradient
    for (int i = 1; i <= 3; i++)
    {
        // Set offset in i-th component of the position vector
        dr.copy(Matrix::zeros(1, 3));
        dr(1, i) = d;
        // Acceleration difference
        Matrix da = AccelHarmonic(r + dr / 2, U, n_max, m_max) - AccelHarmonic(r - dr / 2, U, n_max, m_max);
        // Derivative with respect to i-th axis
        for(int j = 1; j <= 3; j++)
        {
            G(j, i) = da(1, j) / d;
        }
    }    
    return G;
}