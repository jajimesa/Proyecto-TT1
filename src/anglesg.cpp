//$Source$
//------------------------------------------------------------------------------
// anglesg.cpp
//------------------------------------------------------------------------------
/**
 * @file anglesg.cpp
 * @author Javier Jiménez Santana
 * @date 15/05/2024
 */
//------------------------------------------------------------------------------

#include "../include/anglesg.hpp"

//------------------------------------------------------------------------------
// void anglesg(double az1, double az2, double az3,
//             double el1, double el2, double el3,
//             double Mjd1, double Mjd2, double Mjd3,
//             Matrix Rs1, Matrix Rs2, Matrix Rs3,
//             Matrix &r2, Matrix &v2)
//------------------------------------------------------------------------------
/**
 * @brief Solución del problema de determinación de órbita usando tres 
 * avistamientos ópticos.
 *
 * @param az1 Azimut en t1 [rad].
 * @param az2 Azimut en t2 [rad].
 * @param az3 Azimut en t3 [rad].
 * @param el1 Elevación en t1 [rad].
 * @param el2 Elevación en t2 [rad].
 * @param el3 Elevación en t3 [rad].
 * @param Mjd1 Fecha juliana modificada de t1.
 * @param Mjd2 Fecha juliana modificada de t2.
 * @param Mjd3 Fecha juliana modificada de t3.
 * @param Rs1 Vector de posición de la estación 1 en IJK [m].
 * @param Rs2 Vector de posición de la estación 2 en IJK [m].
 * @param Rs3 Vector de posición de la estación 3 en IJK [m].
 * @param r2 [out] Vector de posición en IJK en t2 [m].
 * @param v2 [out] Vector de velocidad en IJK en t2 [m/s].
 */
//------------------------------------------------------------------------------
void anglesg(double az1, double az2, double az3, 
            double el1, double el2, double el3,
            double Mjd1, double Mjd2, double Mjd3,
            Matrix Rs1, Matrix Rs2, Matrix Rs3,
            Matrix &r2, Matrix &v2)
{
    Matrix eopdata = *Global::eopdata;

    Matrix L1 = Matrix::zeros(1, 3);
    L1(1, 1) = cos(el1)*sin(az1);
    L1(1, 2) = cos(el1)*cos(az1);
    L1(1, 3) = sin(el1);   
    Matrix L2 = Matrix::zeros(1, 3);
    L2(1, 1) = cos(el2)*sin(az2);
    L2(1, 2) = cos(el2)*cos(az2);
    L2(1, 3) = sin(el2);
    Matrix L3 = Matrix::zeros(1, 3);
    L3(1, 1) = cos(el3)*sin(az3);
    L3(1, 2) = cos(el3)*cos(az3);
    L3(1, 3) = sin(el3);

    std::cout << "He llegado a Geodetic" << std::endl;
    double lon1 = 0.0;
    double lat1 = 0.0;
    double h1 = 0.0;
    Geodetic(Rs1, lon1, lat1, h1);

    double lon2 = 0.0;
    double lat2 = 0.0;
    double h2 = 0.0;
    Geodetic(Rs2, lon2, lat2, h2);

    double lon3 = 0.0;
    double lat3 = 0.0;
    double h3 = 0.0;
    Geodetic(Rs3, lon3, lat3, h3);

    std::cout << "He llegado a LTC" << std::endl;

    Matrix M1 = LTC(lon1, lat1);
    //Matrix M2 = LTC(lon2, lat2);
    //Matrix M3 = LTC(lon3, lat3);

    std::cout << "He llegado a M1 M2 M3" << std::endl;

    // body-fixed system
    Matrix Lb1 = M1.transpose()*L1.transpose();
    Matrix Lb2 = M1.transpose()*L2.transpose();
    Matrix Lb3 = M1.transpose()*L3.transpose();

    std::cout << "He llegado a IERS" << std::endl;

    // mean of date system (J2000)
    double Mjd_UTC = Mjd1;
    double x_pole = 0.0;
    double y_pole = 0.0;
    double UT1_UTC = 0.0;
    double LOD = 0.0;
    double dpsi = 0.0;
    double deps = 0.0;
    double dx_pole = 0.0;
    double dy_pole = 0.0;
    double TAI_UTC = 0.0;
    IERS(eopdata, Mjd_UTC, 'l', x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC);
    double UT1_TAI = 0.0;
    double UTC_GPS = 0.0;
    double UT1_GPS = 0.0;
    double TT_UTC = 0.0;
    double GPS_UTC = 0.0;
    timediff(UT1_UTC, TAI_UTC, UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC);
    double Mjd_TT = Mjd_UTC + TT_UTC/86400.0;
    double Mjd_UT1 = Mjd_TT + (UT1_UTC - TT_UTC)/86400.0;

    std::cout << "He llegado a P N T E" << std::endl;

    Matrix P = PrecMatrix(Const::MJD_J2000, Mjd_TT);
    Matrix N = NutMatrix(Mjd_TT);
    std::cout << "N:" << N << std::endl;
    std::cout << "P:" << P << std::endl;
    Matrix T = N*P;
    std::cout << "T:" << T << std::endl;
    Matrix E = PoleMatrix(x_pole, y_pole)*GHAMatrix(Mjd_UT1)*T;
    std::cout << "E:" << E << std::endl;

    std::cout << "Lb1:" << Lb1 << std::endl;
    Matrix Lm1 = E.transpose()*Lb1;
    std::cout << "Lm1:" << Lm1 << std::endl;
    std::cout << "Rs1:" << Rs1 << std::endl;
    std::cout << "E.transpose():" << E.transpose() << std::endl;
    Matrix Rs1Aux = E.transpose()*Rs1.transpose();
    std::cout << "Rs1Aux:" << Rs1Aux << std::endl;
    Rs1(1, 1) = Rs1Aux(1, 1);
    Rs1(1, 2) = Rs1Aux(2, 1);
    Rs1(1, 3) = Rs1Aux(3, 1);
    std::cout << "Nueva Rs1:" << Rs1 << std::endl;

    std::cout << "He llegado a IERS" << std::endl;

    Mjd_UTC = Mjd2;
    IERS(eopdata, Mjd_UTC, 'l', x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC);
    timediff(UT1_UTC, TAI_UTC, UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC);
    Mjd_TT = Mjd_UTC + TT_UTC/86400.0;
    Mjd_UT1 = Mjd_TT + (UT1_UTC - TT_UTC)/86400.0;

    std::cout << "He llegado a P N T E (2)" << std::endl;
    
    P.trueCopy(PrecMatrix(Const::MJD_J2000, Mjd_TT));
    std::cout << "P:" << P << std::endl;
    N.trueCopy(NutMatrix(Mjd_TT));
    std::cout << "N:" << N << std::endl;
    T.trueCopy(N*P);
    std::cout << "T:" << T << std::endl;
    E.trueCopy(PoleMatrix(x_pole, y_pole)*GHAMatrix(Mjd_UT1)*T);
    std::cout << "E:" << E << std::endl;

    std::cout << "Lb2:" << Lb2 << std::endl;
    Matrix Lm2 = E.transpose()*Lb2;
    std::cout << "Lm2:" << Lm2 << std::endl;
    Matrix Rs2aux = E.transpose()*Rs2.transpose();
    std::cout << "Rs2aux:" << Rs2aux << std::endl;
    Rs2(1, 1) = Rs2aux(1, 1);
    Rs2(1, 2) = Rs2aux(2, 1);
    Rs2(1, 3) = Rs2aux(3, 1);
    std::cout << "Nueva Rs2:" << Rs2 << std::endl;

    std::cout << "He llegado a IERS 2" << std::endl;
    Mjd_UTC = Mjd3;
    IERS(eopdata, Mjd_UTC, 'l', x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC);
    timediff(UT1_UTC, TAI_UTC, UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC);
    Mjd_TT = Mjd_UTC + TT_UTC/86400.0;
    Mjd_UT1 = Mjd_TT + (UT1_UTC - TT_UTC)/86400.0;

    std::cout << "He llegado a P N T E (3)" << std::endl;

    std::cout << "P:" << P << std::endl;
    P.trueCopy(PrecMatrix(Const::MJD_J2000, Mjd_TT));
    std::cout << "P:" << P << std::endl;
    N.trueCopy(NutMatrix(Mjd_TT));
    std::cout << "N:" << N << std::endl;
    T.trueCopy(N*P);
    std::cout << "T:" << T << std::endl;
    E.trueCopy(PoleMatrix(x_pole, y_pole)*GHAMatrix(Mjd_UT1)*T);
    std::cout << "E:" << E << std::endl;

    Matrix Lm3 = E.transpose()*Lb3;
    std::cout << "Lm3:" << Lm3 << std::endl;
    Matrix Rs3aux = E.transpose()*Rs3.transpose();
    std::cout << "Rs3aux:" << Rs3aux << std::endl;
    Rs3(1, 1) = Rs3aux(1, 1);
    Rs3(1, 2) = Rs3aux(2, 1);
    Rs3(1, 3) = Rs3aux(3, 1);
    std::cout << "Nueva Rs3:" << Rs3 << std::endl;

    std::cout << "He llegado a geocentric inertial position" << std::endl;
    // geocentric inertial position
    double tau1 = (Mjd1 - Mjd2)*86400.0;
    double tau3 = (Mjd3 - Mjd2)*86400.0;

    double a1 = tau3/(tau3-tau1);
    double a3 =-tau1/(tau3-tau1);

    double b1 = tau3/(6*(tau3-tau1))*((tau3-tau1)*(tau3+tau1)-pow(tau3,2));
    double b3 =-tau1/(6*(tau3-tau1))*((tau3-tau1)*(tau3+tau1)-pow(tau1,2));

    b1 = tau3/(6*(tau3-tau1))*(pow(tau3-tau1,2)-pow(tau3,2));
    b3 =-tau1/(6*(tau3-tau1))*(pow(tau3-tau1,2)-pow(tau1,2));

    Matrix auxD1 = Matrix::concatenateRows(Lm1, Lm2);
    auxD1.trueCopy(Matrix::concatenateRows(auxD1, Lm3));
    Matrix auxD2 = Matrix::concatenateRows(Rs1.transpose(), Rs2.transpose());
    auxD2.trueCopy(Matrix::concatenateRows(auxD2, Rs3.transpose()));
    std::cout << "auxD1:" << auxD1 << std::endl;
    std::cout << "auxD2:" << auxD2 << std::endl;
    Matrix D = auxD1.inverse() * auxD2.transpose();
    std::cout << "D:" << D << std::endl;

    double d1s = D(2,1)*a1-D(2,2)+D(2,3)*a3;
    double d2s = D(2,1)*b1+D(2,3)*b3;

    std::cout << "He llegado a Ccye" << std::endl;
    std::cout << "Lm2:" << Lm2 << std::endl;
    std::cout << "Rs2:" << Rs2 << std::endl;
    double Ccye = 2*Lm2.transpose().dot(Rs2);

    std::cout << "He llegado al polinomio" << std::endl;

    Matrix poly = Matrix::zeros(1, 9);
    poly(1, 1) = 1.0;  // R2^8... polynomial
    poly(1, 2) = 0.0;
    poly(1, 3) = -(pow(d1s, 2) + d1s*Ccye + (pow(Rs2.norm(), 2)));
    poly(1, 4) = 0.0;
    poly(1, 5) = 0.0;
    poly(1, 6) = -Const::GM_Earth*(d2s*Ccye + 2*d1s*d2s);
    poly(1, 7) = 0.0;
    poly(1, 8) = 0.0;
    poly(1, 9) = -pow(Const::GM_Earth, 2)*pow(d2s,2);
    
    Matrix rootarr = roots(poly);

    double bigr2 = -99999990.0;

    std::cout << "He llegado al bucle de raices" << std::endl;
    for (int j = 1; j <= 2*8; j = j+2)
    {
        if (isReal(rootarr(1, j), rootarr(1, j+1)) && (rootarr(1, j) > bigr2))
        {
            bigr2 = rootarr(1, j);
        }
    }
    std::cout << "bigr2:" << bigr2 << std::endl;

    double u = Const::GM_Earth/(pow(bigr2, 3));

    double C1 = a1+b1*u;
    double C2 = -1;
    double C3 = a3+b3*u;

    Matrix temp = Matrix(1, 3);
    temp(1, 1) = C1;
    temp(1, 2) = C2;
    temp(1, 3) = C3;
    std::cout << "temp:" << temp << std::endl;
    Matrix tempAux = D * (-1) * temp.transpose();
    temp.trueCopy(tempAux.transpose());
    std::cout << "Nueva temp" << temp << std::endl;
    double rho1 = temp(1, 1) / (a1 + b1*u);
    double rho2 = temp(1, 2);
    double rho3 = temp(1, 3) / (a3 + b3*u);

    double rhoold1 = rho1;
    double rhoold2 = rho2;
    double rhoold3 = rho3;

    rho2 = 99999999.9;
    int ll   = 0;

    Matrix r1 = Matrix::zeros(1, 1);
    Matrix r3 = Matrix::zeros(1, 1);
    double magr1 = 0.0;
    double magr2 = 0.0;
    double magr3 = 0.0;
    double theta = 0.0;
    double theta1 = 0.0;
    double copa = 0.0;
    string error = "\0";
    std::cout << "He llegado al bucle de iteraciones" << std::endl;
    while ((abs(rhoold2-rho2) > 1e-12) && (ll <= 0 ))
    {
        ll = ll + 1;
        rho2 = rhoold2;
        
        std::cout << "trueCopy ri" << std::endl;
        r1.trueCopy(Rs1.transpose() + Lm1*rho1);
        r2.trueCopy(Rs2.transpose() + Lm2*rho2);
        r3.trueCopy(Rs3.transpose() + Lm3*rho3);
        std::cout << "r1:" << r1 << std::endl;
        std::cout << "r2:" << r2 << std::endl;
        std::cout << "r3:" << r3 << std::endl;
        
        magr1 = r1.norm();
        magr2 = r2.norm();
        magr3 = r2.norm();
        
        gibbs(r1, r2, r3, v2, theta, theta1, copa, error);
        
        if (!(error == "ok\0") & (copa < Const::pi/180.0))
        {
            hgibbs(r1, r2, r3, Mjd1, Mjd2, Mjd3, v2, theta, theta1, copa, error);
        }     
        
        void elements(Matrix y, double& p, double& a, double& e, double& i, double& Omega, double& omega, double& M);
        Matrix elementsAux = Matrix::concatenateRows(r2, v2);
        double p = 0.0;
        double a = 0.0;
        double e = 0.0;
        double i = 0.0;
        double Omega = 0.0;
        double omega = 0.0;
        double M = 0.0;
        elements(elementsAux, p, a, e, i, Omega, omega, M);
        
        double rdot, udot, tausqr, f1, g1, f3, g3;
        if (ll <= 8)
        {
            u = Const::GM_Earth/pow(magr2,3);
            rdot = r2.dot(v2)/magr2;
            udot= (-3*Const::GM_Earth*rdot)/pow(magr2,4);
            
            tausqr= tau1*tau1;
            f1=  1 - 0.5*u*tausqr -(1.0/6.0)*udot*tausqr*tau1 - (1.0/24.0) * u*u*tausqr*tausqr - (1.0/30.0)*u*udot*tausqr*tausqr*tau1;
            g1= tau1 - (1.0/6.0)*u*tau1*tausqr - (1.0/12.0) * udot*tausqr*tausqr - (1.0/120.0)*u*u*tausqr*tausqr*tau1 - (1.0/120.0)*u*udot*tausqr*tausqr*tausqr;
            tausqr= tau3*tau3;
            f3=  1 - 0.5*u*tausqr -(1.0/6.0)*udot*tausqr*tau3 - (1.0/24.0) * u*u*tausqr*tausqr - (1.0/30.0)*u*udot*tausqr*tausqr*tau3;
            g3= tau3 - (1.0/6.0)*u*tau3*tausqr - (1.0/12.0) * udot*tausqr*tausqr - (1.0/120.0)*u*u*tausqr*tausqr*tau3 - (1.0/120.0)*u*udot*tausqr*tausqr*tausqr;
        }
        else
        {    
            theta  = angl(r1,r2);
            theta1 = angl(r2,r3);
            
            f1= 1 - ((magr1*(1 - cos(theta)) / p));
            g1= (magr1*magr2*sin(-theta)) / sqrt(p);
            f3= 1 - ((magr3*(1 - cos(theta1)) / p));
            g3= (magr3*magr2*sin(theta1)) / sqrt(p);
        }
        
        C1 = g3/(f1*g3-f3*g1);
        C2 = -1;
        C3 =-g1/(f1*g3-f3*g1);
        
        double H1 = Const::GM_Earth*tau3/12.0;
        double H3 =-Const::GM_Earth*tau1/12.0;
        double H2 = H1-H3;

        double G1 = -tau3/(tau1*(tau3-tau1));
        double G3 = -tau1/(tau3*(tau3-tau1));
        double G2 = G1-G3;

        double D1 = G1+H1/pow(magr1,3);
        double D2 = G2+H2/pow(magr2,3);
        double D3 = G3+H3/pow(magr3,3);
        
        temp(1, 1) = D1;
        temp(1, 2) = D2;
        temp(1, 3) = D3;
        Matrix tempAux = Matrix::zeros(1, 3);
        tempAux(1, 1) = C1;
        tempAux(1, 2) = C2;
        tempAux(1, 3) = C3;
        tempAux.trueCopy(temp * tempAux.transpose());

        rhoold1 = temp(1, 1)/(a1+b1*u);
        rhoold2 = temp(1, 2) * (-1);
        rhoold3 = temp(1, 3)/(a3+b3*u);
        
        r1.trueCopy(Rs1+Lm1*rhoold1);
        r2.trueCopy(Rs2+Lm2*rhoold2);
        r3.trueCopy(Rs3+Lm3*rhoold3);        
    }

    r1.trueCopy(Rs1+Lm1*rho1);
    r2.trueCopy(Rs2+Lm2*rho2);
    r3.trueCopy(Rs3+Lm3*rho3);
}