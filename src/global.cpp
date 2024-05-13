//$Source$
//------------------------------------------------------------------------------
// Global:Global
//------------------------------------------------------------------------------
// Global es una clase que implementa el acceso a los datos del fichero
// ../data/eop19620101.txt, mediante una matriz.
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
}