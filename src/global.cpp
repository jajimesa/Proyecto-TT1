//$Source$
//------------------------------------------------------------------------------
// Global:Global
//------------------------------------------------------------------------------
// Global es una clase que implementa el acceso a los datos del los diversos
// ficheros de datos que se utilizan en el programa.
//------------------------------------------------------------------------------
/**
 * @author Javier Jiménez Santana
 * @date 24/04/2024
 * @brief Acceso a los datos del fichero ../data/eop19620101.txt.
 */
//------------------------------------------------------------------------------

#include "../include/global.hpp"

Matrix *Global::eopdata;
Matrix *Global::Cnm;
Matrix *Global::Snm;
Matrix *Global::PC;
Matrix *Global::obs;
Param Global::AuxParam;

//------------------------------------------------------------------------------
// void Global::initAuxParam()
//------------------------------------------------------------------------------
/**
 * @brief Inicializa la estructura AuxParam con algunos de los valores que se
 * necesitan para testear la función Accel, a partir del fichero principal.
 */
//------------------------------------------------------------------------------
void Global::initAuxParam()
{
    Global::AuxParam.Mjd_UTC = 49746.1112847221;
    Global::AuxParam.Mjd_TT = 0;
    Global::AuxParam.n = 20;
    Global::AuxParam.m = 20;
    Global::AuxParam.sun = 1;
    Global::AuxParam.moon = 1;
    Global::AuxParam.planets = 1;
}

//------------------------------------------------------------------------------
// void Global::eop19620101(int c)
//------------------------------------------------------------------------------
/**
 * @brief Función que lee c columnas del fichero eop19620101.txt y las almacena en
 * la matriz eopdata. c como máximo 21413.
 * @param c Número de líneas a leer.
 */
//------------------------------------------------------------------------------
void Global::eop19620101(int c = 21413) // poner bien el nombre
{
    Global::eopdata = new Matrix(13, c);
    FILE *fid = fopen("../data/eop19620101.txt", "r");
    if(fid == NULL)
    {
        printf("Error: No se ha podido abrir el fichero eop19620101.txt\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i <= c; i++) {
        fscanf(fid,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf",
            &((*Global::eopdata)(1,i)),
            &((*Global::eopdata)(2,i)),
            &((*Global::eopdata)(3,i)),
            &((*Global::eopdata)(4,i)),
            &((*Global::eopdata)(5,i)),
            &((*Global::eopdata)(6,i)),
            &((*Global::eopdata)(7,i)),
            &((*Global::eopdata)(8,i)),
            &((*Global::eopdata)(9,i)),
            &((*Global::eopdata)(10,i)),
            &((*Global::eopdata)(11,i)),
            &((*Global::eopdata)(12,i)),
            &((*Global::eopdata)(13,i)));
    }
    fclose(fid);
}

//------------------------------------------------------------------------------
// void Global::GGM03S(int c)
//------------------------------------------------------------------------------
/**
 * @brief Función que lee c líneas del fichero GGM03S.txt y las almacena en
 * las matrices Cnm y Snm. c como máximo 181.
 * @param c Número de líneas a leer.
 */
//------------------------------------------------------------------------------
void Global::GGM03S(int c = 181)
{
    Global::Cnm = new Matrix(c, 181);
    Global::Snm = new Matrix(c, 181);

    FILE *fid = fopen("../data/GGM03S.txt", "r");
    if(fid == NULL)
    {
        printf("Error: No se ha podido abrir el fichero GGM03S.txt\n");
        exit(EXIT_FAILURE);
    }

    Matrix temp(1,6);
    for(int n=1; n<=c; n++)
    {
        for(int m=1; m<=n; m++)
        {
            fscanf(fid, "%lf %lf %lf %lf %lf %lf", 
                &temp(1,1),
                &temp(1,2),
                &temp(1,3),
                &temp(1,4),
                &temp(1,5),
                &temp(1,6));

            (*Global::Cnm)(n, m) = temp(1, 3);
            (*Global::Snm)(n, m) = temp(1, 4);
        }
    }
    fclose(fid);
}

//------------------------------------------------------------------------------
// void Global::DE430Coeff(int c)
//------------------------------------------------------------------------------
/**
 * @brief Función que lee c líneas del fichero DE430Coeff.txt y las almacena en
 * la matriz PC. c como máximo 2285.
 * @param c Número de líneas a leer.
 */
//------------------------------------------------------------------------------
void Global::DE430Coeff(int c = 1020)
{
    Global::PC = new Matrix(c, 1020);
    
    FILE *fid = fopen("../data/DE430Coeff.txt", "r");
    if(fid == NULL)
    {
        printf("Error: No se ha podido abrir el fichero DE430Coeff.txt\n");
        exit(EXIT_FAILURE);
    }

    Matrix temp(1,6);
    for(int n=1; n<=c; n++)
    {
        for(int m=1; m<=1020; m=m+6)
        {
            fscanf(fid, "%lf %lf %lf %lf %lf %lf", 
                &temp(1,1),
                &temp(1,2),
                &temp(1,3),
                &temp(1,4),
                &temp(1,5),
                &temp(1,6));

            (*Global::PC)(n, m    ) = temp(1, 1);
            (*Global::PC)(n, m + 1) = temp(1, 2);
            (*Global::PC)(n, m + 2) = temp(1, 3);
            (*Global::PC)(n, m + 3) = temp(1, 4);
            (*Global::PC)(n, m + 4) = temp(1, 5);
            (*Global::PC)(n, m + 5) = temp(1, 6);
        }
    }
    fclose(fid);
}

//------------------------------------------------------------------------------
// void Global::GEOMS3()
//------------------------------------------------------------------------------
/**
 * @brief Función que lee el fichero GEOS3.txt y almacena los datos en la 
 * matriz obs.
 */
//------------------------------------------------------------------------------
void Global::GEOMS3()
{
    int nobs = 46;
    Global::obs = new Matrix(nobs, 4);
    FILE *fid = fopen("../data/GEOS3.txt", "r");
    if(fid == NULL)
    {
        printf("Error: No se ha podido abrir el fichero GEOS3.txt\n");
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<nobs; i++)
    {
        char tline[100];
        if(fgets(tline, sizeof(tline), fid) == NULL)
            break;

        int Y = atoi(std::string(tline).substr(0, 4).c_str());
        int M = atoi(std::string(tline).substr(5, 2).c_str());
        int D = atoi(std::string(tline).substr(8, 2).c_str());
        int h = atoi(std::string(tline).substr(12, 2).c_str());
        int m = atoi(std::string(tline).substr(15, 2).c_str());
        double s = atof(std::string(tline).substr(18, 6).c_str());
        double az = atof(std::string(tline).substr(25, 8).c_str());
        double el = atof(std::string(tline).substr(35, 7).c_str());
        double Dist = atof(std::string(tline).substr(44, 10).c_str());

        (*Global::obs)(i+1, 1) = Mjday(Y, M, D, h, m, s);
        (*Global::obs)(i+1, 2) = Const::Rad * az;
        (*Global::obs)(i+1, 3) = Const::Rad * el;
        (*Global::obs)(i+1, 4) = 1e3 * Dist;

        //std::cout << "Observacion " << i << " leida correctamente." << std::endl;
    }
    fclose(fid);
}