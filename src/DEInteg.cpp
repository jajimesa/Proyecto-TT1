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
 * @param neqn Número de ecuaciones diferenciales.
 * @param y [in, out] Matriz de condiciones iniciales y resultado.
 * @param yArr Array de condiciones iniciales y resultado.
 * @param work Array de trabajo.
 * @param iwork Array de trabajo.
 * @return Matriz con el resultado del sistema de ecuaciones diferenciales.
 */
//------------------------------------------------------------------------------------------------------------------------------
Matrix DEInteg(void (*f)(double t, double *y, double *yp), double t, double tout, double relerr, double abserr, int neqn,
               Matrix &y, double *yArr, double *work, int *iwork)
{
    int iflag = 1;

    // Convierto la matriz y a un array de C++
    Matrix::matrixToDoubleArray(y, yArr);

    //std::cout << "Estado inicial de yArr: ";
    //for (int i = 0; i < neqn; ++i) {
    //    std::cout << yArr[i] << " ";
    //}
    //std::cout << std::endl;

    // Llamo a la función de integración "ode"
    ode(f, neqn, yArr, t, tout, relerr, abserr, iflag, work, iwork);
    if (iflag != 2) {
        std::cerr << "Error en la integración, iflag = " << iflag << std::endl;
    }

    //std::cout << "Estado final de yArr: ";
    //for (int i = 0; i < neqn; ++i) {
    //    std::cout << yArr[i] << " ";
    //}
    //std::cout << std::endl;

    // Convertir el resultado de vuelta a una matriz de tu clase Matrix
    Matrix result = Matrix::doubleArrayToMatrix(yArr, 1, neqn);

    // Asigno el resultado a y usando trueCopy
    y.trueCopy(result);

    return y;
}