#include <iostream>
#include <exception>
#include <cstdlib>
#include <vector>

#ifndef __MATRIX__
#define __MATRIX__

/* ******************************************************** */
/* Examples */
/* ******************************************************** */
/*
    A#
    int v1[4][1] = { {1}, {-3}, {2}, {4} };
    Matrix x(MatrixFactory<4,1>(v1));

    B#
    Matrix z(3,3); z.fill(0);
*/

namespace linalg 
    {
    /* ******************************************************** */
    /* Exceptions */
    /* ******************************************************** */

    class OutOfBounds: public std::exception { virtual const char* what() const throw(); };

    class LeastSquare: public std::exception { virtual const char* what() const throw(); };

    class Multiplication: public std::exception { virtual const char* what() const throw(); };

    /* ******************************************************** */
    /* CLASS Matrix */
    /* ******************************************************** */
    class Matrix
        {
    public:
        
        /**
        * Create a matrix
        */
        Matrix(int rows, int cols);
        Matrix(const Matrix &m);

        ~Matrix() {};

        /** 
         * Multiplication with scalar 
         * Multiplication
         * Addition
         * Substraction
         */
        operator*(double v);
        operator+(double v);
        operator*(const Matrix &m) throw();
        operator+(const Matrix &m);
        operator-(const Matrix &m);
        operator=(const Matrix &m);
        /**
         * Row operations
         */
        void row_scalar_multiplication(int row, double value);
        void row_addition_multilpum(int rowA, int rowB, int times, char isAddition);
        void row_move(int fromRow, int toRow);

        /**
         * Helper functions
         */
        void fill(double value);
        void transpose();
        void set_value(int row, int col, double value) throw();
        double get_value(int row, int col) throw();
        void pretty_print();

        std::vector<std::vector<double> > data;
        int rows; int cols;

    private:
        
        const OutOfBounds outofbounds;
        const LeastSquare leastsquare;
        const Multiplication multiplication;
        
        };

    /* ******************************************************** */
    /* Matrix factory */
    /* ******************************************************** */

    template <int rows, int cols>
    Matrix MatrixFactory(double (&data)[rows][cols])
        {
        Matrix m(rows, cols);
        for(int i = 0; i < rows; i++)
            {
            m.data.push_back(std::vector<double>());
            m.data[m.data.size()-1].assign(data[i], data[i]+cols);
            }
        return m;
        };

    /* ******************************************************** */
    /* Exceptions */
    /* ******************************************************** */

    inline const char* OutOfBounds::what() const throw()
        {
        return "Matrix.cpp: Out of bounds";
        };

    inline const char* LeastSquare::what() const throw()
        {
        return "Matrix.cpp: Any matrix should atleast be 1 by 1";
        };

    inline const char* Multiplication::what() const throw()
        {
        return "Matrix.cpp: (Matrix A) columnsize == (Matrix B) rowsize.";
        };
    };



#endif