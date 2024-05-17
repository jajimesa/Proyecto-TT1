//$Source$
//------------------------------------------------------------------------------
// Legendre
//------------------------------------------------------------------------------
/**
 * @file Legendre.cpp
 * @author Javier Jiménez Santana
 * @date 04/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/Legendre.hpp"

//------------------------------------------------------------------------------
// void Legendre(int n, int m, double fi, Matrix&pnm, Matrix& dpnm)
//------------------------------------------------------------------------------
/**
 * Calcula los polinomios de Legendre y sus derivadas hasta el grado n y orden m.
 * 
 * @param n [in] Grado del polinomio de Legendre.
 * @param m [in] Orden de la derivada.
 * @param fi [in] Ángulo de colatitud [rad].
 * @param pnm [out] Matriz, polinomios de Legendre. Inicializada a matriz cero.
 * @param dpnm [out] Matriz, derivadas de los polinomios de Legendre. También
 * inicializada a matriz cero.
 */
//------------------------------------------------------------------------------
void Legendre(int n, int m, double fi, Matrix& pnm, Matrix& dpnm) {
    
    pnm(1,1) = 1;
    dpnm(1,1) = 0;
    pnm(2,2) = sqrt(3)*cos(fi);
    dpnm(2,2) = -sqrt(3)*sin(fi);
    // diagonal coefficients
    for (int i = 2; i <= n; i++) {
        pnm(i+1,i+1) = sqrt((2.0*i+1)/(2.0*i))*cos(fi)*pnm(i,i);
    }
    for (int i = 2; i <= n; i++) {
        dpnm(i+1,i+1) = sqrt((2.0*i+1)/(2.0*i))*((cos(fi)*dpnm(i,i))-
                      (sin(fi)*pnm(i,i)));
    }
    // horizontal first step coefficients
    for (int i = 1; i <= n; i++) {
        pnm(i+1,i) = sqrt(2.0*i+1)*sin(fi)*pnm(i,i);
    }
    for (int i = 1; i <= n; i++) {
        dpnm(i+1,i) = sqrt(2.0*i+1)*((cos(fi)*pnm(i,i))+(sin(fi)*dpnm(i,i)));
    }
    // horizontal second step coefficients
    int j = 0;
    int k = 2;
    while(true) {
        for (int i = k; i <= n; i++) {
            pnm(i+1,j+1) = sqrt((2.0*i+1)/((i-j)*(i+j)))*((sqrt(2.0*i-1)*sin(fi)*pnm(i,j+1))-
                (sqrt(((i+j-1)*(i-j-1))/(2.0*i-3))*pnm(i-1,j+1)));
        }
        j++;
        k++;
        if (j > m) {
            break;
        }
    }
    j = 0;
    k = 2;
    while(true) {
        for (int i = k; i <= n; i++) {
            dpnm(i+1,j+1) = sqrt((2.0*i+1)/((i-j)*(i+j)))*((sqrt(2.0*i-1)*sin(fi)*dpnm(i,j+1))+
                 (sqrt(2.0*i-1)*cos(fi)*pnm(i,j+1))-(sqrt(((i+j-1)*(i-j-1))/(2.0*i-3))*dpnm(i-1,j+1)));
        }
        j++;
        k++;
        if (j > m) {
            break;
        }
    }
}

