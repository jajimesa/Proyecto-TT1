//$Source$
//------------------------------------------------------------------------------
// JPL_Eph_DE430
//------------------------------------------------------------------------------
/**
 * @file JPL_Eph_DE430.cpp
 * @author Javier Jiménez Santana
 * @date 12/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/JPL_Eph_DE430.hpp"

//------------------------------------------------------------------------------
// void JPL_Eph_DE430(double Mjd_TDB, double &r_Mercury, double &r_Venus,
//     double &r_Earth, double &r_Mars, double &r_Jupiter, double &r_Saturn,
//     double &r_Uranus, double &r_Neptune, double &r_Pluto, double &r_Moon,
//     double &r_Sun)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la posición ecuatorial del sol, la luna y los nueve planetas
 * principales usando las efemérides JPL.
 *
 * @param Mjd_TDB [in] Fecha juliana modificada de TDB.
 * @param r_Mercury [out] Posición ecuatorial de Mercurio.
 * @param r_Venus [out] Posición ecuatorial de Venus.
 * @param r_Earth [out] Posición ecuatorial de la Tierra.
 * @param r_Mars [out] Posición ecuatorial de Marte.
 * @param r_Jupiter [out] Posición ecuatorial de Júpiter.
 * @param r_Saturn [out] Posición ecuatorial de Saturno.
 * @param r_Uranus [out] Posición ecuatorial de Urano.
 * @param r_Neptune [out] Posición ecuatorial de Neptuno.
 * @param r_Pluto [out] Posición ecuatorial de Plutón.
 * @param r_Moon [out] Posición ecuatorial de la Luna.
 * @param r_Sun [out] Posición ecuatorial del Sol.
 */
//------------------------------------------------------------------------------
void JPL_Eph_DE430(double Mjd_TDB,
    Matrix &r_Mercury, Matrix &r_Venus, Matrix &r_Earth, Matrix &r_Mars,
    Matrix &r_Jupiter, Matrix &r_Saturn, Matrix &r_Uranus, Matrix &r_Neptune,
    Matrix &r_Pluto, Matrix &r_Moon, Matrix &r_Sun)
{
    Matrix PC = *Global::PC;

    double JD = Mjd_TDB + 2400000.5;

    int i = -1;
    Matrix PCtemp = Matrix::zeros(1, 1020); // Inicializo con ceros
    for (int k = 1; k <= PC.n_row; k++) {
        if (PC(k, 1) <= JD && JD <= PC(k, 2)) {
            i = k;
            break;
        }
    }
    if (i != -1) {
        // Entonces encontró un intervalo válido en PC
        PCtemp.copy(PC.row(i));
    } else {
        exit(EXIT_FAILURE);
    }

    double t1 = PCtemp(1, 1) - 2400000.5; // MJD at start of interval

    double dt = Mjd_TDB - t1;

    //==============================================================================
    // Cálculo de la posición de la Tierra
    //==============================================================================
    Matrix temp = Matrix(1, 4);
    
    // temp = (231:13:270);
    int aux = 1;
    for (int i = 231; i <= 270; i += 13) {
        temp(1, aux) = i;
        aux++;
    }
    Matrix Cx_Earth_aux = PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1);
    Matrix Cy_Earth_aux = PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1);
    Matrix Cz_Earth_aux = PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1);
    
    temp.copy(temp + 39);

    Matrix Cx = PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1);
    Matrix Cy = PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1);
    Matrix Cz = PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1);

    // Cx_Earth = [Cx_Earth,Cx];
    // Cy_Earth = [Cy_Earth,Cy];
    // Cz_Earth = [Cz_Earth,Cz];   
    Matrix Cx_Earth = Matrix::concatenateRows(Cx_Earth_aux, Cx);
    Matrix Cy_Earth = Matrix::concatenateRows(Cy_Earth_aux, Cy);
    Matrix Cz_Earth = Matrix::concatenateRows(Cz_Earth_aux, Cz);

    double Mjd0 = 0;
    int j = 0;
    if (0 <= dt && dt <= 16) 
    {
        Mjd0 = t1;
    } 
    else if (16 < dt && dt <= 32) 
    {
        j = 1;
        Mjd0 = t1 + 16;
    }

    Matrix auxCheb3D = Cheb3D(Mjd_TDB, 13, Mjd0, Mjd0 + 16, 
                    Cx_Earth.subvectorFromRow(1, 13 * j + 1, 13 * j + 13),
                    Cy_Earth.subvectorFromRow(1, 13 * j + 1, 13 * j + 13),
                    Cz_Earth.subvectorFromRow(1, 13 * j + 1, 13 * j + 13));
    r_Earth.copy(auxCheb3D * 1e3);

    //==============================================================================
    // Cálculo de la posición de la Luna
    //==============================================================================    
    // temp = (441:13:480);
    aux = 1;
    for (int i = 441; i <= 480; i += 13) {
        temp(1, aux) = i;
        aux++;
    }

    /***********************************
    Cx_Moon = PCtemp(temp(1):temp(2)-1);
    Cy_Moon = PCtemp(temp(2):temp(3)-1);
    Cz_Moon = PCtemp(temp(3):temp(4)-1);
    for i=1:7
        temp = temp+39;
        Cx = PCtemp(temp(1):temp(2)-1);
        Cy = PCtemp(temp(2):temp(3)-1);
        Cz = PCtemp(temp(3):temp(4)-1);   
        Cx_Moon = [Cx_Moon,Cx];
        Cy_Moon = [Cy_Moon,Cy];
        Cz_Moon = [Cz_Moon,Cz];    
    end
    */
    Matrix Cx_Moon = PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1);
    Matrix Cy_Moon = PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1);
    Matrix Cz_Moon = PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1);

    Matrix Cx_Moon_aux(1, 1);
    Matrix Cy_Moon_aux(1, 1);
    Matrix Cz_Moon_aux(1, 1);

    for (int i = 1; i <= 7; i++) {
        temp.copy(temp + 39);
        Cx.trueCopy(PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1));
        Cy.trueCopy(PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1));
        Cz.trueCopy(PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1));

        Cx_Moon_aux.trueCopy(Cx_Moon);
        Cy_Moon_aux.trueCopy(Cy_Moon);
        Cz_Moon_aux.trueCopy(Cz_Moon);

        Cx_Moon.trueCopy(Matrix::concatenateRows(Cx_Moon_aux, Cx));
        Cy_Moon.trueCopy(Matrix::concatenateRows(Cy_Moon_aux, Cy));
        Cz_Moon.trueCopy(Matrix::concatenateRows(Cz_Moon_aux, Cz));
    }
    //***********************************
    j = 0;
    if (0<=dt && dt<=4)
    {
        Mjd0 = t1;
    }
    else if (4 < dt && dt <= 8)
    {
        j = 1;
        Mjd0 = t1 + 4 * j;
    }
    else if (8 < dt && dt <= 12)
    {
        j = 2;
        Mjd0 = t1 + 4 * j;
    }
    else if (12 < dt && dt <= 16)
    {
        j = 3;
        Mjd0 = t1 + 4 * j;
    }
    else if (16 < dt && dt <= 20)
    {
        j = 4;
        Mjd0 = t1 + 4 * j;
    }
    else if (20 < dt && dt <= 24)
    {
        j = 5;
        Mjd0 = t1 + 4 * j;
    }
    else if (24 < dt && dt <= 28)
    {
        j = 6;
        Mjd0 = t1 + 4 * j;
    }
    else if (28 < dt && dt <= 32)
    {
        j = 7;
        Mjd0 = t1 + 4 * j;
    }

    //std::cout << Cx_Moon << std::endl;
    //std::cout << Cy_Moon << std::endl;
    //std::cout << Cz_Moon << std::endl;
    //std::cout << "j: " << j << std::endl;
    auxCheb3D.copy(Cheb3D(Mjd_TDB, 13, Mjd0, Mjd0 + 4, 
                Cx_Moon.subvectorFromRow(1, 13 * j + 1, 13 * j + 13),
                Cy_Moon.subvectorFromRow(1, 13 * j + 1, 13 * j + 13),
                Cz_Moon.subvectorFromRow(1, 13 * j + 1, 13 * j + 13)));
    //std::cout << auxCheb3D << std::endl;
    r_Moon.copy(auxCheb3D * 1e3);

    //==============================================================================
    // Cálculo de la posición del Sol
    //==============================================================================
    // temp = (753:11:786);
    aux = 1;
    for (int i = 753; i <= 786; i += 11) {
        temp(1, aux) = i;
        aux++;
    }

    Matrix Cx_Sun_aux = PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1);
    Matrix Cy_Sun_aux = PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1);
    Matrix Cz_Sun_aux = PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1);

    temp.copy(temp + 33);

    Cx.trueCopy(PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1));
    Cy.trueCopy(PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1));
    Cz.trueCopy(PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1));

    // Cx_Sun = [Cx_Sun,Cx];
    // Cy_Sun = [Cy_Sun,Cy];
    // Cz_Sun = [Cz_Sun,Cz];
    Matrix Cx_Sun = Matrix::concatenateRows(Cx_Sun_aux, Cx);
    Matrix Cy_Sun = Matrix::concatenateRows(Cy_Sun_aux, Cy);
    Matrix Cz_Sun = Matrix::concatenateRows(Cz_Sun_aux, Cz);

    if (0 <= dt && dt <= 16) 
    {
        j = 0;
        Mjd0 = t1;
    } 
    else if (16 < dt && dt <= 32) 
    {
        j = 1;
        Mjd0 = t1 + 16 * j;
    }

    //std::cout << Cx_Sun << std::endl;
    //std::cout << Cy_Sun << std::endl;
    //std::cout << Cz_Sun << std::endl;
    auxCheb3D.copy(Cheb3D(Mjd_TDB, 11, Mjd0, Mjd0 + 16, 
                    Cx_Sun.subvectorFromRow(1, 11 * j + 1, 11 * j + 11),
                    Cy_Sun.subvectorFromRow(1, 11 * j + 1, 11 * j + 11),
                    Cz_Sun.subvectorFromRow(1, 11 * j + 1, 11 * j + 11)));
    //std::cout << auxCheb3D * 1e3 << std::endl;
    r_Sun.copy(auxCheb3D * 1e3);

    //==============================================================================
    // Cálculo de la posición de Mercurio
    //==============================================================================
    // temp = (3:14:45);
    aux = 1;
    for (int i = 3; i <= 45; i += 14) {
        temp(1, aux) = i;
        aux++;
    }

    /***********************************
    Cx_Mercury = PCtemp(temp(1):temp(2)-1);
    Cy_Mercury = PCtemp(temp(2):temp(3)-1);
    Cz_Mercury = PCtemp(temp(3):temp(4)-1);
    for i=1:3
        temp = temp+42;
        Cx = PCtemp(temp(1):temp(2)-1);
        Cy = PCtemp(temp(2):temp(3)-1);
        Cz = PCtemp(temp(3):temp(4)-1);
        Cx_Mercury = [Cx_Mercury,Cx];
        Cy_Mercury = [Cy_Mercury,Cy];
        Cz_Mercury = [Cz_Mercury,Cz];    
    end
    */
    Matrix Cx_Mercury = PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1);
    Matrix Cy_Mercury = PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1);
    Matrix Cz_Mercury = PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1);

    Matrix Cx_Mercury_aux(1, 1);
    Matrix Cy_Mercury_aux(1, 1);
    Matrix Cz_Mercury_aux(1, 1);

    for (int i = 1; i <= 3; i++) {
        temp.copy(temp + 42);
        Cx.trueCopy(PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1));
        Cy.trueCopy(PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1));
        Cz.trueCopy(PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1));

        Cx_Mercury_aux.trueCopy(Cx_Mercury);
        Cy_Mercury_aux.trueCopy(Cy_Mercury);
        Cz_Mercury_aux.trueCopy(Cz_Mercury);

        Cx_Mercury.trueCopy(Matrix::concatenateRows(Cx_Mercury_aux, Cx));
        Cy_Mercury.trueCopy(Matrix::concatenateRows(Cy_Mercury_aux, Cy));
        Cz_Mercury.trueCopy(Matrix::concatenateRows(Cz_Mercury_aux, Cz));
    }
    //***********************************

    if (0<=dt && dt<=8)
    {
        j=0;
        Mjd0 = t1;
    }
    else if(8<dt && dt<=16) 
    {
        j=1;
        Mjd0 = t1+8*j;
    }
    else if (16<dt && dt<=24) 
    {
        j=2;
        Mjd0 = t1+8*j;
    }
    else if (24<dt && dt<=32) 
    {
        j=3;
        Mjd0 = t1+8*j;
    }

    auxCheb3D.copy(Cheb3D(Mjd_TDB, 14, Mjd0, Mjd0+8, 
                    Cx_Mercury.subvectorFromRow(1, 14*j+1, 14*j+14),
                    Cy_Mercury.subvectorFromRow(1, 14*j+1, 14*j+14),
                    Cz_Mercury.subvectorFromRow(1, 14*j+1, 14*j+14)));
    r_Mercury.copy(auxCheb3D * 1e3);

    //==============================================================================
    // Cálculo de la posición de Venus
    //==============================================================================
    // temp = (171:10:201);
    aux = 1;
    for (int i = 171; i <= 201; i += 10) {
        temp(1, aux) = i;
        aux++;
    }

    Matrix Cx_Venus_aux = PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1);
    Matrix Cy_Venus_aux = PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1);
    Matrix Cz_Venus_aux = PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1);

    temp.copy(temp + 30);

    Cx.trueCopy(PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1));
    Cy.trueCopy(PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1));
    Cz.trueCopy(PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1));

    // Cx_Venus = [Cx_Venus,Cx];
    // Cy_Venus = [Cy_Venus,Cy];
    // Cz_Venus = [Cz_Venus,Cz];
    Matrix Cx_Venus = Matrix::concatenateRows(Cx_Venus_aux, Cx);
    Matrix Cy_Venus = Matrix::concatenateRows(Cy_Venus_aux, Cy);
    Matrix Cz_Venus = Matrix::concatenateRows(Cz_Venus_aux, Cz);
    
    if (0<=dt && dt<=16)
    {
        j=0;
        Mjd0 = t1;
    }
    else if(16<dt && dt<=32)
    {
        j=1;
        Mjd0 = t1+16*j;
    }

    auxCheb3D.copy(Cheb3D(Mjd_TDB, 10, Mjd0, Mjd0+16, 
                Cx_Venus.subvectorFromRow(1, 10*j+1, 10*j+10),
                Cy_Venus.subvectorFromRow(1, 10*j+1, 10*j+10),
                Cz_Venus.subvectorFromRow(1, 10*j+1, 10*j+10)));
    r_Venus.copy(auxCheb3D * 1e3);

    //==============================================================================
    // Cálculo de la posición de Marte
    //==============================================================================
    // temp = (309:11:342);
    aux = 1;
    for (int i = 309; i <= 342; i += 11) {
        temp(1, aux) = i;
        aux++;
    }

    Matrix Cx_Mars = PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1);
    Matrix Cy_Mars = PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1);
    Matrix Cz_Mars = PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1);

    j = 0;
    Mjd0 = t1;
    auxCheb3D.copy(Cheb3D(Mjd_TDB, 11, Mjd0, Mjd0 + 32, 
                    Cx_Mars.subvectorFromRow(1, 11 * j + 1, 11 * j + 11),
                    Cy_Mars.subvectorFromRow(1, 11 * j + 1, 11 * j + 11),
                    Cz_Mars.subvectorFromRow(1, 11 * j + 1, 11 * j + 11)));
    r_Mars.copy(auxCheb3D * 1e3);

    //==============================================================================
    // Cálculo de la posición de Júpiter
    //==============================================================================
    // temp = (342:8:366);
    aux = 1;
    for (int i = 342; i <= 366; i += 8) {
        temp(1, aux) = i;
        aux++;
    }

    Matrix Cx_Jupiter = PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1);
    Matrix Cy_Jupiter = PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1);
    Matrix Cz_Jupiter = PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1);

    j = 0;
    Mjd0 = t1;
    auxCheb3D.copy(Cheb3D(Mjd_TDB, 8, Mjd0, Mjd0 + 32, 
                    Cx_Jupiter.subvectorFromRow(1, 8 * j + 1, 8 * j + 8),
                    Cy_Jupiter.subvectorFromRow(1, 8 * j + 1, 8 * j + 8),
                    Cz_Jupiter.subvectorFromRow(1, 8 * j + 1, 8 * j + 8)));
    r_Jupiter.copy(auxCheb3D * 1e3);

    //==============================================================================
    // Cálculo de la posición de Saturno
    //==============================================================================
    // temp = (366:7:387);
    aux = 1;
    for (int i = 366; i <= 387; i += 7) {
        temp(1, aux) = i;
        aux++;
    }

    Matrix Cx_Saturn = PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1);
    Matrix Cy_Saturn = PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1);
    Matrix Cz_Saturn = PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1);

    j = 0;
    Mjd0 = t1;
    auxCheb3D.copy(Cheb3D(Mjd_TDB, 7, Mjd0, Mjd0 + 32, 
                    Cx_Saturn.subvectorFromRow(1, 7 * j + 1, 7 * j + 7),
                    Cy_Saturn.subvectorFromRow(1, 7 * j + 1, 7 * j + 7),
                    Cz_Saturn.subvectorFromRow(1, 7 * j + 1, 7 * j + 7)));
    r_Saturn.copy(auxCheb3D * 1e3);

    //==============================================================================
    // Cálculo de la posición de Urano
    //==============================================================================
    // temp = (387:6:405);
    aux = 1;
    for (int i = 387; i <= 405; i += 6) {
        temp(1, aux) = i;
        aux++;
    }

    Matrix Cx_Uranus = PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1);
    Matrix Cy_Uranus = PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1);
    Matrix Cz_Uranus = PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1);

    j = 0;
    Mjd0 = t1;
    auxCheb3D.copy(Cheb3D(Mjd_TDB, 6, Mjd0, Mjd0 + 32, 
                    Cx_Uranus.subvectorFromRow(1, 6 * j + 1, 6 * j + 6),
                    Cy_Uranus.subvectorFromRow(1, 6 * j + 1, 6 * j + 6),
                    Cz_Uranus.subvectorFromRow(1, 6 * j + 1, 6 * j + 6)));
    r_Uranus.copy(auxCheb3D * 1e3);

    //==============================================================================
    // Cálculo de la posición de Neptuno
    //==============================================================================
    // temp = (405:6:423);
    aux = 1;
    for (int i = 405; i <= 423; i += 6) {
        temp(1, aux) = i;
        aux++;
    }

    Matrix Cx_Neptune = PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1);
    Matrix Cy_Neptune = PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1);
    Matrix Cz_Neptune = PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1);

    j = 0;
    Mjd0 = t1;
    auxCheb3D.copy(Cheb3D(Mjd_TDB, 6, Mjd0, Mjd0 + 32, 
                    Cx_Neptune.subvectorFromRow(1, 6 * j + 1, 6 * j + 6),
                    Cy_Neptune.subvectorFromRow(1, 6 * j + 1, 6 * j + 6),
                    Cz_Neptune.subvectorFromRow(1, 6 * j + 1, 6 * j + 6)));
    r_Neptune.copy(auxCheb3D * 1e3);

    //==============================================================================
    // Cálculo de la posición de Plutón
    //==============================================================================
    // temp = (423:6:441);
    aux = 1;
    for (int i = 423; i <= 441; i += 6) {
        temp(1, aux) = i;
        aux++;
    }

    Matrix Cx_Pluto = PCtemp.subvectorFromRow(1, temp(1, 1), temp(1, 2) - 1);
    Matrix Cy_Pluto = PCtemp.subvectorFromRow(1, temp(1, 2), temp(1, 3) - 1);
    Matrix Cz_Pluto = PCtemp.subvectorFromRow(1, temp(1, 3), temp(1, 4) - 1);

    j = 0;
    Mjd0 = t1;
    auxCheb3D.copy(Cheb3D(Mjd_TDB, 6, Mjd0, Mjd0 + 32, 
                    Cx_Pluto.subvectorFromRow(1, 6 * j + 1, 6 * j + 6),
                    Cy_Pluto.subvectorFromRow(1, 6 * j + 1, 6 * j + 6),
                    Cz_Pluto.subvectorFromRow(1, 6 * j + 1, 6 * j + 6)));
    r_Pluto.copy(auxCheb3D * 1e3);

    /*
    NUTATIONS y LIBRATIONS (NO IMPLEMENTADO): no se utilizan en el proyecto y es copiar
    y pegar código de las posiciones de los planetas cambiando dos cosas, pero quiero agilizar
    el trabajo.
    */
   
    double EMRAT = 81.30056907419062; // DE430
    double EMRAT1 = 1/(1+EMRAT);

    r_Earth.copy(r_Earth - r_Moon*EMRAT1);
    r_Mercury.copy(r_Earth*(-1.0) + r_Mercury);
    r_Venus.copy(r_Earth*(-1.0) + r_Venus);
    r_Mars.copy(r_Earth*(-1.0) + r_Mars);
    r_Jupiter.copy(r_Earth*(-1.0) + r_Jupiter);
    r_Saturn.copy(r_Earth*(-1.0) + r_Saturn);
    r_Uranus.copy(r_Earth*(-1.0) + r_Uranus);
    r_Neptune.copy(r_Earth*(-1.0) + r_Neptune);
    r_Pluto.copy(r_Earth*(-1.0) + r_Pluto);
    r_Sun.copy(r_Earth*(-1.0) + r_Sun);
}