//$Source$
//------------------------------------------------------------------------------
// angl
//------------------------------------------------------------------------------
/**
 * @file angl.cpp
 * @author Javier Jiménez Santana
 * @date 04/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/angl.hpp"

//------------------------------------------------------------------------------
// double angl(Matrix vec1, Matrix v2)
//------------------------------------------------------------------------------
/**
 * Calcula el ángulo entre dos vectores.
 *
 * @param vec1 [in] Vector 1.
 * @param vec2 [in] Vector 2.
 * @return Ángulo entre los dos vectores (-pi, pi).
 */
//------------------------------------------------------------------------------
double angl(Matrix vec1, Matrix vec2)
{
    double small = 0.00000001;
    double undefined = 999999.1;

    double magv1 = vec1.norm();
    double magv2 = vec2.norm();

    if(magv1 * magv2 > small * small)
    {
        double temp = vec1.dot(vec2) / (magv1 * magv2);
        if(abs(temp) > 1.0)
        {
            temp = sign(temp) * 1.0;
        }
        return acos(temp);
    }
    else
    {
        return undefined;
    }
}