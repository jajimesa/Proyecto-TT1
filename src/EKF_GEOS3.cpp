//$Source$
//--------------------------------------------------------------------------------------------
// EKF_GEOS3.cpp
//--------------------------------------------------------------------------------------------
/**
 * @file EKF_GEOS3.cpp
 * @author Javier Jiménez Santana
 * @date 17/05/2024
 */
//--------------------------------------------------------------------------------------------

#include "../include/EKF_GEOS3.hpp"

//--------------------------------------------------------------------------------------------
// void EKF_GEOS3()
//--------------------------------------------------------------------------------------------
/**
 * @brief Determinación de la órbita inicial utilizando los métodos de Gauss y el 
 * Filtro de Kalman Extendido.
 */
//--------------------------------------------------------------------------------------------
void EKF_GEOS3()
{
    // INICIALIZO LAS VARIABLES GLOBALES
    Global::GGM03S(181);
    //Matrix Cnm = *Global::Cnm;
    //Matrix Snm = *Global::Snm;

    Global::eop19620101(21413);
    Matrix eopdata = *Global::eopdata;

    Global::GEOMS3();
    Matrix obs = *Global::obs;

    Global::DE430Coeff(1020);

    const double sigma_range = 92.5;            // [m]
    const double sigma_az = 0.0224*Const::Rad;  // [rad]
    const double sigma_el = 0.0139*Const::Rad;  // [rad]

    // Kaena Point station
    const double lat = Const::Rad*21.5748;      // [rad]
    const double lon = Const::Rad*(-158.2706);  // [rad]
    const double alt = 300.20;                  // [m]

    Matrix Rs = Position(lon, lat, alt).transpose();
    std::cout << "Rs: " << std::endl << Rs << std::endl;

    // OPCIONAL
    /*
    double Mjd1 = obs(1,1);
    double Mjd2 = obs(9,1);
    double Mjd3 = obs(18,1);
    Matrix r2 = Matrix::zeros(1, 1);
    Matrix v2 = Matrix::zeros(1, 1);
    anglesg(obs(1,2),obs(9,2),obs(18,2),obs(1,3),obs(9,3),obs(18,3),
            Mjd1,Mjd2,Mjd3,Rs,Rs,Rs,r2,v2);
    */
    // RESULTADOS ESPERADOS
    Matrix r2 = Matrix(1, 3);
    r2(1, 1) = 6221397.62857869;
    r2(1, 2) = 2867713.77965738;
    r2(1, 3) = 3006155.98509949;
    Matrix v2 = Matrix(1, 3);
    v2(1, 1) = 4645.04725161807;
    v2(1, 2) = -2752.21591588205;
    v2(1, 3) = -7507.99940987033;

    Matrix Y0_apr = Matrix::concatenateRows(r2, v2);
    std::cout << "Y0_apr: " << std::endl << Y0_apr << std::endl;
    
    double Mjd0 = Mjday(1995,1,29,02,38,0);
    std::cout << "Mjd0: " << std::endl << Mjd0 << std::endl;

    double Mjd_UTC = obs(9,1);
    std::cout << "Mjd_UTC: " << std::endl << Mjd_UTC << std::endl;

    Global::AuxParam.Mjd_UTC = Mjd_UTC;
    Global::AuxParam.n = 20;
    Global::AuxParam.m = 20;
    Global::AuxParam.sun = 1;
    Global::AuxParam.moon = 1;
    Global::AuxParam.planets = 1;

    int neqn = 6;
    double* yArr = new double[neqn];
    double* work = new double[100 + 21 * neqn];
    int iwork[5] = {0};  // Inicialización de iwork
    Matrix Y = DEInteg(Accel, 0, -(obs(9,1)-Mjd0)*86400.0, 1e-13, 1e-6, neqn, Y0_apr, yArr, work, iwork);
    std::cout << "Y: " << std::endl << Y << std::endl;   

    Matrix P = Matrix::zeros(6, 6);

    for(int i = 1; i <= 3; i++)
    {
        P(i, i) = 1e8;
    }
    for(int i = 4; i <= 6; i++)
    {
        P(i, i) = 1e3;
    }
    std::cout << "P_inicializada: " << std::endl << P << std::endl;

    Matrix LT = LTC(lon, lat);
    std::cout << "LT: " << std::endl << LT << std::endl;

    Matrix yPhi = Matrix::zeros(1, 42);
    Matrix Phi = Matrix::zeros(6, 6);

    // Measurement loop
    int nobs = 46;
    double t = 0.0;
    double t_old;
    Matrix Y_old = Matrix::zeros(1, 1); // Luego la piso
    double x_pole = 0.0;
    double y_pole = 0.0;
    double UT1_UTC = 0.0;
    double LOD = 0.0;
    double dpsi = 0.0;
    double deps = 0.0;
    double dx_pole = 0.0;
    double dy_pole = 0.0;
    double TAI_UTC = 0.0;
    double UT1_TAI = 0.0;
    double UTC_GPS = 0.0;
    double UT1_GPS = 0.0;
    double TT_UTC = 0.0;
    double GPS_UTC = 0.0;
    double Mjd_TT, Mjd_UT1;
    double theta;
    Matrix U = Matrix::zeros(3, 3);
    Matrix r = Matrix::zeros(1, 3);
    Matrix s = Matrix::zeros(1, 3);
    double Azim, Elev;
    Matrix dAds = Matrix::zeros(1, 3);
    Matrix dEds = Matrix::zeros(1, 3);
    Matrix K = Matrix::zeros(1, 6);
    Matrix dAdY = Matrix::zeros(1, 6);
    Matrix dEdY = Matrix::zeros(1, 6);
    Matrix dDds = Matrix::zeros(1, 3);
    double Dist;
    Matrix dDdY = Matrix::zeros(1, 3);
    Matrix yPhiAux = Matrix(1, 6);
    work = new double[100 + 21 * neqn];

    std::cout << "Comienzo del bucle de observaciones (hasta aqui TODO coincide)" << std::endl;
    std::cout << "---------------------------------------------------------------" << std::endl;
    for(int i=1; i<=nobs; i++)
    {
        std::cout << "Comienzo la observacion " << i << std::endl;

        // Previous step
        t_old = t;
        Y_old.trueCopy(Y);
        std::cout << "Y_old (" << i << "): " << std::endl << Y_old << std::endl;

        // Time increment and propagation
        Mjd_UTC = obs(i,1);                       // Modified Julian Date
        t = (Mjd_UTC-Mjd0)*86400.0;         // Time since epoch [s]

        IERS(eopdata, Mjd_UTC, 'l', x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC);
        std::cout << "IERS ejecutado para la observacion " << i << std::endl;

        timediff(UT1_UTC, TAI_UTC, UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC);

        Mjd_TT = Mjd_UTC + TT_UTC/86400.0;
        Mjd_UT1 = Mjd_TT + (UT1_UTC-TT_UTC)/86400.0;
        Global::AuxParam.Mjd_UTC = Mjd_UTC;
        Global::AuxParam.Mjd_TT = Mjd_TT;
        
        for(int ii=1; ii<=6; ii++)
        {
            yPhi(1, ii) = Y_old(1, ii);
            for(int j=1; j<=6; j++)
            {
                if(ii==j)
                {
                    yPhi(1, 6*j+ii) = 1;
                }
                else
                {
                    yPhi(1, 6*j+ii) = 0;
                }
            }
        }
        std::cout << "yPhi actualizado para la observacion " << i << std::endl;
        std::cout << "yPhi (" << i << "): " << std::endl << yPhi.transpose() << std::endl;

        std::cout << "t - t_old (" << i << "): " << t-t_old << std::endl;
        neqn = 42;
        yArr = new double[neqn];  // neqn = yPhi.n_column * yPhi.n_row
        work = new double[100 + 21 * neqn];
        for(int j=0; j<5; j++)
        {
            iwork[j] = 0;
        }
        DEInteg(VarEqn, 0, t-t_old, 1e-13, 1e-6, yPhi.n_column * yPhi.n_row, yPhi, yArr, work, iwork); // yPhi es actualizado
        std::cout << "DEInteg(VarEqn) ejecutado para la observacion " << i << std::endl;
        std::cout << "yPhi (" << i << "): " << std::endl << yPhi.transpose() << std::endl;

        // Extract state transition matrices
        for (int j = 1; j <= 6; j++) {
            yPhiAux.copy(yPhi.subvectorFromRow(1, 6*j+1, 6*j+6)); // la fila que copio
            for (int i = 1; i <= 6; i++) {
                Phi(i, j) = yPhiAux(1, i); // la columna que copio
            }
        }
        std::cout << "Phi actualizado para la observacion " << i << std::endl;

        neqn = 6;
        yArr = new double[neqn];
        work = new double[100 + 21 * neqn];
        for(int j=0; j<5; j++)
        {
            iwork[j] = 0;
        }
        Y.trueCopy(DEInteg(Accel, 0, t-t_old, 1e-13, 1e-6, neqn, Y_old, yArr, work, iwork));
        std::cout << "DEInteg(Accel) ejecutado para la observacion " << i << std::endl;
        std::cout << "Y (" << i << "): " << std::endl << Y.transpose() << std::endl;

        // Topocentric coordinates
        theta = gmst(Mjd_UT1);                    // Earth rotation
        U.copy(R_z(theta));
        r.trueCopy(Y.subvectorFromRow(1, 1, 3));
    
        s.copy((LT*(U*r.transpose()-Rs)).transpose());                  // Topocentric position [m]

        std::cout << "U (" << i << "): " << std::endl << U << std::endl;
        std::cout << "r (" << i << "): " << std::endl << r << std::endl;
        std::cout << "s (" << i << "): " << std::endl << s << std::endl;

        // Time update
        P.trueCopy(TimeUpdate(P, Phi, 0.0));
        std::cout << "TimeUpdate ejecutado para la observacion " << i << std::endl;
        std::cout << "P_TimeUpdate (" << i << "): " << std::endl << P << std::endl;

        // Azimuth and partials
        AzElPa(s, Azim, Elev, dAds, dEds);        // Azimuth, Elevation
        std::cout << "AzElPa ejecutado para la observacion " << i << std::endl;
        std::cout << "Azim (" << i << "): " << Azim << std::endl;
        std::cout << "Elev (" << i << "): " << Elev << std::endl;
        std::cout << "dAds (" << i << "): " << std::endl << dAds << std::endl;
        std::cout << "dEds (" << i << "): " << std::endl << dEds << std::endl;

        dAdY.trueCopy(Matrix::concatenateRows(dAds*LT*U, Matrix::zeros(1, 3)));
        std::cout << "dAdY (" << i << "): " << std::endl << dAdY << std::endl;

        // Measurement update
        std::cout << "MeasUpdate (Azim) comienza para la observacion " << i << std::endl;
        MeasUpdate(obs(i, 2), Azim, sigma_az, dAdY, P, 6, K, Y);
        std::cout << "MeasUpdate (Azim) ejecutado para la observacion " << i << std::endl;
        std::cout << "Y_measUpdate1 (" << i << "): " << std::endl << Y.transpose() << std::endl;
        std::cout << "P_measUpdate1 (" << i << "): " << std::endl << P << std::endl;
        std::cout << "K_measUpdate1 (" << i << "): " << std::endl << K << std::endl;

        // Elevation and partials
        r.trueCopy(Y.subvectorFromRow(1, 1, 3));
        s.copy((LT*(U*r.transpose()-Rs)).transpose());                  // Topocentric position [m]
        AzElPa(s, Azim, Elev, dAds, dEds);        // Azimuth, Elevation

        dEdY.trueCopy(Matrix::concatenateRows(dEds*LT*U, Matrix::zeros(1, 3)));
        std::cout << "dEdY (" << i << "): " << std::endl << dEdY << std::endl;

        // Measurement update
        std::cout << "MeasUpdate (Elev) comienza para la observacion " << i << std::endl;
        MeasUpdate(obs(i,3), Elev, sigma_el, dEdY, P, 6, K, Y);
        std::cout << "MeasUpdate (Elev) ejecutado para la observacion " << i << std::endl;
        std::cout << "Y_measUpdate2 (" << i << "): " << std::endl << Y.transpose() << std::endl;
        std::cout << "P_measUpdate2 (" << i << "): " << std::endl << P << std::endl;
        std::cout << "K_measUpdate2 (" << i << "): " << std::endl << K << std::endl;

        // Range and partials
        r.trueCopy(Y.subvectorFromRow(1, 1, 3));
        s.copy((LT*(U*r.transpose()-Rs)).transpose());                  // Topocentric position [m]
        Dist = s.norm(); 
        dDds.copy(s/Dist);      // Range
        dDdY.trueCopy(Matrix::concatenateRows(dDds*LT*U, Matrix::zeros(1, 3)));
        std::cout << "dDdY (" << i << "): " << std::endl << dDdY << std::endl;

        // Measurement update
        std::cout << "MeasUpdate (Dist) comienza para la observacion " << i << std::endl;
        MeasUpdate(obs(i,4), Dist, sigma_range, dDdY, P, 6, K, Y);
        std::cout << "MeasUpdate (Dist) ejecutado para la observacion " << i << std::endl;
        std::cout << "Y_measUpdate3 (" << i << "): " << std::endl << Y.transpose() << std::endl;
        std::cout << "P_measUpdate3 (" << i << "): " << std::endl << P << std::endl;
        std::cout << "K_measUpdate3 (" << i << "): " << std::endl << K << std::endl;

        std::cout << "He llegado hasta la observacion " << i << std::endl;
    }
    std::cout << "He llegado hasta el final del bucle de observaciones" << std::endl;

    IERS(eopdata, obs(46,1), 'l', x_pole, y_pole, UT1_UTC, LOD, dpsi, deps, dx_pole, dy_pole, TAI_UTC);
    timediff(UT1_UTC, TAI_UTC, UT1_TAI, UTC_GPS, UT1_GPS, TT_UTC, GPS_UTC);
    Mjd_TT = Mjd_UTC + TT_UTC/86400.0;
    Global::AuxParam.Mjd_UTC = Mjd_UTC;
    Global::AuxParam.Mjd_TT = Mjd_TT;

    neqn = 6;
    yArr = new double[neqn];
    work = new double[100 + 21 * neqn];
    for(int j=0; j<5; j++)
    {
        iwork[j] = 0;
    }
    Matrix Y0 = DEInteg(Accel, 0, -(obs(46,1)-obs(1,1))*86400.0, 1e-13, 1e-6, neqn, Y, yArr, work, iwork);

    Matrix Y_true = Matrix(1, 6);
    Y_true(1, 1) = 5753.173e3;
    Y_true(1, 2) = 2673.361e3;
    Y_true(1, 3) = 3440.304e3;
    Y_true(1, 4) = 4.324207e3;
    Y_true(1, 5) = -1.924299e3;
    Y_true(1, 6) = -5.728216e3;
    
    std::cout << "\nError of Position Estimation" << std::endl;
    std::cout << "dX\t" << Y0(1, 1)-Y_true(1, 1) << "\t[m]" << std::endl;
    std::cout << "dY\t" << Y0(1, 2)-Y_true(1, 2) << "\t[m]" << std::endl;
    std::cout << "dZ\t" << Y0(1, 3)-Y_true(1, 3) << "\t[m]" << std::endl;
    std::cout << "\nError of Velocity Estimation" << std::endl;
    std::cout << "dVx\t" << Y0(1, 4)-Y_true(1, 4) << "\t[m/s]" << std::endl;
    std::cout << "dVy\t" << Y0(1, 5)-Y_true(1, 5) << "\t[m/s]" << std::endl;
    std::cout << "dVz\t" << Y0(1, 6)-Y_true(1, 6) << "\t[m/s]" << std::endl;
}