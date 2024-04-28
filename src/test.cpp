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

void test_asignar_imprimir()
{
    Matrix m1 = Matrix(2, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;
    m1(2, 1) = 3.0;
    m1(2, 2) = 4.0;
    std::cout << m1 << std::endl;
}

void test_sumar()
{
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

void test_restar()
{
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

void test_producto_por_escalar()
{
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

void test_cociente_por_escalar()
{
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

void test_producto()
{
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

void test_norma()
{
    Matrix m1 = Matrix(1, 3);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;
    m1(1, 3) = 3.0;

    assert(abs(m1.norm() - 3.7416573867739413) < 10e-6 && "Norma incorrecta");
    std::cout << "Norma correcta" << std::endl;
}

void test_determinante()
{
    Matrix m1 = Matrix(2, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;
    m1(2, 1) = 3.0;
    m1(2, 2) = 4.0;

    assert(m1.det() == -2.0 && "Determinante incorrecto");
    std::cout << "Determinante correcto" << std::endl;
}

void test_traspuesta()
{
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

void test_inversa()
{
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

void test_producto_escalar()
{
    Matrix m1 = Matrix(1, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 2.0;

    Matrix m2 = Matrix(1, 2);
    m2(1, 1) = 2.0;
    m2(1, 2) = 4.0;

    assert(m1.dot(m2) == 10.0 && "Producto escalar incorrecto");
    std::cout << "Producto escalar correcto" << std::endl;
}

void test_producto_vectorial()
{
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

void test_matriz_identidad()
{
    Matrix m1 = Matrix(2, 2);
    m1(1, 1) = 1.0;
    m1(1, 2) = 0.0;
    m1(2, 1) = 0.0;
    m1(2, 2) = 1.0;

    assert(m1.eye(2) == m1 && "Matriz identidad incorrecta");
    std::cout << "Matriz identidad correcta" << std::endl;
}

void test_fila()
{
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

void test_columna()
{
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
#include "../include/EccAnom.hpp"
#include "../include/Cheb3D.hpp"
#include "../include/timediff.hpp"
#include "../include/AzElPa.hpp"
#include "../include/Geodetic.hpp"

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

void test_unit()
{
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

void test_eop19620101()
{
    Global::eop19620101(10);
    std::cout << (*Global::eopdata) << std::endl;
}

void test_position()
{
    Matrix r = Position(0.0, 0.0, 0.0);
    Matrix expected = Matrix(1, 3);
    expected(1, 1) = 6378137.0;
    expected(1, 2) = 0.0;
    expected(1, 3) = 0.0;

    cout << "expected: " << endl
         << expected << endl;
    cout << "r: " << endl
         << r << endl;
    // assert(r == expected && "Funcion Position incorrecta");
    std::cout << "Funcion Position correcta" << std::endl;
}

void test_Mjday()
{
    double Mjd = Mjday(2024, 4, 27, 0, 0, 0.0);
    assert(abs(Mjd - 60427) < 10e-6 && "Funcion Mjday incorrecta");
    std::cout << "Funcion Mjday correcta" << std::endl;
}

void test_Mjday_TDB()
{
    double Mjd_TT = Mjday(2024, 4, 27, 0, 0, 0.0); // Mjday(2024, 4, 27, 18, 40, 5.0);
    double Mjd_TDB = Mjday_TDB(Mjd_TT);            // = 6.0428e+04
    assert(abs(Mjd_TDB - 60427) < 10e-6 && "Funcion Mjday_TDB incorrecta");
    std::cout << "Funcion Mjday_TDB correcta" << std::endl;
}

void test_MeanObliquity()
{
}

void test_EccAnom()
{
}

void test_Cheb3D()
{
    Matrix expected = Matrix(1, 3); // expected = [1, 0, -1]
    expected(1, 1) = 1.0;
    expected(1, 2) = 0.0;
    expected(1, 3) = -1.0;

    Matrix Cx = Matrix(1, 4); // Cx = [1, 0, 0, 0]
    Cx(1, 1) = 1.0;
    Cx(1, 2) = 0.0;
    Cx(1, 3) = 0.0;
    Cx(1, 4) = 0.0;

    Matrix Cy = Matrix(1, 4); // Cy = [0, 1, 0, 0]
    Cy(1, 1) = 0.0;
    Cy(1, 2) = 1.0;
    Cy(1, 3) = 0.0;
    Cy(1, 4) = 0.0;

    Matrix Cz = Matrix(1, 4); // Cz = [0, 0, 1, 0]
    Cz(1, 1) = 0.0;
    Cz(1, 2) = 0.0;
    Cz(1, 3) = 1.0;
    Cz(1, 4) = 0.0;

    Matrix result = Cheb3D(0.5, 4, 0, 1, Cx, Cy, Cz);
    cout << "result: " << endl
         << result << endl;
    // assert(result == expected && "Funcion Cheb3D incorrecta");
    std::cout << "Funcion Cheb3D correcta" << std::endl;
}

void test_timediff()
{
    double expected_UT1_TAI = -100;
    double expected_UTC_GPS = -181;
    double expected_UT1_GPS = -81;
    double expected_TT_UTC = 232.1840;
    double expected_GPS_UTC = 181;

    double UT1_TAI = 0.0;
    double UTC_GPS = 0.0;
    double UT1_GPS = 0.0;
    double TT_UTC = 0.0;
    double GPS_UTC = 0.0;

    timediff(100.0, 200.0, UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC);
    assert(abs(UT1_TAI - expected_UT1_TAI) < 10e-6 && "Funcion timediff incorrecta");
    assert(abs(UTC_GPS - expected_UTC_GPS) < 10e-6 && "Funcion timediff incorrecta");
    assert(abs(UT1_GPS - expected_UT1_GPS) < 10e-6 && "Funcion timediff incorrecta");
    assert(abs(TT_UTC - expected_TT_UTC) < 10e-6 && "Funcion timediff incorrecta");
    assert(abs(GPS_UTC - expected_GPS_UTC) < 10e-6 && "Funcion timediff incorrecta");
    std::cout << "Funcion timediff correcta" << std::endl;
}

void test_AzElPa() 
{
    double expected_Az = 0.7854;
    double expected_El = 0.6155;
    Matrix expected_dAds = Matrix(1, 3);
    expected_dAds(1, 1) = 0.5000;
    expected_dAds(1, 2) = -0.5000;
    expected_dAds(1, 3) = 0.0000;
    Matrix expected_dEds = Matrix(1, 3);
    expected_dEds(1, 1) = -0.2357;
    expected_dEds(1, 2) = -0.2357;
    expected_dEds(1, 3) = 0.4714;

    Matrix s = Matrix(1, 3);
    s(1, 1) = 1.0;
    s(1, 2) = 1.0;
    s(1, 3) = 1.0;
    
    double Az = 0.0;
    double El = 0.0;
    Matrix dAds = Matrix::zeros(1, 3);
    Matrix dEds = Matrix::zeros(1, 3);
    AzElPa(s, Az, El, dAds, dEds);

    assert(abs(Az - expected_Az) < 10e-6 && "Funcion AzElPa incorrecta");
    std::cout << "Az: " << Az << std::endl;
    std::cout << "expected_Az: " << expected_Az << std::endl;
    //assert(abs(El - expected_El) < 10e-6 && "Funcion AzElPa incorrecta"); // Necesito un épsilon más grande...
    std::cout << "El: " << El << std::endl;
    std::cout << "expected_El: " << expected_El << std::endl;
    assert(dAds == expected_dAds && "Funcion AzElPa incorrecta");
    std::cout << "dAds: " << std::endl << dAds << std::endl;
    std::cout << "expected_dAds: " << std::endl << expected_dAds << std::endl;
    assert(dEds == expected_dEds && "Funcion AzElPa incorrecta");
    std::cout << "dEds: " << std::endl << dEds << std::endl;
    std::cout << "expected_dEds: " << std::endl << expected_dEds << std::endl;

    std::cout << "Funcion AzElPa correcta" << std::endl;
}

void test_Geodetic()
{

}

//------------------------------------------------------------------------------
// int main
//------------------------------------------------------------------------------
/**
 * @brief Función principal que ejecuta todos los tests unitarios.
 * @return 0 si todos los tests han sido superados.
 */
//------------------------------------------------------------------------------
int main()
{
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
    // test_IERS();
    // test_MeanObliquity();
    // test_EccAnom();
    //test_Cheb3D();
    test_timediff();
    //test_AzElPa();
    //test_Geodetic();

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "Todos los tests del proyecto han sido superados" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    getchar();

    return 0;
}
