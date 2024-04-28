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

//------------------------------------------------------------------------------
// void Global::eop19620101(int c)
//------------------------------------------------------------------------------
/**
 * @brief Función que lee c líneas del fichero eop19620101.txt y las almacena en
 * la matriz eopdata.
 * @param c Número de líneas a leer.
 * @return void
 */
//------------------------------------------------------------------------------
void Global::eop19620101(int c) // poner bien el nombre
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