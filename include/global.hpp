//$Header$
//------------------------------------------------------------------------------
// Global
//------------------------------------------------------------------------------
/**
 * @file global.hpp
 * @author Javier Jiménez Santana
 * @date 23/04/2024
 */
//------------------------------------------------------------------------------

#ifndef _GLOBAL_
#define _GLOBAL_

#include "matrix.hpp"

class Global {
public:
    static Matrix *eopdata;

    static void eop19620101(int c);
};

#endif