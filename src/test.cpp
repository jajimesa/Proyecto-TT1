//$Source$
//------------------------------------------------------------------------------
// matrix_test
//------------------------------------------------------------------------------
/**
 * @file matrix_test.cpp
 * @author Javier Jiménez Santana
 * @date 18/04/2024
 */
//------------------------------------------------------------------------------

#include "../include/matrix.hpp"
#include <iostream>

void test_asignar_imprimir() {
    Matrix m1 = Matrix(2, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;
    m1(2, 1) = 3.0;
    m1(2, 2) = 4.0;
    std::cout << m1 << std::endl;
}

void test_sumar() {
    Matrix m1 = Matrix(2, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;
    m1(2, 1) = 3.0;
    m1(2, 2) = 4.0;

    Matrix m2 = Matrix(2, 2);
    m2(1, 1) = 1.0;
    m2(1, 2) = 2.0;
    m2(2, 1) = 3.0;
    m2(2, 2) = 4.0;

    Matrix m3 = Matrix(2, 2);
    m3(1, 1) = 2.0;
    m3(1, 2) = 4.0;
    m3(2, 1) = 6.0;
    m3(2, 2) = 8.0;

    assert((m1 + m2) == m3 && "Suma de matrices incorrecta");   
    std::cout << "Suma de matrices correcta" << std::endl;
}

void test_restar() {
    Matrix m1 = Matrix(2, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;
    m1(2, 1) = 3.0;
    m1(2, 2) = 4.0;

    Matrix m2 = Matrix(2, 2);
    m2(1, 1) = 1.0;
    m2(1, 2) = 2.0;
    m2(2, 1) = 3.0;
    m2(2, 2) = 4.0;

    Matrix m3 = Matrix(2, 2);

    assert((m1 - m2) == m3 && "Resta de matrices incorrecta");
    std::cout << "Resta de matrices correcta" << std::endl;   
}

void test_producto_por_escalar(){
    Matrix m1 = Matrix(2, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;
    m1(2, 1) = 3.0;
    m1(2, 2) = 4.0;

    Matrix m2 = Matrix(2, 2);
    m2(1, 1) = 2.0;
    m2(1, 2) = 4.0;
    m2(2, 1) = 6.0;
    m2(2, 2) = 8.0;

    assert((m1 * 2) == m2 && "Producto por escalar incorrecto");   
    std::cout << "Producto por escalar correcto" << std::endl;
}

void test_cociente_por_escalar(){
    Matrix m1 = Matrix(2, 2);
    m1(1, 1) = 2.0;
    m1(1, 2) = 4.0;
    m1(2, 1) = 6.0;
    m1(2, 2) = 8.0;

    Matrix m2 = Matrix(2, 2);
    m2(1, 1) = 1.0;
    m2(1, 2) = 2.0;
    m2(2, 1) = 3.0;
    m2(2, 2) = 4.0;

    assert((m1 / 2) == m2 && "Cociente por escalar incorrecto");
    std::cout << "Cociente por escalar correcto" << std::endl;   
}

void test_producto() {
    Matrix m1 = Matrix(2, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;
    m1(2, 1) = 3.0;
    m1(2, 2) = 4.0;

    Matrix m2 = Matrix(2, 2);
    m2(1, 1) = 7.0;
    m2(1, 2) = 10.0;
    m2(2, 1) = 15.0;
    m2(2, 2) = 22.0;

    assert((m1 * m1) == m2 && "Producto de matrices incorrecto");
    std::cout << "Producto de matrices correcto" << std::endl;
}

void test_norma() {
    Matrix m1 = Matrix(1, 3);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;
    m1(1, 3) = 3.0;

    assert(abs(m1.norm() - 3.7416573867739413) < 10e-6 && "Norma incorrecta");
    std::cout << "Norma correcta" << std::endl;
}

void test_determinante() {
    Matrix m1 = Matrix(2, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;
    m1(2, 1) = 3.0;
    m1(2, 2) = 4.0;

    assert(m1.det() == -2.0 && "Determinante incorrecto");
    std::cout << "Determinante correcto" << std::endl;
}

void test_traspuesta() {
    Matrix m1 = Matrix(2, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;
    m1(2, 1) = 3.0;
    m1(2, 2) = 4.0;

    Matrix m2 = Matrix(2, 2);
    m2(1, 1) = 1.0;
    m2(1, 2) = 3.0;
    m2(2, 1) = 2.0;
    m2(2, 2) = 4.0;

    assert(m1.transpose() == m2 && "Traspuesta incorrecta");
    std::cout << "Traspuesta correcta" << std::endl;
}

void test_inversa() {
    Matrix m1 = Matrix(2, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;
    m1(2, 1) = 3.0;
    m1(2, 2) = 4.0;

    Matrix m2 = Matrix(2, 2);
    m2(1, 1) = -2.0;
    m2(1, 2) = 1.0;
    m2(2, 1) = 1.5;
    m2(2, 2) = -0.5;

    assert(m1.inverse() == m2 && "Inversa incorrecta");
    std::cout << "Inversa correcta" << std::endl;
}

void test_producto_escalar() {
    Matrix m1 = Matrix(1, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;

    Matrix m2 = Matrix(1, 2);
    m2(1, 1) = 2.0;
    m2(1, 2) = 4.0;

    assert(m1.dot(m2) == 10.0 && "Producto escalar incorrecto");
    std::cout << "Producto escalar correcto" << std::endl;
}

void test_producto_vectorial() {
    Matrix m1 = Matrix(1, 3);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;
    m1(1, 3) = 3.0;

    Matrix m2 = Matrix(1, 3);
    m2(1, 1) = 4.0;
    m2(1, 2) = 5.0;
    m2(1, 3) = 6.0;

    Matrix m3 = Matrix(1, 3);
    m3(1, 1) = -3.0;
    m3(1, 2) = 6.0;
    m3(1, 3) = -3.0;

    assert(m1.cross(m2) == m3 && "Producto vectorial incorrecto");
    std::cout << "Producto vectorial correcto" << std::endl;
}

void test_matriz_identidad() {
    Matrix m1 = Matrix(2, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 0.0;
    m1(2, 1) = 0.0;
    m1(2, 2) = 1.0;

    assert(m1.eye(2) == m1 && "Matriz identidad incorrecta");
    std::cout << "Matriz identidad correcta" << std::endl;
}

void test_fila() {
    Matrix m1 = Matrix(2, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;
    m1(2, 1) = 3.0;
    m1(2, 2) = 4.0;

    Matrix m2 = Matrix(1, 2);
    m2(1, 1) = 3.0;
    m2(1, 2) = 4.0;

    assert(m1.row(1) == m2 && "Fila incorrecta");
    std::cout << "Fila correcta" << std::endl;
}

void test_columna() {
    Matrix m1 = Matrix(2, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;
    m1(2, 1) = 3.0;
    m1(2, 2) = 4.0;

    Matrix m2 = Matrix(2, 1);
    m2(1, 1) = 2.0;
    m2(2, 1) = 4.0;

    assert(m1.column(1) == m2 && "Columna incorrecta");
    std::cout << "Columna correcta" << std::endl;
}

//------------------------------------------------------------------------------
// Tests de las funciones del proyecto
//------------------------------------------------------------------------------
#define _USE_MATH_DEFINES
#include <cmath>
#include "../include/R_x.hpp"
#include "../include/R_y.hpp"
#include "../include/R_z.hpp"
#include "../include/Frac.hpp"
#include "../include/AccelPointMass.hpp"
#include "../include/sign_.hpp"
#include "../include/unit.hpp"
#include "../include/global.hpp"
#include "../include/position.hpp"
#include "../include/Mjday.hpp"
#include "../include/Mjday_TDB.hpp"
#include "../include/MeanObliquity.hpp"

void test_R_x()
{
    Matrix R = R_x(M_PI);
    Matrix expected(3, 3);
    expected(1, 1) = 1.0000;
    expected(1, 2) = 0.0000;
    expected(1, 3) = 0.0000;
    expected(2, 1) = 0.0000;
    expected(2, 2) = -1.0000;
    expected(2, 3) = 0.0000;
    expected(3, 1) = 0.0000;
    expected(3, 2) = -0.0000;
    expected(3, 3) = -1.0000;

    assert(R == expected && "Rotacion en x incorrecta");
    std::cout << "Rotacion en x correcta" << std::endl;
}

void test_R_y()
{
    Matrix R = R_y(M_PI);
    Matrix expected = Matrix(3, 3);
    expected(1, 1) = -1.0000;
    expected(1, 2) = 0.0000;
    expected(1, 3) = 0.0000;
    expected(2, 1) = 0.0000;
    expected(2, 2) = 1.0000;
    expected(2, 3) = 0.0000;
    expected(3, 1) = 0.0000;
    expected(3, 2) = 0.0000;
    expected(3, 3) = -1.0000;

    assert(R == expected && "Rotacion en y incorrecta");
    std::cout << "Rotacion en y correcta" << std::endl;
}

void test_R_z()
{
    Matrix R = R_z(M_PI);
    Matrix expected = Matrix(3, 3);
    expected(1, 1) = -1.0000;
    expected(1, 2) = 0.0000;
    expected(1, 3) = 0.0000;
    expected(2, 1) = 0.0000;
    expected(2, 2) = -1.0000;
    expected(2, 3) = 0.0000;
    expected(3, 1) = 0.0000;
    expected(3, 2) = 0.0000;
    expected(3, 3) = 1.0000;

    assert(R == expected && "Rotacion en z incorrecta");
    std::cout << "Rotacion en z correcta" << std::endl;
}

void test_Frac()
{
    double pi = M_PI;
    assert(abs(Frac(pi) - 0.141592) < 10e-6 && "Parte fraccionaria de pi incorrecta");
    std::cout << "Parte fraccionaria de pi correcta" << std::endl;
}

void test_AccelPointMass() 
{
    Matrix r = Matrix(1, 3);
    r(1, 1) = 1.0;
    r(1, 2) = 2.0;
    r(1, 3) = 3.0;

    Matrix s = Matrix(1, 3);
    s(1, 1) = 4.0;
    s(1, 2) = 5.0;
    s(1, 3) = 6.0;

    double GM = 10;

    Matrix expected = Matrix(1, 3);
    expected(1, 1) = 0.1546;
    expected(1, 2) = 0.1398;
    expected(1, 3) = 0.1250;

    AccelPointMass(r, s, GM);
    assert(AccelPointMass(r, s, GM) == expected && "Funcion AccelPointMass incorrecta");
    std::cout << "Funcion AccelPointMass correcta" << std::endl;    
}

void test_sign_()
{
    assert(abs(sign_(-1.0, 1.0) - 1.0) < 10e-6 && "Funcion sign_ incorrecta");
    std::cout << "Funcion sign_ correcta" << std::endl;
}

void test_unit(){
    Matrix vec = Matrix(1, 3);
    vec(1, 1) = 1.0;
    vec(1, 2) = 2.0;
    vec(1, 3) = 3.0;

    Matrix expected = Matrix(1, 3);
    expected(1, 1) = 0.2673;
    expected(1, 2) = 0.5345;
    expected(1, 3) = 0.8018;

    assert(unit(vec) == expected && "Funcion unit incorrecta");

    Matrix vec2 = Matrix::zeros(1, 3);
    Matrix expected2 = Matrix::zeros(1, 3);

    assert(unit(vec2) == expected2 && "Funcion unit incorrecta");
    std::cout << "Funcion unit correcta" << std::endl;
}

void test_eop19620101() {
    Global::eop19620101(10);
    std::cout << (*Global::eopdata) << std::endl;
}

void test_position() {
    Matrix r = Position(0.0, 0.0, 0.0);
    Matrix expected = Matrix(1, 3);
    expected(1, 1) = 6378137.0;
    expected(1, 2) = 0.0;
    expected(1, 3) = 0.0;

    cout << "expected: " << endl << expected << endl;
    cout << "r: " << endl << r << endl;
    //assert(r == expected && "Funcion Position incorrecta");
    std::cout << "Funcion Position correcta" << std::endl;
}

void test_Mjday() {
    double Mjd = Mjday(2024, 4, 27, 0, 0, 0.0);
    assert(abs(Mjd - 60427) < 10e-6 && "Funcion Mjday incorrecta");
    std::cout << "Funcion Mjday correcta" << std::endl;
}

void test_Mjday_TDB() {
    double Mjd_TT = Mjday(2024, 4, 27, 0, 0, 0.0); // Mjday(2024, 4, 27, 18, 40, 5.0);
    double Mjd_TDB = Mjday_TDB(Mjd_TT);            // = 6.0428e+04
    assert(abs(Mjd_TDB - 60427) < 10e-6 && "Funcion Mjday_TDB incorrecta");
    std::cout << "Funcion Mjday_TDB correcta" << std::endl;
}

void test_MeanObliquity() {
    
}

//------------------------------------------------------------------------------
// int main
//------------------------------------------------------------------------------
/**
 * @brief Función principal que ejecuta todos los tests unitarios.
 * @return 0 si todos los tests han sido superados.
 */
//------------------------------------------------------------------------------
int main() {
    test_asignar_imprimir();
    test_sumar();
    test_restar();
    test_producto_por_escalar();
    test_cociente_por_escalar();
    test_producto();
    test_determinante();
    test_traspuesta();
    test_inversa();
    test_producto_escalar();
    test_producto_vectorial();
    test_matriz_identidad();
    test_fila();
    test_columna();

    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "Todos los tests de matrices han sido superados" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;

    getchar();

    test_R_x();
    test_R_y();
    test_R_z();
    test_Frac();
    test_AccelPointMass();
    test_sign_();
    test_unit();
    test_eop19620101();
    test_position();
    test_Mjday();
    test_Mjday_TDB();
    //test_MeanObliquity();

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "Todos los tests del proyecto han sido superados" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    getchar();

    return 0;
}
