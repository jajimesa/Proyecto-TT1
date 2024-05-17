//$Source$
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

#include "../include/matrix.hpp"

//------------------------------------------------------------------------------
// Matrix(int n_row, int n_column)
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 *
 * @param n_row [in] número de filas mayor
 * @param n_column [in] número de columnas
 * @return una matriz de ceros dimensión n_row x n_column
 */
//------------------------------------------------------------------------------
Matrix::Matrix(int n_row, int n_column)
{
    this->n_row = n_row;
    this->n_column = n_column;
    this->data = new double *[n_row];
    for (int i = 0; i < n_row; ++i)
    {
        data[i] = new double[n_column];
        for (int j = 0; j < n_column; ++j)
        {
            data[i][j] = 0.0;
        }
    }
}

//------------------------------------------------------------------------------
// Matrix(int n_row, int n_column, double **data)
//------------------------------------------------------------------------------
/**
 * @brief Constructor.
 *
 * @param n_row [in] número de filas.
 * @param n_column [in] número de columnas.
 * @param data [in] datos de la matriz.
 * @return una matriz con los datos proporcionados.
 */
//------------------------------------------------------------------------------
Matrix::Matrix(int n_row, int n_column, double **data)
{
    this->n_row = n_row;
    this->n_column = n_column;
    this->data = data;
}

//------------------------------------------------------------------------------
// Matrix zeros(int n_row, int n_column)
//------------------------------------------------------------------------------
/**
 * @brief Crea una matriz de ceros.
 *
 * @param n_row [in] número de filas.
 * @param n_column [in] número de columnas.
 * @return una matriz de ceros dimensión n_row x n_column.
 */
//------------------------------------------------------------------------------
Matrix Matrix::zeros(int n_row, int n_column)
{
    Matrix zero_matrix(n_row, n_column);
    return zero_matrix;
}

//------------------------------------------------------------------------------
// double Matrix::dot(const Matrix &m)
//------------------------------------------------------------------------------
/**
 * @brief Calcula el producto escalar de la matriz fila sobre la que se invoca
 * con la matriz fila m.
 *
 * @param m [in] matriz fila con la que se va a hacer el producto punto.
 * @return el producto punto de las matrices.
 */
//------------------------------------------------------------------------------
double Matrix::dot(const Matrix &m)
{
    assert(n_row == 1 && m.n_row == 1 && n_column == m.n_column 
            && "Matrices must be row vectors of the same size");
    double result = 0.0;
    for (int i = 0; i < n_column; ++i)
    {
        result += data[0][i] * m.data[0][i];
    }
    return result;
}

//------------------------------------------------------------------------------
// Matrix Matrix::cross(const Matrix &m)
//------------------------------------------------------------------------------
/**
 * @brief Calcula el producto vectorial de la matriz fila sobre la que se invoca
 * con la matriz fila m.
 *
 * @param m [in] matriz fila con la que se va a hacer el producto cruz.
 * @return el producto cruz de las matrices.
 */
//------------------------------------------------------------------------------
Matrix Matrix::cross(const Matrix &m)
{
    assert(n_row == 1 && m.n_row == 1 && n_column == 3 && m.n_column == 3
            && "Matrices must be row vectors of size 3");
    Matrix result = Matrix(1, 3);
    result.data[0][0] = data[0][1] * m.data[0][2] - data[0][2] * m.data[0][1];
    result.data[0][1] = data[0][2] * m.data[0][0] - data[0][0] * m.data[0][2];
    result.data[0][2] = data[0][0] * m.data[0][1] - data[0][1] * m.data[0][0];
    return result;
}

//------------------------------------------------------------------------------
// Matrix Matrix::eye(int n)
//------------------------------------------------------------------------------
/**
 * @brief Crea una matriz identidad.
 *
 * @param n [in] tamaño de la matriz identidad.
 * @return una matriz identidad de tamaño n x n.
 */
//------------------------------------------------------------------------------
Matrix Matrix::eye(int n)
{
    Matrix identity = Matrix(n, n);
    for (int i = 0; i < n; ++i)
    {
        identity.data[i][i] = 1.0;
    }
    return identity;
}

//------------------------------------------------------------------------------
// double Matrix::det() const
//------------------------------------------------------------------------------
/**
 * @brief Calcula el determinante de la matriz sobre la que se invoca.
 *
 * @return el determinante de la matriz.
 */
//------------------------------------------------------------------------------
double Matrix::det() const
{
    assert(this->n_row == this->n_column && "Matrix must be square");

    if (this->n_row == 1)
    {
        return this->data[0][0];
    }

    double determinant = 0.0;
    Matrix submatrix(this->n_row - 1, this->n_column - 1);

    for (int i = 0; i < this->n_column; ++i)
    {
        int sub_i = 0;
        for (int row = 1; row < this->n_row; ++row)
        {
            int sub_j = 0;
            for (int column = 0; column < this->n_column; ++column)
            {
                if (column == i)
                    continue;
                submatrix.data[sub_i][sub_j] = this->data[row][column];
                ++sub_j;
            }
            ++sub_i;
        }

        double sign = (i % 2 == 0) ? 1 : -1;
        double minor_det = submatrix.det();
        determinant += sign * this->data[0][i] * minor_det;
    }

    return determinant;
}

//------------------------------------------------------------------------------
// double Matrix::det(const Matrix &m)
//------------------------------------------------------------------------------
/**
 * @brief Calcula el determinante de la matriz m (versión estática del método).
 *
 * @param m [in] matriz de la que se va a calcular el determinante.
 * @return el determinante de la matriz.
 */
//------------------------------------------------------------------------------
double Matrix::det(const Matrix &m)
{
    return m.det();
}

//------------------------------------------------------------------------------
// double Matrix::norm() const
//------------------------------------------------------------------------------
/**
 * @brief Calcula la norma de la matriz sobre la que se invoca.
 *
 * @return la norma de la matriz.
 */
//------------------------------------------------------------------------------
double Matrix::norm() const
{
    assert((n_row == 1 || n_column == 1) && "Matrix must be a row or column vector");
    double norm = 0.0;
    if (n_row == 1)
    {
        for (int i = 0; i < n_column; ++i)
        {
            norm += data[0][i] * data[0][i];
        }
    }
    if (n_column == 1)
    {
        for (int i = 0; i < n_row; ++i)
        {
            norm += data[i][0] * data[i][0];
        }
    }
    return sqrt(norm);
}

//------------------------------------------------------------------------------
// double Matrix::norm(const Matrix &m)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la norma de la matriz m (versión estática del método).
 *
 * @param m [in] matriz de la que se va a calcular la norma.
 * @return la norma de la matriz.
 */
//------------------------------------------------------------------------------
double Matrix::norm(const Matrix &m)
{
    return m.norm();
}

//------------------------------------------------------------------------------
// Matrix Matrix::transpose()
//------------------------------------------------------------------------------
/**
 * @brief Calcula la transpuesta de la matriz sobre la que se invoca.
 *
 * @return la transpuesta de la matriz.
 */
//------------------------------------------------------------------------------
Matrix Matrix::transpose()
{
    if (n_row == 1) {
        // Caso especial: matriz fila
        Matrix transposed = Matrix(n_column, 1);
        for (int i = 0; i < n_column; ++i)
        {
            transposed.data[i][0] = data[0][i];
        }
        return transposed;
    } else if (n_column == 1) {
        // Caso especial: matriz columna
        Matrix transposed = Matrix(1, n_row);
        for (int i = 0; i < n_row; ++i)
        {
            transposed.data[0][i] = data[i][0];
        }
        return transposed;
    } else {
        // Caso general: matriz cuadrada o rectangular
        Matrix transposed = Matrix(n_column, n_row);
        for (int i = 0; i < n_row; ++i)
        {
            for (int j = 0; j < n_column; ++j)
            {
                transposed.data[j][i] = data[i][j];
            }
        }
        return transposed;
    }
}

//------------------------------------------------------------------------------
// Matrix Matrix::transpose(Matrix &m)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la transpuesta de la matriz m (versión estática del método).
 *
 * @param m [in] matriz a la que se le va a calcular la transpuesta.
 * @return la transpuesta de la matriz.
 */
//------------------------------------------------------------------------------
Matrix Matrix::transpose(Matrix &m)
{
    return m.transpose();
}

//------------------------------------------------------------------------------
// Matrix Matrix::adjoint() const
//------------------------------------------------------------------------------
/**
 * @brief Calcula la adjunta de la matriz sobre la que se invoca (método
 * auxiliar para calcular la inversa de una matriz).
 *
 * @return la adjunta de la matriz.
 */
//------------------------------------------------------------------------------
Matrix Matrix::adjoint() const
{
    assert(this->n_row == this->n_column && "Matrix must be square");

    Matrix adj(this->n_row, this->n_column);

    for (int i = 0; i < this->n_row; ++i)
    {
        for (int j = 0; j < this->n_column; ++j)
        {
            Matrix submatrix(this->n_row - 1, this->n_column - 1);

            int sub_i = 0;
            for (int row = 0; row < this->n_row; ++row)
            {
                if (row == i)
                    continue;

                int sub_j = 0;
                for (int column = 0; column < this->n_column; ++column)
                {
                    if (column == j)
                        continue;

                    submatrix.data[sub_i][sub_j] = this->data[row][column];
                    ++sub_j;
                }
                ++sub_i;
            }

            double sign = ((i + j) % 2 == 0) ? 1 : -1;
            double minor_det = submatrix.det();
            adj.data[j][i] = sign * minor_det;
        }
    }

    return adj;
}

//------------------------------------------------------------------------------
// Matrix Matrix::inverse()
//------------------------------------------------------------------------------
/**
 * @brief Calcula la inversa de la matriz sobre la que se invoca.
 *
 * @return la inversa de la matriz.
 */
//------------------------------------------------------------------------------
Matrix Matrix::inverse()
{
    assert(this->n_row == this->n_column && "Matrix must be square");
    assert(this->det() != 0 && "Matrix must be invertible");

    double determinant = this->det();
    Matrix adjoint = this->adjoint();
    return adjoint / determinant;
}

//------------------------------------------------------------------------------
// Matrix Matrix::inverse(Matrix &m)
//------------------------------------------------------------------------------
/**
 * @brief Calcula la inversa de la matriz m (versión estática del método).
 *
 * @param m [in] matriz de la que se va a calcular la inversa.
 * @return la inversa de la matriz.
 */
//------------------------------------------------------------------------------
Matrix inverse(Matrix &m)
{
    return m.inverse();
}

Matrix Matrix::row(int i) const
{
    assert(i >= 1 && i <= n_row && "Row index out of bounds");

    Matrix row_matrix(1, n_column);
    for (int j = 0; j < n_column; ++j)
    {
        row_matrix.data[0][j] = data[i - 1][j];
    }
    return row_matrix;
}

//------------------------------------------------------------------------------
// Matrix Matrix::column(int j) const
//------------------------------------------------------------------------------
/**
 * @brief Obtiene una columna de la matriz.
 *
 * @param j [in] índice de la columna.
 * @return la columna j de la matriz.
 */
//------------------------------------------------------------------------------
Matrix Matrix::column(int j) const
{
    assert(j >= 1 && j <= n_column && "Column index out of bounds");

    Matrix column_matrix(n_row, 1);
    for (int i = 0; i < n_row; ++i)
    {
        column_matrix.data[i][0] = data[i][j - 1];
    }
    return column_matrix;
}

//------------------------------------------------------------------------------
// Matrix Matrix::subvectorFromRow(int row, int startIndex, int endIndex) const
//------------------------------------------------------------------------------
/**
 * @brief Obtiene un subvector de la matriz a partir de una fila y dos índices
 * ambos inclusives. Si los índices están fuera del rango, se ajustan como en
 * Matlab.
 *
 * @param row [in] fila a partir de la que se va a extraer el subvector.
 * @param startIndex [in] índice de inicio del subvector.
 * @param endIndex [in] índice de fin del subvector.
 * @return el subvector de la matriz.
 */
//------------------------------------------------------------------------------
Matrix Matrix::subvectorFromRow(int row, int startIndex, int endIndex) const
{
     assert(row >= 1 && row <= n_row && "Row index out of bounds");

    // Ajusto los índices si están fuera del rango, como en Matlab
    if (startIndex < 1) startIndex = 1;
    if (endIndex > n_column) endIndex = n_column;

    // Verifico que el índice de inicio sea menor o igual al índice final
    assert(startIndex <= endIndex && "Start index must be less than or equal to end index");

    Matrix subvector(1, endIndex - startIndex + 1);
    for (int i = 0; i < endIndex - startIndex + 1; i++)
    {
        subvector.data[0][i] = data[row - 1][startIndex - 1 + i];
    }
    return subvector;
}

//------------------------------------------------------------------------------
// Matrix Matrix::concatenateRows(const Matrix &m1, const Matrix &m2)
//------------------------------------------------------------------------------
Matrix Matrix::concatenateRows(const Matrix &m1, const Matrix &m2) 
{
    assert(m1.n_row == m2.n_row && "Matrices must have the same number of rows for concatenation");

    int new_n_column = m1.n_column + m2.n_column;
    Matrix concatenated(m1.n_row, new_n_column);

    // Copio los datos de la primera matriz en la matriz concatenada
    for (int i = 0; i < m1.n_row; i++) {
        for (int j = 0; j < m1.n_column; j++) {
            concatenated.data[i][j] = m1.data[i][j];
        }
    }

    // Copio los datos de la segunda matriz en la matriz concatenada
    for (int i = 0; i < m2.n_row; i++) {
        for (int j = 0; j < m2.n_column; j++) {
            concatenated.data[i][m1.n_column + j] = m2.data[i][j];
        }
    }

    return concatenated;
}

//------------------------------------------------------------------------------
// void matrixToDoubleArray(const Matrix& mat, double* arr)
//------------------------------------------------------------------------------
/**
 * @brief Convierte una matriz en un array de doubles.
 * @param mat Matriz a convertir.
 * @param arr [out] Array de salida.
 */
//------------------------------------------------------------------------------
void Matrix::matrixToDoubleArray(const Matrix& mat, double* arr) {
    int idx = 0;
    for (int i = 0; i < mat.n_row; i++) {
        for (int j = 0; j < mat.n_column; j++) {
            arr[idx] = mat.data[i][j];
            idx++;
        }
    }
}

//------------------------------------------------------------------------------
// Matrix doubleArrayToMatrix(const double* arr, int n_row, int n_column)
//------------------------------------------------------------------------------
/**
 * @brief Convierte un array de doubles en una matriz.
 * @param arr Array a convertir.
 * @param n_row Número de filas de la matriz.
 * @param n_column Número de columnas de la matriz.
 * @return Matriz resultante.
 */
//------------------------------------------------------------------------------
Matrix Matrix::doubleArrayToMatrix(const double* arr, int n_row, int n_column) {
    Matrix mat(n_row, n_column);
    int idx = 0;
    for (int i = 1; i <= n_row; ++i) {
        for (int j = 1; j <= n_column; ++j) {
            mat(i, j) = arr[idx];
            idx++;
        }
    }
    return mat;
}

//------------------------------------------------------------------------------
// double& Matrix::operator () (int row, int column)
//------------------------------------------------------------------------------
/**
 * @brief Sobrecarga del operador de acceso a elementos de la matriz para que se
 * comporte como una matriz de Matlab.
 *
 * @param row [in] índice de la fila.
 * @param column [in] índice de la columna.
 * @return el elemento de la matriz en la fila row y columna column.
 */
//------------------------------------------------------------------------------
double &Matrix::operator()(int row, int column)
{
    assert(row >= 1 && row <= n_row && "Row index out of bounds");
    assert(column >= 1 && column <= n_column && "Column index out of bounds");
    return data[row - 1][column - 1];
}

//------------------------------------------------------------------------------
// Matrix& Matrix::operator + (Matrix const &m)
//------------------------------------------------------------------------------
/**
 * @brief Sobrecarga del operador de suma de matrices.
 *
 * @param m [in] matriz a sumar.
 * @return la suma de las matrices.
 */
//------------------------------------------------------------------------------
Matrix &Matrix::operator+(Matrix const &m)
{
    assert(this->n_row == m.n_row && this->n_column == m.n_column
            && "Matrices must have the same dimensions");

    Matrix *result = new Matrix(this->n_row, this->n_column);
    for (int i = 0; i < this->n_row; i++)
    {
        for (int j = 0; j < this->n_column; j++)
        {
            result->data[i][j] = this->data[i][j] + m.data[i][j];
        }
    }
    return *result;
}

//------------------------------------------------------------------------------
// Matrix& Matrix::operator + (double scalar)
//------------------------------------------------------------------------------
/**
 * @brief Sobrecarga del operador de suma de un escalar a una matriz.
 *
 * @param scalar [in] escalar a sumar.
 * @return la matriz sumada con el escalar.
 */
//------------------------------------------------------------------------------
Matrix &Matrix::operator+(double scalar)
{
    Matrix *result = new Matrix(this->n_row, this->n_column);
    for (int i = 0; i < this->n_row; i++)
    {
        for (int j = 0; j < this->n_column; j++)
        {
            result->data[i][j] = this->data[i][j] + scalar;
        }
    }
    return *result;
}

//------------------------------------------------------------------------------
// Matrix& Matrix::operator - (Matrix const &m)
//------------------------------------------------------------------------------
/**
 * @brief Sobrecarga del operador de resta de matrices.
 *
 * @param m [in] matriz a restar.
 * @return la resta de las matrices.
 */
//------------------------------------------------------------------------------
Matrix &Matrix::operator-(Matrix const &m)
{
    assert(this->n_row == m.n_row && this->n_column == m.n_column
            && "Matrices must have the same dimensions");

    Matrix *result = new Matrix(this->n_row, this->n_column);
    for (int i = 0; i < this->n_row; i++)
    {
        for (int j = 0; j < this->n_column; j++)
        {
            result->data[i][j] = this->data[i][j] - m.data[i][j];
        }
    }
    return *result;
}

//------------------------------------------------------------------------------
// Matrix& Matrix::operator - (double scalar)
//------------------------------------------------------------------------------
/**
 * @brief Sobrecarga del operador de resta de un escalar a la matriz.
 *
 * @param scalar [in] escalar a restar.
 * @return la matriz con el escalar restado.
 */
//------------------------------------------------------------------------------
Matrix &Matrix::operator-(double scalar)
{
    Matrix *result = new Matrix(this->n_row, this->n_column);
    for (int i = 0; i < this->n_row; i++)
    {
        for (int j = 0; j < this->n_column; j++)
        {
            result->data[i][j] = this->data[i][j] - scalar;
        }
    }
    return *result;
}

//------------------------------------------------------------------------------
// Matrix& Matrix::operator * (double scalar)
//------------------------------------------------------------------------------
/**
 * @brief Sobrecarga del operador de multiplicación por un escalar.
 *
 * @param scalar [in] escalar por el que se va a multiplicar la matriz.
 * @return la matriz multiplicada por el escalar.
 */
//------------------------------------------------------------------------------
Matrix &Matrix::operator*(double scalar)
{
    Matrix *result = new Matrix(this->n_row, this->n_column);
    for (int i = 0; i < this->n_row; i++)
    {
        for (int j = 0; j < this->n_column; j++)
        {
            result->data[i][j] = this->data[i][j] * scalar;
        }
    }
    return *result;
}

//------------------------------------------------------------------------------
// Matrix& Matrix::operator / (double scalar)
//------------------------------------------------------------------------------
/**
 * @brief Sobrecarga del operador de división por un escalar.
 *
 * @param scalar [in] escalar por el que se va a dividir la matriz.
 * @return la matriz dividida por el escalar.
 */
//------------------------------------------------------------------------------
Matrix &Matrix::operator/(double scalar)
{
    assert(scalar != 0 && "Division by zero");

    Matrix *result = new Matrix(this->n_row, this->n_column);
    for (int i = 0; i < this->n_row; i++)
    {
        for (int j = 0; j < this->n_column; j++)
        {
            result->data[i][j] = this->data[i][j] / scalar;
        }
    }
    return *result;
}

//------------------------------------------------------------------------------
// Matrix& Matrix::operator * (Matrix const &m)
//------------------------------------------------------------------------------
/**
 * @brief Sobrecarga del operador de multiplicación de matrices.
 *
 * @param m [in] matriz a multiplicar.
 * @return el producto de las matrices.
 */
//------------------------------------------------------------------------------
Matrix &Matrix::operator*(Matrix const &m)
{
    assert(this->n_column == m.n_row && "Number of columns of the first matrix must be equal to the number of rows of the second matrix");

    Matrix *result = new Matrix(this->n_row, m.n_column);
    for (int i = 0; i < this->n_row; ++i) {
        for (int j = 0; j < m.n_column; ++j) {
            double sum = 0.0;
            for (int k = 0; k < this->n_column; ++k) {
                sum += this->data[i][k] * m.data[k][j];
            }
            result->data[i][j] = sum;
        }
    }
    return *result;
}

//------------------------------------------------------------------------------
// bool Matrix::operator == (Matrix const &m)
//------------------------------------------------------------------------------
/**
 * @brief Sobrecarga del operador de comparación de matrices.
 *
 * @param m [in] matriz a comparar.
 * @return true si las matrices son iguales, false en caso contrario.
 */
//------------------------------------------------------------------------------
bool Matrix::operator==(Matrix const &m)
{
    if (this->n_row != m.n_row || this->n_column != m.n_column)
    {
        return false;
    }

    for (int i = 0; i < this->n_row; i++)
    {
        for (int j = 0; j < this->n_column; j++)
        {
            if (std::abs(this->data[i][j] - m.data[i][j]) > Matrix::epsilon)
            {
                return false;
            }
        }
    }
    return true;
}

//------------------------------------------------------------------------------
// bool Matrix::equals(Matrix const &m, double epsilon)
//------------------------------------------------------------------------------
/**
 * @brief Compara dos matrices con una tolerancia epsilon. Me obligó a añadirlo
 * porque el método operator== no me permitía cambiar el valor de epsilon, lo
 * cual es necesario según qué tests.
 *
 * @param m [in] matriz a comparar.
 * @param epsilon [in] tolerancia para la comparación.
 * @return true si las matrices son iguales, false en caso contrario.
 */
//------------------------------------------------------------------------------
bool Matrix::equals(Matrix const &m, double epsilon)
{
    if (this->n_row != m.n_row || this->n_column != m.n_column)
    {
        return false;
    }
    for (int i = 0; i < m.n_row; i++)
    {
        for (int j = 0; j < m.n_column; j++)
        {
            if (std::abs(this->data[i][j] - m.data[i][j]) > epsilon)
            {
                return false;
            }
        }
    }
    return true;
}

//------------------------------------------------------------------------------
// Matrix& Matrix::copy(const Matrix &m)
//------------------------------------------------------------------------------
/**
 * @brief Copia una matriz en otra.
 *
 * @param m [in] matriz a copiar.
 * @return la matriz copiada.
 */
//------------------------------------------------------------------------------
Matrix& Matrix::copy(const Matrix &m)
{
    assert(this->n_row == m.n_row && this->n_column == m.n_column && "Matrices must have the same dimensions");
    for (int i = 0; i < m.n_row; i++)
    {
        for (int j = 0; j < m.n_column; j++)
        {
            this->data[i][j] = m.data[i][j];
        }
    }
    return *this;
}

//----------------------------------------------------------------------------------
// Matrix& Matrix::trueCopy(const Matrix &m)
//----------------------------------------------------------------------------------
/**
 * @brief Copia una matriz en otra, incluyendo las dimensiones y los datos.
 * Me he visto obligado a añadir este método porque el método copy, al modificarlo
 * para que cambiara dimensiones y el arreglo de datos, me daba problemas con
 * funciones antiguas que usaban el método copy y ya funcionaban.
 *
 * @param m [in] matriz a copiar.
 * @return la matriz copiada.
 */
//----------------------------------------------------------------------------------
Matrix& Matrix::trueCopy(const Matrix &m)
{
    // Copio las dimensiones de la matriz original
    this->n_row = m.n_row;
    this->n_column = m.n_column;

    // Libero la memoria asignada previamente
    for (int i = 0; i < this->n_row; i++) {
        delete[] this->data[i];
    }
    delete[] this->data;

    // Asigno nueva memoria para los datos
    this->data = new double*[this->n_row];
    for (int i = 0; i < this->n_row; i++) {
        this->data[i] = new double[this->n_column];
    }

    // Copio los datos de la matriz original
    for (int i = 0; i < m.n_row; i++) {
        for (int j = 0; j < m.n_column; j++) {
            this->data[i][j] = m.data[i][j];
        }
    }

    return *this;
}

//------------------------------------------------------------------------------
// ostream& operator << (ostream &os, const Matrix &m)
//------------------------------------------------------------------------------
/**
 * @brief Sobrecarga del operador de impresión de matrices.
 *
 * @param os [in] flujo de salida.
 * @param m [in] matriz a imprimir.
 * @return el flujo de salida con la matriz impresa.
 */
//------------------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const Matrix &m)
{
    for (int i = 0; i < m.n_row; i++)
    {
        for (int j = 0; j < m.n_column; j++)
        {
            os << m.data[i][j] << "\t";
        }
        os << endl;
    }
    return os;
}