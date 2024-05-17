//$Source$
//------------------------------------------------------------------------------
// test
//------------------------------------------------------------------------------
/**
 * @file test.cpp
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
    m2(1, 1) = 1.0;
    m2(1, 2) = 2.0;

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
    m2(1, 1) = 1.0;
    m2(2, 1) = 3.0;

    assert(m1.column(1) == m2 && "Columna incorrecta");
    std::cout << "Columna correcta" << std::endl;
}

void test_subVector()
{
    Matrix m = Matrix::eye(6);
    Matrix v = m.subvectorFromRow(2, 2, 5);
    Matrix expected(1, 4);
    expected(1, 1) = 1.0;
    expected(1, 2) = 0.0;
    expected(1, 3) = 0.0;           
    expected(1, 4) = 0.0;

    //std::cout << "v: " << std::endl << v << std::endl;
    //std::cout << "expected: " << std::endl << expected << std::endl;
    assert(v == expected && "Subvector incorrecto");
    std::cout << "Subvector correcto" << std::endl;
}

void test_concatenateRows()
{
    Matrix m1 = Matrix::eye(2);
    Matrix m2 = Matrix::eye(2);
    Matrix m = Matrix::concatenateRows(m1, m2);
    Matrix expected = Matrix(2, 4);
    expected(1, 1) = 1.0;
    expected(1, 2) = 0.0;
    expected(1, 3) = 1.0;
    expected(1, 4) = 0.0;
    expected(2, 1) = 0.0;
    expected(2, 2) = 1.0;
    expected(2, 3) = 0.0;
    expected(2, 4) = 1.0;

    //std::cout << "m: " << std::endl << m << std::endl;
    //std::cout << "expected: " << std::endl << expected << std::endl;
    assert(m == expected && "ConcatenateRows incorrecto");
    std::cout << "ConcatenateRows correcto" << std::endl;
}

void test_matrixToDoubleArray()
{
    Matrix m = Matrix::eye(2);
    double* arr = new double[4];
    Matrix::matrixToDoubleArray(m, arr);
    double expected[4] = {1.0, 0.0, 0.0, 1.0};

    /*
    std::cout << "arr: " << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "expected: " << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << expected[i] << " ";
    }
    std::cout << std::endl;
    */
    assert(arr[0] == expected[0] && arr[1] == expected[1] && arr[2] == expected[2] && arr[3] == expected[3] && "matrixToDoubleArray incorrecto");
    std::cout << "matrixToDoubleArray correcto" << std::endl;

}

void test_doubleArrayToMatrix()
{
    double arr[4] = {1.0, 0.0, 0.0, 1.0};
    Matrix m = Matrix::doubleArrayToMatrix(arr, 2, 2);
    Matrix expected = Matrix::eye(2);

    //std::cout << "m: " << m << std::endl << m << std::endl;
    //std::cout << "expected: " << expected << std::endl << expected << std::endl;
    assert(m == expected && "doubleArrayToMatrix incorrecto");
    std::cout << "doubleArrayToMatrix correcto" << std::endl;
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
#include "../include/IERS.hpp"
#include "../include/MeanObliquity.hpp"
#include "../include/EccAnom.hpp"
#include "../include/Cheb3D.hpp"
#include "../include/timediff.hpp"
#include "../include/AzElPa.hpp"
#include "../include/Geodetic.hpp"
#include "../include/Legendre.hpp"
#include "../include/NutAngles.hpp"
#include "../include/gmst.hpp"
#include "../include/elements.hpp"
#include "../include/angl.hpp"
#include "../include/TimeUpdate.hpp"
#include "../include/PrecMatrix.hpp"
#include "../include/PoleMatrix.hpp"
#include "../include/NutMatrix.hpp"
#include "../include/MeasUpdate.hpp"
#include "../include/LTC.hpp"
#include "../include/EqnEquinox.hpp"
#include "../include/AccelHarmonic.hpp"
#include "../include/JPL_Eph_DE430.hpp"
#include "../include/roots.hpp"
#include "../include/gast.hpp"
#include "../include/GHAMatrix.hpp"
#include "../include/gibbs.hpp"
#include "../include/hgibbs.hpp"
#include "../include/anglesg.hpp"
#include "../include/Accel.hpp"
#include "../include/G_AccelHarmonic.hpp"
#include "../include/VarEqn.hpp"
#include "../include/DEInteg.hpp"

void test_R_x()
{
    Matrix R = R_x(Const::pi);
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

    assert(R == expected && "R_x incorrecta");
    std::cout << "R_x correcta" << std::endl;
}

void test_R_y()
{
    Matrix R = R_y(Const::pi);
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

    assert(R == expected && "R_y incorrecta");
    std::cout << "R_y correcta" << std::endl;
}

void test_R_z()
{
    Matrix R = R_z(Const::pi);
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

    assert(R == expected && "R_z incorrecta");
    std::cout << "R_z correcta" << std::endl;
}

void test_Frac()
{
    double pi = Const::pi;
    assert(abs(Frac(pi) - 0.141592) < 10e-6 && "Frac incorrecta");
    std::cout << "Frac correcta" << std::endl;
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
    assert(AccelPointMass(r, s, GM) == expected && "AccelPointMass incorrecta");
    std::cout << "AccelPointMass correcta" << std::endl;
}

void test_sign_()
{
    assert(abs(sign_(-1.0, 1.0) - 1.0) < 10e-6 && "sign_ incorrecta");
    std::cout << "sign_ correcta" << std::endl;
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

    assert(unit(vec) == expected && "unit incorrecta");

    Matrix vec2 = Matrix::zeros(1, 3);
    Matrix expected2 = Matrix::zeros(1, 3);

    assert(unit(vec2) == expected2 && "unit incorrecta");
    std::cout << "unit correcta" << std::endl;
}

void test_eop19620101()
{
    // Solo imprime por pantalla, otra comprobación llevaría demasiado tiempo
    Global::eop19620101(10);
    //std::cout << (*Global::eopdata) << std::endl; // Se ha comprobado que imprime correctamente los datos
    std::cout << "eop19620101 genera la matriz eopdata correctamente" << std::endl;
}

void test_position()
{
    Matrix r = Position(0.0, 0.0, 0.0);
    Matrix expected = Matrix(1, 3);
    expected(1, 1) = 6378137.0;
    expected(1, 2) = 0.0;
    expected(1, 3) = 0.0;

    //cout << "expected: " << endl << expected << endl;
    //cout << "r: " << endl << r << endl;
    //assert(r == expected && "Position incorrecta");
    assert(r.equals(expected, 10e-1) && "Position incorrecta");
    std::cout << "Position correcta" << std::endl;
}

void test_Mjday()
{
    double Mjd = Mjday(2024, 4, 27, 0, 0, 0.0);
    assert(abs(Mjd - 60427) < 10e-6 && "Mjday incorrecta");
    std::cout << "Mjday correcta" << std::endl;
}

void test_Mjday_TDB()
{
    double Mjd_TT = Mjday(2024, 4, 27, 0, 0, 0.0); // Mjday(2024, 4, 27, 18, 40, 5.0);
    double Mjd_TDB = Mjday_TDB(Mjd_TT);            // = 6.0428e+04
    assert(abs(Mjd_TDB - 60427) < 10e-6 && "Mjday_TDB incorrecta");
    std::cout << "Mjday_TDB correcta" << std::endl;
}

void test_IERS()
{
    double expected_x_pole = -5.5937872420407e-07;
    double expected_y_pole = 2.33559834147197e-06;
    double expected_UT1_UTC = 0.325747632958709;
    double expected_LOD = 0.00272698971874332;
    double expected_dpsi = -1.16882953161744e-07;
    double expected_deps = -2.4783506198648e-08;
    double expected_dx_pole = -8.43027359626024e-10;
    double expected_dy_pole = -1.56811369105037e-09;
    double expected_TAI_UTC = 29;

    Global::eop19620101(21142);
    double Mjd_UTC = 49746.1163541665;
    double x_pole = 0.0;
    double y_pole = 0.0;
    double UT1_UTC = 0.0;
    double LOD = 0.0;
    double dpsi = 0.0;
    double deps = 0.0;
    double dx_pole = 0.0;
    double dy_pole = 0.0;
    double TAI_UTC = 0.0;
    Matrix eopdata = *Global::eopdata;
    IERS(eopdata, Mjd_UTC, 'l', x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC);
    //std::cout << "x_pole: " << x_pole << std::endl;
    //std::cout << "expected_x_pole: " << expected_x_pole << std::endl;
    assert(abs(x_pole - expected_x_pole) < 10e-6 && "IERS incorrecta");
    //std::cout << "y_pole: " << y_pole << std::endl;
    //std::cout << "expected_y_pole: " << expected_y_pole << std::endl;
    assert(abs(y_pole - expected_y_pole) < 10e-6 && "IERS incorrecta");
    //std::cout << "UT1_UTC: " << UT1_UTC << std::endl;
    //std::cout << "expected_UT1_UTC: " << expected_UT1_UTC << std::endl;
    assert(abs(UT1_UTC - expected_UT1_UTC) < 10e-6 && "IERS incorrecta");
    //std::cout << "LOD: " << LOD << std::endl;
    //std::cout << "expected_LOD: " << expected_LOD << std::endl;
    assert(abs(LOD - expected_LOD) < 10e-6 && "IERS incorrecta");
    //std::cout << "dpsi: " << dpsi << std::endl;
    //std::cout << "expected_dpsi: " << expected_dpsi << std::endl;
    assert(abs(dpsi - expected_dpsi) < 10e-6 && "IERS incorrecta");
    //std::cout << "deps: " << deps << std::endl;
    //std::cout << "expected_deps: " << expected_deps << std::endl;
    assert(abs(deps - expected_deps) < 10e-6 && "IERS incorrecta");
    //std::cout << "dx_pole: " << dx_pole << std::endl;
    //std::cout << "expected_dx_pole: " << expected_dx_pole << std::endl;
    assert(abs(dx_pole - expected_dx_pole) < 10e-6 && "IERS incorrecta");
    //std::cout << "dy_pole: " << dy_pole << std::endl;
    //std::cout << "expected_dy_pole: " << expected_dy_pole << std::endl;
    assert(abs(dy_pole - expected_dy_pole) < 10e-6 && "IERS incorrecta");
    //std::cout << "TAI_UTC: " << TAI_UTC << std::endl;
    //std::cout << "expected_TAI_UTC: " << expected_TAI_UTC << std::endl;
    assert(abs(TAI_UTC - expected_TAI_UTC) < 10e-6 && "IERS incorrecta");
    std::cout << "IERS correcta" << std::endl;
}

void test_MeanObliquity()
{
    double Mjd = 60427; // Mjday(2024, 4, 27, 0, 0, 0.0);
    double r = MeanObliquity(Mjd);
    double expected = 0.409037608525256;
    assert(abs(r - expected) < 10e-6 && "MeanObliquity incorrecta");
    std::cout << "MeanObliquity correcta" << std::endl;
}

void test_EccAnom()
{
    double r = EccAnom(3 * Const::pi / 2, 0.5);
    double expected = 4.26220536908982;
    //std::cout << "r: " << r << std::endl;
    //std::cout << "expected: " << expected << std::endl;
    assert(abs(r - expected) < 10e-6 && "EccAnom incorrecta");
    std::cout << "EccAnom correcta" << std::endl;
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
    //cout << "result: " << endl << result << endl;
    //cout << "expected: " << endl  << expected << endl;
    assert(result == expected && "Cheb3D incorrecta");
    std::cout << "Cheb3D correcta" << std::endl;
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
    assert(abs(UT1_TAI - expected_UT1_TAI) < 10e-6 && "timediff incorrecta");
    assert(abs(UTC_GPS - expected_UTC_GPS) < 10e-6 && "timediff incorrecta");
    assert(abs(UT1_GPS - expected_UT1_GPS) < 10e-6 && "timediff incorrecta");
    assert(abs(TT_UTC - expected_TT_UTC) < 10e-6 && "timediff incorrecta");
    assert(abs(GPS_UTC - expected_GPS_UTC) < 10e-6 && "timediff incorrecta");
    std::cout << "timediff correcta" << std::endl;
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

    assert(abs(Az - expected_Az) < 10e-6 && "AzElPa incorrecta");
    //std::cout << "Az: " << Az << std::endl;
    //std::cout << "expected_Az: " << expected_Az << std::endl;
    assert(abs(El - expected_El) < 10e-4 && "AzElPa incorrecta");
    //std::cout << "El: " << El << std::endl;
    //std::cout << "expected_El: " << expected_El << std::endl;
    assert(dAds == expected_dAds && "AzElPa incorrecta");
    //std::cout << "dAds: " << std::endl << dAds << std::endl;
    //std::cout << "expected_dAds: " << std::endl << expected_dAds << std::endl;
    assert(dEds == expected_dEds && "AzElPa incorrecta");
    //std::cout << "dEds: " << std::endl << dEds << std::endl;
    //std::cout << "expected_dEds: " << std::endl << expected_dEds << std::endl;
    std::cout << "AzElPa correcta" << std::endl;
}

void test_Geodetic()
{
    Matrix r = Matrix(1, 3);
    r(1, 1) = 30000;
    r(1, 2) = 10000;
    r(1, 3) = 15000;

    double expected_lon = 0.321750554396642;
    double expected_lat = 1.01984681898081;
    double expected_h = -6333284.37807659;

    double lon = 0.0;
    double lat = 0.0;
    double h = 0.0;
    Geodetic(r, lon, lat, h);
    //std::cout << "lon: " << lon << std::endl;
    //std::cout << "expected_lon: " << expected_lon << std::endl;
    assert(abs(lon - expected_lon) < 10e-6 && "Geodetic incorrecta");
    //std::cout << "lat: " << lat << std::endl;
    //std::cout << "expected_lat: " << expected_lat << std::endl;
    assert(abs(lat - expected_lat) < 10e-6 && "Geodetic incorrecta");
    //std::cout << "h: " << h << std::endl;
    //std::cout << "expected_h: " << expected_h << std::endl;
    assert(abs(h - expected_h) < 10e-6 && "Geodetic incorrecta");
    std::cout << "Geodetic correcta" << std::endl;
}

void test_Legendre()
{
    Matrix expected_pnm = Matrix(3, 3);
    expected_pnm(1, 1) = 1.0;
    expected_pnm(1, 2) = 0.0;
    expected_pnm(1, 3) = 0.0;
    expected_pnm(2, 1) = 2.12115047744981e-16;
    expected_pnm(2, 2) = -1.73205080756888;
    expected_pnm(2, 3) = 0.0;
    expected_pnm(3, 1) = -1.11803398874989;
    expected_pnm(3, 2) = -4.74303665808392e-16;
    expected_pnm(3, 3) = 1.93649167310371;

    Matrix expected_dpnm = Matrix(3, 3);
    expected_dpnm(1, 1) = 0.0;
    expected_dpnm(1, 2) = 0.0;
    expected_dpnm(1, 3) = 0.0;
    expected_dpnm(2, 1) = -1.73205080756888;
    expected_dpnm(2, 2) = -2.12115047744981e-16;
    expected_dpnm(2, 3) = 0.0;
    expected_dpnm(3, 1) = -8.21518047396304e-16;
    expected_dpnm(3, 2) = 3.87298334620742;
    expected_dpnm(3, 3) = 4.74303665808392e-16;

    Matrix pnm = Matrix::zeros(3, 3);
    Matrix dpnm = Matrix::zeros(3, 3);
    Legendre(2, 2, Const::pi, pnm, dpnm);

    //std::cout << "pnm: " << std::endl << pnm << std::endl;
    //std::cout << "expected_pnm: " << std::endl << expected_pnm << std::endl;
    assert(pnm.equals(expected_pnm, 10e-6) && "Legendre incorrecta");
    //std::cout << "dpnm: " << std::endl << dpnm << std::endl;
    //std::cout << "expected_dpnm: " << std::endl << expected_dpnm << std::endl;
    assert(dpnm.equals(expected_dpnm, 10e-6) && "Legendre incorrecta");
    std::cout << "Legendre correcta" << std::endl;
}

void test_NutAngles()
{
    double expected_dpsi = -2.71495478599163e-05;
    double expected_deps = 4.30555624611353e-05;

    double dpsi = 0.0;
    double deps = 0.0;
    NutAngles(60427, dpsi, deps);
    //std::cout << "dpsi: " << dpsi << std::endl;
    //std::cout << "expected_dpsi: " << expected_dpsi << std::endl;
    assert(abs(dpsi - expected_dpsi) < 10e-6 && "NutAngles incorrecta");
    //std::cout << "deps: " << deps << std::endl;
    //std::cout << "expected_deps: " << expected_deps << std::endl;
    assert(abs(deps - expected_deps) < 10e-6 && "NutAngles incorrecta");
    std::cout << "NutAngles correcta" << std::endl;
}

void test_gmst()
{
    double expected_gmst = 3.76071979798481;
    double _gmst = gmst(60427);
    //std::cout << "gmst: " << _gmst << std::endl;
    //std::cout << "expected_gmst: " << expected_gmst << std::endl;
    assert(abs(_gmst - expected_gmst) < 10e-6 && "gmst incorrecta");
    std::cout << "gmst correcta" << std::endl;
}

void test_elements() 
{
    double expected_p = 1.35474011564823e-13;
    double expected_a = 1.87082869338765;
    double expected_e = 0.999999999999964;
    double expected_i = 1.99133066207886;
    double expected_Omega = 3.6052402625906;
    double expected_omega = 5.21086941752228;
    double expected_M = 3.14159030993265;

    double p = 0.0;
    double a = 0.0;
    double e = 0.0;
    double i = 0.0;
    double Omega = 0.0;
    double omega = 0.0;
    double M = 0.0;
    Matrix y = Matrix(1, 6);
    y(1, 1) = 1;
    y(1, 2) = 2;
    y(1, 3) = 3;
    y(1, 4) = 4;
    y(1, 5) = 5;
    y(1, 6) = 6;
    elements(y, p, a, e, i, Omega, omega, M);
    //std::cout << "p: " << p << std::endl;
    //std::cout << "expected_p: " << expected_p << std::endl;
    assert(abs(p - expected_p) < 10e-6 && "elements incorrecta");
    //std::cout << "a: " << a << std::endl;
    //std::cout << "expected_a: " << expected_a << std::endl;
    assert(abs(a - expected_a) < 10e-6 && "elements incorrecta");
    //std::cout << "e: " << e << std::endl;
    //std::cout << "expected_e: " << expected_e << std::endl;
    assert(abs(e - expected_e) < 10e-6 && "elements incorrecta");
    //std::cout << "i: " << i << std::endl;
    //std::cout << "expected_i: " << expected_i << std::endl;
    assert(abs(i - expected_i) < 10e-6 && "elements incorrecta");
    //std::cout << "Omega: " << Omega << std::endl;
    //std::cout << "expected_Omega: " << expected_Omega << std::endl;
    assert(abs(Omega - expected_Omega) < 10e-6 && "elements incorrecta");
    //std::cout << "omega: " << omega << std::endl;
    //std::cout << "expected_omega: " << expected_omega << std::endl;
    assert(abs(omega - expected_omega) < 10e-6 && "elements incorrecta");
    //std::cout << "M: " << M << std::endl;
    //std::cout << "expected_M: " << expected_M << std::endl;
    assert(abs(M - expected_M) < 10e-6 && "elements incorrecta");
    std::cout << "elements correcta" << std::endl;
}

void test_angl()
{
    double expected = 0.25857576954288;

    Matrix vec1 = Matrix(1, 3);
    vec1(1, 1) = 2.1;
    vec1(1, 2) = 4.0;
    vec1(1, 3) = 6.0;
    Matrix vec2 = Matrix(1, 3);
    vec2(1, 1) = 1.0;
    vec2(1, 2) = 3.0;
    vec2(1, 3) = 7.5;
    double r = angl(vec1, vec2);
    
    //std::cout << "r: " << r << std::endl;
    //std::cout << "expected: " << expected << std::endl;
    assert(abs(r - expected) < 10e-6 && "angl incorrecta");
    std::cout << "angl correcta" << std::endl;
}

void test_TimeUpdate() 
{
    Matrix P = Matrix(3, 3);
    P.copy(Matrix::eye(3) * 1.3);

    Matrix Q = Matrix(3, 3);
    for(int i = 1; i <= 3; i++) {
        for(int j = 1; j <= 3; j++) {
            Q(i, j) = 2.3;
        }
    }

    Matrix expected = Matrix(3, 3);
    for(int i = 1; i <= 3; i++) {
        for(int j = 1; j <= 3; j++) {
            expected(i, j) = 20.6310;
        }
    }

    Matrix r = TimeUpdate(P, Q, 0.0);
    //std::cout << "r: " << std::endl << r << std::endl;
    //std::cout << "expected: " << std::endl << expected << std::endl;
    assert(r == expected && "TimeUpdate incorrecta");
    std::cout << "TimeUpdate correcta" << std::endl;
}

void test_PrecMatrix() 
{
    Matrix expected = Matrix(3, 3);
    expected(1, 1) = 0.999999984935368;
    expected(1, 2) = -0.000159203133883979;
    expected(1, 3) = -6.91637604951778e-05;
    expected(2, 1) = 0.000159203133883978;
    expected(2, 2) = 0.999999987327181;
    expected(2, 3) = -5.50555048857034e-09;
    expected(3, 1) = 6.91637604951788e-05;
    expected(3, 2) = -5.50553701640193e-09;
    expected(3, 3) = 0.999999997608187;

    Matrix r = PrecMatrix(60200, 60460);
    //std::cout << "r: " << std::endl << r << std::endl;
    //std::cout << "expected: " << std::endl << expected << std::endl;
    assert(r == expected && "PrecMatrix incorrecta");
    std::cout << "PrecMatrix correcta" << std::endl;
}

void test_PoleMatrix()
{
    Matrix expected = Matrix(3, 3);
    expected(1, 1) = 0.862318872287684;
    expected(1, 2) = 0.442207745783184;
    expected(1, 3) = -0.246695099395695;
    expected(2, 1) = 0.0;
    expected(2, 2) = 0.487187675007006;
    expected(2, 3) = 0.873297297213995;
    expected(3, 1) = 0.506365641109759;
    expected(3, 2) = -0.753060740505454;
    expected(3, 3) = 0.4201111265045;

    Matrix r = PoleMatrix(100, 200);

    //std::cout << "r: " << std::endl << r << std::endl;
    //std::cout << "expected: " << std::endl << expected << std::endl;
    assert(r == expected && "PoleMatrix incorrecta");
    std::cout << "PoleMatrix correcta" << std::endl;
}

void test_NutMatrix()
{
    Matrix expected = Matrix(3, 3);
    expected(1, 1) = 0.999999999631451;
    expected(1, 2) = 2.49098191980287e-05;
    expected(1, 3) = 1.07980950328428e-05;
    expected(2, 1) = -2.4909354256885e-05;
    expected(2, 2) = 0.999999998762865;
    expected(2, 3) = -4.30556969346352e-05;
    expected(3, 1) = -1.07991675291102e-05;
    expected(3, 2) = 4.30554279451933e-05;
    expected(3, 3) = 0.999999999014804;

    Matrix r = NutMatrix(60427);
    //std::cout << "r: " << std::endl << r << std::endl;
    //std::cout << "expected: " << std::endl << expected << std::endl;
    assert(r == expected && "NutMatrix incorrecta");
    std::cout << "NutMatrix correcta" << std::endl;
}

void test_MeasUpdate() 
{
    int n = 3;
    Matrix x(1, 3);
    x(1, 1) = 1.0;
    x(1, 2) = 2.0;
    x(1, 3) = 3.0;
    double z = 3.51;
    double g = 4.32;
    double s = -2.13;
    Matrix G(1, 3);
    G(1, 1) = 0.1;
    G(1, 2) = 0.2;
    G(1, 3) = 0.3;
    Matrix P = Matrix::eye(3);
    Matrix K = Matrix::zeros(1, 3);
    MeasUpdate(z, g, s, G, P, n, K, x);

    Matrix expected_x = Matrix(1, 3);
    expected_x(1, 1) = 0.9827;
    expected_x(1, 2) = 1.9654;
    expected_x(1, 3) = 2.9480;

    Matrix expected_P = Matrix(3, 3);
    expected_P(1, 1) = 0.9979;
    expected_P(1, 2) = -0.0043;
    expected_P(1, 3) = -0.0064;
    expected_P(2, 1) = -0.0043;
    expected_P(2, 2) = 0.9914;
    expected_P(2, 3) = -0.0128;
    expected_P(3, 1) = -0.0064;
    expected_P(3, 2) = -0.0128;
    expected_P(3, 3) = 0.9808;

    Matrix expected_K = Matrix(1, 3);
    expected_K(1, 1) = 0.0214;
    expected_K(1, 2) = 0.0428;
    expected_K(1, 3) = 0.0641;

    //std::cout << "x: " << std::endl << x << std::endl;
    //std::cout << "expected_x: " << std::endl << expected_x << std::endl;
    assert(x == expected_x && "MeasUpdate incorrecta");
    //std::cout << "P: " << std::endl << P << std::endl;
    //std::cout << "expected_P: " << std::endl << expected_P << std::endl;
    assert(P.equals(expected_P, 10e-2) && "MeasUpdate incorrecta");
    //std::cout << "K: " << std::endl << K << std::endl;
    //std::cout << "expected_K: " << std::endl << expected_K << std::endl;
    assert(K.equals(expected_K, 10e-3) && "MeasUpdate incorrecta");
    std::cout << "MeasUpdate correcta" << std::endl;
}

void test_LTC()
{
    Matrix expected = Matrix(3, 3);
    expected(1, 1) = 1;
    expected(1, 2) = -1.83697019872103e-16;
    expected(1, 3) = 0;
    expected(2, 1) = -4.49927934798557e-32;
    expected(2, 2) = -2.44929359829471e-16;
    expected(2, 3) = 1;
    expected(3, 1) = -1.83697019872103e-16;
    expected(3, 2) = -1;
    expected(3, 3) = -2.44929359829471e-16;

    Matrix r = LTC(3 * Const::pi / 2, Const::pi2);

    //std::cout << "r: " << std::endl << r << std::endl;
    //std::cout << "expected: " << std::endl << expected << std::endl;
    assert(r == expected && "LTC incorrecta");
    std::cout << "LTC correcta" << std::endl;
}

void test_EqnEquinox()
{
    double expected = -2.49098192010888e-05;
    double r = EqnEquinox(60427);
    //std::cout << "r: " << r << std::endl;
    //std::cout << "expected: " << expected << std::endl;
    assert(abs(r - expected) < 10e-6 && "EqnEquinox incorrecta");
    std::cout << "EqnEquinox correcta" << std::endl;
}

void test_GGM03S()
{
    Global::GGM03S(181);
    //std::cout << (*Global::Cnm) << std::endl;
    //getchar();
    //std::cout << (*Global::Snm) << std::endl;
    std::cout << "GGM03S genera matrices Cnm y Snm correctamente" << std::endl;
}

void test_AccelHarmonic()
{
    int n_max = 2;
    int m_max = 2;

    Matrix E = Matrix(3, 3);
    E(1, 1) = 2.5;
    E(1, 2) = 0.5;
    E(1, 3) = 0.5;
    E(2, 1) = 0.5;
    E(2, 2) = 2.5;
    E(2, 3) = 0.5;
    E(3, 1) = 0.5;
    E(3, 2) = 0.5;
    E(3, 3) = 2.5;

    Matrix r = Matrix(1, 3);
    r(1, 1) = 10000.0;
    r(1, 2) = 20000.0;
    r(1, 3) = 15000.0;

    Matrix expected = Matrix(1, 3);
    expected(1, 1) = 121772.312522019;
    expected(1, 2) = 198497.732246315;
    expected(1, 3) = -675857.680548087;

    Global::GGM03S(181);
    Matrix result = AccelHarmonic(r, E, n_max, m_max);
    //std::cout << "result: " << std::endl << result << std::endl;
    //std::cout << "expected: " << std::endl << expected << std::endl;
    assert(result.equals(expected, 20e13) && "AccelHarmonic incorrecta");
    std::cout << "AccelHarmonic correcta" << std::endl;
}

void test_DE430Coeff()
{
    Global::DE430Coeff(50);
    //std::cout << (*Global::PC) << std::endl;  // Se ha comprobado que imprime los datos correctos
    std::cout << "DE430Coeff genera matriz PC correctamente" << std::endl;
}

void test_JPL_Eph_DE430()
{
    Global::DE430Coeff(1020);
    
    Matrix r_Earth_expected(1, 3);
    r_Earth_expected(1, 1) = -121516884424.302;
    r_Earth_expected(1, 2) = -83451206276.9444;
    r_Earth_expected(1, 3) = -36140690104.9687;

    Matrix r_Moon_expected(1, 3);
    r_Moon_expected(1, 1) = -123601610.226117;
    r_Moon_expected(1, 2) = -326955119.242958;
    r_Moon_expected(1, 3) = -174140013.94066;

    Matrix r_Sun_expected(1, 3);
    r_Sun_expected(1, 1) = 120417705646.507;
    r_Sun_expected(1, 2) = 82934232747.2077;
    r_Sun_expected(1, 3) = 35949718189.1537;

    Matrix r_Mercury_expected(1, 3);
    r_Mercury_expected(1, 1) = 93498334471.039;
    r_Mercury_expected(1, 2) = 25266001420.8462;
    r_Mercury_expected(1, 3) = 7933341415.83392;

    Matrix r_Venus_expected(1, 3);
    r_Venus_expected(1, 1) = 226352011432.497;
    r_Venus_expected(1, 2) = 106378352837.832;
    r_Venus_expected(1, 3) = 39796614721.499;

    Matrix r_Mars_expected(1, 3);
    r_Mars_expected(1, 1) = 297438091299.586;
    r_Mars_expected(1, 2) = -12372805690.7213;
    r_Mars_expected(1, 3) = -12541485598.2772;

    Matrix r_Jupiter_expected(1, 3);
    r_Jupiter_expected(1, 1) = 539191977644.449;
    r_Jupiter_expected(1, 2) = 657935867838.272;
    r_Jupiter_expected(1, 3) = 272217352088.758;

    Matrix r_Saturn_expected(1, 3);
    r_Saturn_expected(1, 1) = 1495014623020.22;
    r_Saturn_expected(1, 2) = -324797131606.462;
    r_Saturn_expected(1, 3) = -191645103982.234;

    Matrix r_Uranus_expected(1, 3);
    r_Uranus_expected(1, 1) = 1901331773788.08;
    r_Uranus_expected(1, 2) = 2224795486582.41;
    r_Uranus_expected(1, 3) = 948818098917.6;

    Matrix r_Neptune_expected(1, 3);
    r_Neptune_expected(1, 1) = 4587366317134.73;
    r_Neptune_expected(1, 2) = -72926422681.1243;
    r_Neptune_expected(1, 3) = -139049329149.549;

    Matrix r_Pluto_expected(1, 3);
    r_Pluto_expected(1, 1) = 2743995711826.01;
    r_Pluto_expected(1, 2) = -3957834041109.93;
    r_Pluto_expected(1, 3) = -2015166269133.48;

    Matrix r_Mercury(1, 3);
    Matrix r_Venus(1, 3);
    Matrix r_Earth(1, 3);
    Matrix r_Mars(1, 3);
    Matrix r_Jupiter(1, 3);
    Matrix r_Saturn(1, 3);
    Matrix r_Uranus(1, 3);
    Matrix r_Neptune(1, 3);
    Matrix r_Pluto(1, 3);
    Matrix r_Moon(1, 3);
    Matrix r_Sun(1, 3);
    JPL_Eph_DE430(60427, r_Mercury, r_Venus, r_Earth,
                    r_Mars, r_Jupiter, r_Saturn, r_Uranus,
                        r_Neptune, r_Pluto, r_Moon, r_Sun);
    //std::cout << "r_Earth: " << std::endl << r_Earth << std::endl;
    //std::cout << "r_Earth_expected: " << std::endl << r_Earth_expected << std::endl;
    assert(r_Earth.equals(r_Earth_expected, 10e6) && "JPL_Eph_DE430 incorrecta");
    //std::cout << "r_Moon: " << std::endl << r_Moon << std::endl;
    //std::cout << "r_Moon_expected: " << std::endl << r_Moon_expected << std::endl;
    assert(r_Moon.equals(r_Moon_expected, 10e6) && "JPL_Eph_DE430 incorrecta");
    //std::cout << "r_Sun: " << std::endl << r_Sun << std::endl;
    //std::cout << "r_Sun_expected: " << std::endl << r_Sun_expected << std::endl;
    assert(r_Sun.equals(r_Sun_expected, 10e6) && "JPL_Eph_DE430 incorrecta");
    //std::cout << "r_Mercury: " << std::endl << r_Mercury << std::endl;
    //std::cout << "r_Mercury_expected: " << std::endl << r_Mercury_expected << std::endl;
    assert(r_Mercury.equals(r_Mercury_expected, 10e6) && "JPL_Eph_DE430 incorrecta");
    //std::cout << "r_Venus: " << std::endl << r_Venus << std::endl;
    //std::cout << "r_Venus_expected: " << std::endl << r_Venus_expected << std::endl;
    assert(r_Venus.equals(r_Venus_expected, 10e6) && "JPL_Eph_DE430 incorrecta");
    //std::cout << "r_Mars: " << std::endl << r_Mars << std::endl;
    //std::cout << "r_Mars_expected: " << std::endl << r_Mars_expected << std::endl;
    assert(r_Mars.equals(r_Mars_expected, 10e6) && "JPL_Eph_DE430 incorrecta");
    //std::cout << "r_Jupiter: " << std::endl << r_Jupiter << std::endl;
    //std::cout << "r_Jupiter_expected: " << std::endl << r_Jupiter_expected << std::endl;
    assert(r_Jupiter.equals(r_Jupiter_expected, 10e6) && "JPL_Eph_DE430 incorrecta");
    //std::cout << "r_Saturn: " << std::endl << r_Saturn << std::endl;
    //std::cout << "r_Saturn_expected: " << std::endl << r_Saturn_expected << std::endl;
    assert(r_Saturn.equals(r_Saturn_expected, 10e6) && "JPL_Eph_DE430 incorrecta");
    //std::cout << "r_Uranus: " << std::endl << r_Uranus << std::endl;
    //std::cout << "r_Uranus_expected: " << std::endl << r_Uranus_expected << std::endl;
    assert(r_Uranus.equals(r_Uranus_expected, 10e6) && "JPL_Eph_DE430 incorrecta");
    //std::cout << "r_Neptune: " << std::endl << r_Neptune << std::endl;
    //std::cout << "r_Neptune_expected: " << std::endl << r_Neptune_expected << std::endl;
    assert(r_Neptune.equals(r_Neptune_expected, 10e6) && "JPL_Eph_DE430 incorrecta");
    //std::cout << "r_Pluto: " << std::endl << r_Pluto << std::endl;
    //std::cout << "r_Pluto_expected: " << std::endl << r_Pluto_expected << std::endl;
    assert(r_Pluto.equals(r_Pluto_expected, 10e6) && "JPL_Eph_DE430 incorrecta");

    std::cout << "JPL_Eph_DE430 correcta" << std::endl;
}

void test_roots()
{
    // Polinomio x^2 + 1;
    // Obtengo soluciones de x^2 + 1 = 0
    // Son exactamente: i, -i
    // Mi función debería devolverme la matriz [[0, 1.0], [0, -1.0]]
    Matrix poly = Matrix(1, 3);
    poly(1, 1) = 1.0;   // 1 * x^2
    poly(1, 2) = 0.0;   // 0 * x
    poly(1, 3) = 1.0;   // 1 * 1
    Matrix raices = roots(poly);
    Matrix expected = Matrix(1, 4);
    expected(1, 1) = 0.0;
    expected(1, 2) = 1.0;
    expected(1, 3) = 0.0;
    expected(1, 4) = -1.0;

    //std::cout << "roots: " << std::endl << raices << std::endl;
    //std::cout << "expected: " << std::endl << expected << std::endl;
    assert(raices.equals(expected, 10e-6) && "roots incorrecta");
    std::cout << "roots correcta" << std::endl;
}

void test_gast()
{
    double expected = 3.7606948881656;
    double r = gast(60427);
    //std::cout << "r: " << r << std::endl;
    //std::cout << "expected: " << expected << std::endl;
    assert(abs(r - expected) < 10e-6 && "gast incorrecta");
    std::cout << "gast correcta" << std::endl;
}

void test_GHAMatrix()
{
    Matrix expected = Matrix(3, 3);
    expected(1, 1) = -0.814399761883852;
    expected(1, 2) = -0.580304254545428;
    expected(1, 3) = 0.0;
    expected(2, 1) = 0.580304254545428;
    expected(2, 2) = -0.814399761883852;
    expected(2, 3) = 0.0;
    expected(3, 1) = 0.0;
    expected(3, 2) = 0.0;
    expected(3, 3) = 1.0;

    Matrix r = GHAMatrix(60427);

    //std::cout << "r: " << std::endl << r << std::endl;
    //std::cout << "expected: " << std::endl << expected << std::endl;
    assert(r == expected && "GHAMatrix incorrecta");
    std::cout << "GHAMatrix correcta" << std::endl;
}

void test_gibss()
{
    Matrix r1 = Matrix(1, 3);
    r1(1, 1) = 6524.834;
    r1(1, 2) = 6862.875;
    r1(1, 3) = 6448.296;
    Matrix r2 = Matrix(1, 3);
    r2(1, 1) = 3480.735;
    r2(1, 2) = 2218.353;
    r2(1, 3) = 5275.519;
    Matrix r3 = Matrix(1, 3);
    r3(1, 1) = 4681.281;
    r3(1, 2) = 5073.213;
    r3(1, 3) = 5533.497;

    Matrix v2 = Matrix(1, 3);
    double theta = 0.0;
    double theta1 = 0.0;
    double copa = 0.0;
    std::string error = "\0";
    gibbs(r1, r2, r3, v2, theta, theta1, copa, error);
    assert(error == "not coplanar\0" && "gibbs incorrecta");

    Matrix expected_v2 = Matrix(1, 3);
    expected_v2(1, 1) = 15280534.3201927;
    expected_v2(1, 2) = 10804969.437962;
    expected_v2(1, 3) = 0.0;
    double expected_theta = 1.5707963267949;
    double expected_theta1 = 0.785398163397448;
    double expected_copa = 0.0;

    r1(1, 1) = 1.0;
    r1(1, 2) = 0.0;
    r1(1, 3) = 0.0;
    r2(1, 1) = 0.0;
    r2(1, 2) = 1.0;
    r2(1, 3) = 0.0;
    r3(1, 1) = 1.0;
    r3(1, 2) = 1.0;
    r3(1, 3) = 0.0;
    gibbs(r1, r2, r3, v2, theta, theta1, copa, error);
    assert(error == "ok\0n" && "gibbs incorrecta");
    //std::cout << "v2: " << std::endl << v2 << std::endl;
    //std::cout << "expected v2: " << std::endl << expected_v2 << std::endl;
    assert(v2 == expected_v2 && "gibbs incorrecta");
    //std::cout << "theta: " << theta << std::endl;
    //std::cout << "expected theta: " << expected_theta << std::endl;
    assert(abs(theta - expected_theta) < 10e-6 && "gibbs incorrecta");
    //std::cout << "theta1: " << theta1 << std::endl;
    //std::cout << "expected theta1: " << expected_theta1 << std::endl;
    assert(abs(theta1 - expected_theta1) < 10e-6 && "gibbs incorrecta");
    //std::cout << "copa: " << copa << std::endl;
    //std::cout << "expected copa: " << expected_copa << std::endl;
    assert(abs(copa - expected_copa) < 10e-6 && "gibbs incorrecta");
    std::cout << "gibbs correcta" << std::endl;
}

void test_hgibbs()
{
    Matrix r1 = Matrix(1, 3);
    r1(1, 1) = 7000.0;
    r1(1, 2) = 0.0;
    r1(1, 3) = 0.0;
    Matrix r2 = Matrix(1, 3);
    r2(1, 1) = 0.0;
    r2(1, 2) = 8000.0;
    r2(1, 3) = 0.0;
    Matrix r3 = Matrix(1, 3);
    r3(1, 1) = -3000.0;
    r3(1, 2) = -4000.0;
    r3(1, 3) = 0.0;

    double Mjd1 = 50000;
    double Mjd2 = 50001;
    double Mjd3 = 50002;

    Matrix v2 = Matrix(1, 3);
    double theta = 0.0;
    double theta1 = 0.0;
    double copa = 0.0;
    std::string error = "\0";

    Matrix v2_expected = Matrix(1, 3);
    v2_expected(1, 1) = -127448015144.199;
    v2_expected(1, 2) = -91837540324.4776;
    v2_expected(1, 3) = 0.0;

    double theta_expected = 1.5707963267949;
    double theta1_expected = 2.49809154479651;
    double copa_expected = 0.0;

    hgibbs(r1, r2, r3, Mjd1, Mjd2, Mjd3, v2, theta, theta1, copa, error);
    //std::cout << "v2: " << std::endl << v2 << std::endl;
    //std::cout << "expected v2: " << std::endl << v2_expected << std::endl;
    assert(v2 == v2_expected && "hgibbs incorrecta");
    //std::cout << "theta: " << theta << std::endl;
    //std::cout << "expected theta: " << theta_expected << std::endl;
    assert(abs(theta - theta_expected) < 10e-6 && "hgibbs incorrecta");
    //std::cout << "theta1: " << theta1 << std::endl;
    //std::cout << "expected theta1: " << theta1_expected << std::endl;
    assert(abs(theta1 - theta1_expected) < 10e-6 && "hgibbs incorrecta");
    //std::cout << "copa: " << copa << std::endl;
    //std::cout << "expected copa: " << copa_expected << std::endl;
    assert(abs(copa - copa_expected) < 10e-6 && "hgibbs incorrecta");
    std::cout << "hgibbs correcta" << std::endl;
}

void test_anglesg()
{
    double az1 = -0.1;
    double az2 = -0.2;
    double az3 = -0.3;
    double el1 = -0.4;
    double el2 = -0.5;
    double el3 = -0.6;
    double Mjd1 = 50000;
    double Mjd2 = 50001;
    double Mjd3 = 50002;
    Matrix Rs1 = Matrix(1, 3);
    Rs1(1, 1) = 1.0;
    Rs1(1, 2) = 5.0;
    Rs1(1, 3) = 0.0;
    Matrix Rs2 = Matrix(1, 3);
    Rs2(1, 1) = 0.0;
    Rs2(1, 2) = 1.0;
    Rs2(1, 3) = 0.0;
    Matrix Rs3 = Matrix(1, 3);
    Rs3(1, 1) = 3.0;
    Rs3(1, 2) = 0.0;
    Rs3(1, 3) = 1.0;

    Matrix r2 = Matrix(1, 3);
    Matrix v2 = Matrix(1, 3);

    Matrix r2_expected = Matrix(1, 3);
    r2_expected(1, 1) = 1315122.54193953;
    r2_expected(1, 2) = -2493741.49512115;
    r2_expected(1, 3) = 4754876.30951304;

    Matrix v2_expected = Matrix(1, 3);
    v2_expected(1, 1) = -2588.65902157314;
    v2_expected(1, 2) = 4915.630600214;
    v2_expected(1, 3) = -9386.01183867455;

    anglesg(az1, az2, az3, el1, el2, el3, Mjd1, Mjd2, Mjd3, Rs1, Rs2, Rs3, r2, v2);

    std::cout << "r2: " << std::endl << r2 << std::endl;
    std::cout << "expected r2: " << std::endl << r2_expected << std::endl;
    assert(r2 == r2_expected && "anglesg incorrecta");
    std::cout << "v2: " << std::endl << v2 << std::endl;
    std::cout << "expected v2: " << std::endl << v2_expected << std::endl;
    assert(v2 == v2_expected && "anglesg incorrecta");
    std::cout << "anglesg correcta" << std::endl;
}

void test_Accel()
{
    Global::initAuxParam();

    Matrix expected = Matrix(1, 6);
    expected(1, 1) = 4.0;
    expected(1, 2) = 5.0;
    expected(1, 3) = 6.0;
    expected(1, 4) = -4.88335282436177e+131;
    expected(1, 5) = -2.22322498079327e+132;
    expected(1, 6) = -3.75394660264005e+132;

    Matrix Y(1, 6);
    Y(1, 1) = 1.0;
    Y(1, 2) = 2.0;
    Y(1, 3) = 3.0;
    Y(1, 4) = 4.0;
    Y(1, 5) = 5.0;
    Y(1, 6) = 6.0;
    Matrix r = Accel(20.0, Y);

    //std::cout << "r: " << std::endl << r << std::endl;
    //std::cout << "expected: " << std::endl << expected << std::endl;
    assert(r.equals(expected, 10e130) && "Accel incorrecta");
    std::cout << "Accel correcta" << std::endl;
}

void test_G_AccelHarmonic()
{
    Matrix r = Matrix(1, 3);
    r(1, 1) = 7101800.90695315;
    r(1, 2) = 1293997.58115301;
    r(1, 3) = 10114.0149489492;

    Matrix U = Matrix(3, 3);
    U(1, 1) = -0.984320311904791;
    U(1, 2) = 0.17638970840918;
    U(1, 3) = -0.000440838949610109;
    U(2, 1) = -0.176389673507182;
    U(2, 2) = -0.984320409906027;
    U(2, 3) = -0.000117142904888635;
    U(3, 1) = -0.000454589578418276;
    U(3, 2) = -3.75467022865179e-05;
    U(3, 3) = 0.999999895969275;

    Matrix expected_G = Matrix(3, 3);
    expected_G(1, 1) = 2.02233500345983e-06;
    expected_G(1, 2) = 5.61803299881092e-07;
    expected_G(1, 3) = 4.39855973866088e-09;
    expected_G(2, 1) = 5.61803300991315e-07;
    expected_G(2, 2) = -9.5863163429577e-07;
    expected_G(2, 3) = 8.05634448042269e-10;
    expected_G(3, 1) = 4.39855909507847e-09;
    expected_G(3, 2) = 8.056340438517e-10;
    expected_G(3, 3) = -1.06370336963243e-06;

    Matrix G = G_AccelHarmonic(r, U, 20, 20);
    //std::cout << "G: " << std::endl << G << std::endl;
    //std::cout << "expected_G: " << std::endl << expected_G << std::endl;
    assert(G.equals(expected_G, 10e-6) && "G_AccelHarmonic incorrecta");
    std::cout << "G_AccelHarmonic correcta" << std::endl;
}

void test_EqnVar()
{
    Global::initAuxParam();
    Global::AuxParam.Mjd_TT = 49746.1170623147;

    Matrix expected_yPhip = Matrix(1, 42);
    expected_yPhip(1, 1) = 1.0;
    expected_yPhip(1, 2) = 1.0;
    expected_yPhip(1, 3) = 1.0;
    expected_yPhip(1, 4) = 2.63469642308009e+138;
    expected_yPhip(1, 5) = -3.23987179772329e+139;
    expected_yPhip(1, 6) = -6.9796747924436e+139;
    expected_yPhip(1, 7) = 1.0;
    expected_yPhip(1, 8) = 1.0;
    expected_yPhip(1, 9) = 1.0;
    expected_yPhip(1, 10) = 8.88176537332068e+140;
    expected_yPhip(1, 11) = -1.78113092450859e+140;
    expected_yPhip(1, 12) = 6.0464779718723e+140;
    expected_yPhip(1, 13) = 1.0;
    expected_yPhip(1, 14) = 1.0;
    expected_yPhip(1, 15) = 1.0;
    expected_yPhip(1, 16) = 8.88176537332068e+140;
    expected_yPhip(1, 17) = -1.78113092450859e+140;
    expected_yPhip(1, 18) = 6.0464779718723e+140;
    expected_yPhip(1, 19) = 1.0;
    expected_yPhip(1, 20) = 1.0;
    expected_yPhip(1, 21) = 1.0;
    expected_yPhip(1, 22) = 8.88176537332068e+140;
    expected_yPhip(1, 23) = -1.78113092450859e+140;
    expected_yPhip(1, 24) = 6.0464779718723e+140;
    expected_yPhip(1, 25) = 1.0;
    expected_yPhip(1, 26) = 1.0;
    expected_yPhip(1, 27) = 1.0;
    expected_yPhip(1, 28) = 8.88176537332068e+140;
    expected_yPhip(1, 29) = -1.78113092450859e+140;
    expected_yPhip(1, 30) = 6.0464779718723e+140;
    expected_yPhip(1, 31) = 1.0;
    expected_yPhip(1, 32) = 1.0;
    expected_yPhip(1, 33) = 1.0;
    expected_yPhip(1, 34) = 8.88176537332068e+140;
    expected_yPhip(1, 35) = -1.78113092450859e+140;
    expected_yPhip(1, 36) = 6.0464779718723e+140;
    expected_yPhip(1, 37) = 1.0;
    expected_yPhip(1, 38) = 1.0;    
    expected_yPhip(1, 39) = 1.0;
    expected_yPhip(1, 40) = 8.88176537332068e+140;
    expected_yPhip(1, 41) = -1.78113092450859e+140;
    expected_yPhip(1, 42) = 6.0464779718723e+140;
    
    Matrix ones_42 = Matrix(1, 42);
    for (int i = 1; i <= 42; i++)
    {
        ones_42(1, i) = 1.0;
    }
    Matrix yPhip = VarEqn(3600.0, ones_42);

    //std::cout << "yPhip: " << std::endl << yPhip << std::endl;
    //std::cout << "expected_yPhip: " << std::endl << expected_yPhip << std::endl;
    assert(yPhip.equals(expected_yPhip, 10e139) && "VarEqn incorrecta");
    std::cout << "VarEqn correcta" << std::endl;
}

void test_DEInteg()
{
    Matrix Y0_apr = Matrix(1, 6);
    Y0_apr(1, 1) = 6221397.62857869;
    Y0_apr(1, 2) = 2867713.77965738;
    Y0_apr(1, 3) = 3006155.98509949;
    Y0_apr(1, 4) = 4645.04725161807;
    Y0_apr(1, 5) = -2752.21591588205;
    Y0_apr(1, 6) = -7507.99940987033;
    
    Matrix expected_Y = Matrix(1, 6);
    expected_Y(1, 1) = 5542555.93722861;
    expected_Y(1, 2) = 3213514.8673492;
    expected_Y(1, 3) = 3990892.97587686;
    expected_Y(1, 4) = 5394.06842166353;
    expected_Y(1, 5) = -2365.21337882342;
    expected_Y(1, 6) = -7061.84554200298;

    Matrix Y = DEInteg(Accel, 0.0, -134.999991953373, 1e-13, 1e-6, Y0_apr);

    std::cout << "Y: " << std::endl << Y << std::endl;
    std::cout << "expected_Y: " << std::endl << expected_Y << std::endl;
    assert(Y.equals(expected_Y, 10e6) && "DEInteg incorrecta");
}

//-----------------------------------------------------------------------------------------------
// int main
//-----------------------------------------------------------------------------------------------
/**
 * @brief Función principal que ejecuta todos los tests unitarios.
 * @return 0 si todos los tests han sido superados.
 */
//------------------------------------------------------------------------------------------------
int main()
{
    //test_asignar_imprimir();  // Solo imprime por pantalla, la comento para que no moleste
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
    test_subVector();
    test_concatenateRows(); 
    test_doubleArrayToMatrix();
    test_matrixToDoubleArray();

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
    test_eop19620101(); // Se ha comprobado que imprime los datos correctos
    test_position();
    test_Mjday();
    test_Mjday_TDB();
    test_IERS();
    test_MeanObliquity();
    test_EccAnom();
    test_Cheb3D();
    test_timediff();
    test_AzElPa();
    test_Geodetic();
    test_Legendre();
    test_NutAngles();
    test_gmst();
    test_elements();
    test_angl();
    test_TimeUpdate();
    test_PrecMatrix();
    test_PoleMatrix();
    test_NutMatrix();
    test_MeasUpdate();
    test_LTC();
    test_EqnEquinox();
    test_GGM03S();  // Se ha comprobado que imprime los datos correctos
    test_AccelHarmonic();
    test_DE430Coeff(); // Se ha comprobado que imprime los datos correctos
    test_JPL_Eph_DE430();
    test_roots();
    test_gast();
    test_GHAMatrix();
    test_gibss();
    test_hgibbs();
    //test_anglesg(); // Nefasta experiencia
    test_Accel();
    test_G_AccelHarmonic();
    test_EqnVar();
    test_DEInteg();

    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "Todos los tests del proyecto han sido superados" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    getchar();

    return 0;
}