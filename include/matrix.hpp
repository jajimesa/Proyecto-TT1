//$Header$
//------------------------------------------------------------------------------
// Matrix
//------------------------------------------------------------------------------
// Matrix: una librería sencilla para hacer operaciones con matrices en C++.
//
// **Aviso legal: esta librería fue concebida para el proyecto de TT1 en C++.**
/**
 * @author Javier Jiménez Santana
 * @date 18/04/2024
 * @brief Librería para hacer operaciones con matrices en C++.
 */
//------------------------------------------------------------------------------

#ifndef _MATRIX_
#define _MATRIX_

#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

class Matrix {
    public:
        int n_row, n_column;
        double **data;

        // Precisión para comparar números de punto flotante
        double const epsilon = 1e-3;

        // Constructor de matriz (inicializa con ceros)
        Matrix(int n_row, int n_column);

        // Constructor de matriz (inicializa con datos)
        Matrix(int n_row, int n_column, double **data);

        // Funciones de la clase Matrix
        static Matrix zeros(int n_row, int n_column);
        double dot(const Matrix &m);
        Matrix cross(const Matrix &m);
        double norm() const;
        static double norm(const Matrix &m);
        double det() const;
        static double det(const Matrix &m);
        Matrix transpose();
        static Matrix transpose(Matrix &m);
        Matrix adjoint() const;
        Matrix inverse(); 
        static Matrix inverse(Matrix &m);
        static Matrix eye(int n);
        Matrix row(int i) const;
        Matrix column(int j) const;
        Matrix subvectorFromRow(int row, int startIndex, int endIndex) const;
        static Matrix concatenateRows(const Matrix &m1, const Matrix &m2);

        // Operadores miembros
        double& operator () (int row, int column);
        Matrix& operator + (const Matrix &m);
        Matrix& operator + (const double scalar);
        Matrix& operator - (const Matrix &m);
        Matrix& operator - (const double scalar);
        Matrix& operator * (const double scalar);
        Matrix& operator / (const double scalar);
        Matrix& operator * (const Matrix &m);
        bool operator == (const Matrix &m);
        bool equals(const Matrix &m, double epsilon);
        Matrix& copy(const Matrix &m);
        Matrix& trueCopy(const Matrix &m);
        
        // Operadores no miembros
        friend ostream& operator << (ostream &os, const Matrix &m);
};

ostream& operator << (ostream &os, const Matrix &m);

#endif