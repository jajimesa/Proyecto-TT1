//$Source$
//------------------------------------------------------------------------------
// unit
//------------------------------------------------------------------------------
/**
 * @file unit.cpp
 * @author Javier Jiménez Santana
 * @date 21/04/2024
 */
//------------------------------------------------------------------------------

#include "../include/unit.hpp"

//------------------------------------------------------------------------------
// Matrix unit(Matrix vec)
//------------------------------------------------------------------------------
/**
 * @brief Función que calcula un vector unitario dado un vector original. Si se
 * introduce un vector nulo, el vector se establece a cero.
 * @param vec Vector.
 * @return Vector unitario.
 */
//------------------------------------------------------------------------------
Matrix unit(Matrix vec)
{
    double small = 0.000001;
    double magv = vec.norm();

    if (magv > small)
    {
        return vec / magv;
    }
    else
    {
        return Matrix(1, vec.n_column);
    }
}
