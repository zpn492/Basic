#include "matrix.hpp"

namespace linalg
    {
    /* ******************************************************** */
    /* Operations */
    /* ******************************************************** */

    Matrix::operator*(double v)
        {
        for(int i = 0; i < data.size(); i++)
            {
            for(int j = 0; j < data[i].size(); j++)
                data[i][j] *= v;
            }
        };
    
     Matrix::operator+(double v)
        {
        for(int i = 0; i < data.size(); i++)
            {
            for(int j = 0; j < data[i].size(); j++)
                data[i][j] += v;
            }
        }   

    Matrix::operator*(const Matrix &m) throw()
        {
        try
            {
            if(cols != m.rows)
                throw multiplication;

            Matrix mn(rows, m.cols);  mn.fill(0);
            int n;
            
            for(int i = 0; i < rows; i++)
                {
                for(int j = 0; j < m.cols; j++)
                    {
                    n = 0;
                    for(int k = 0; k < cols; k++)
                        {
                        n += data[i][k] * m.data[k][j];
                        }
                    mn.data[i][j] = n;
                    }
                }
            data = mn.data; rows = mn.rows; cols = mn.cols;
            }
        catch(std::exception& e)
            {
            std::cout << e.what() << " (Matrix A): (" << cols << ")" << " (Matrix B): (" << m.rows << ")" << std::endl;
            std::abort();
            }
        };

    Matrix::operator+(const Matrix &m)
        {
        for(int i = 0; i < m.rows; i++)
            for(int j = 0; j < m.cols; j++)
                data[i][j] += m.data[i][j];
        };

    Matrix::operator-(const Matrix &m)
        {
        for(int i = 0; i < m.rows; i++)
            for(int j = 0; j < m.cols; j++)
                data[i][j] -= m.data[i][j];
        };

    Matrix::operator=(const Matrix &m)
        {
        data = m.data; rows = m.rows; cols = m.cols;
        };

    /* ******************************************************** */
    /* Matrix */
    /* ******************************************************** */

    Matrix::Matrix(int r, int c)
        {
        rows = r;
        cols = c;
        };

    Matrix::Matrix(const Matrix &m)
        {
        rows = m.rows;
        cols = m.cols;
        data = m.data;
        };

    void Matrix::row_scalar_multiplication(int row, double value)
        {
        for(int i = 0; i < data[row].size(); i++)
            data[row-1][i] *= value;
        };
    
    void Matrix::row_addition_multilpum(int rowA, int rowB, int times, char isAddition)
        {
        if(isAddition == 'T')
            {
            for(int i = 0; i < data[rowA].size(); i++)
                data[rowA-1][i] += data[rowB-1][i]*times;
            }
        else
            {
            for(int i = 0; i < data[rowA].size(); i++)
                data[rowA-1][i] -= data[rowB-1][i]*times;
            }
        };

    void Matrix::row_move(int fromRow, int toRow)
        {
        std::vector<double> tmp = data[toRow-1];
        data[toRow-1] = data[fromRow-1];
        data[fromRow-1] = tmp;
        };

    void Matrix::fill(double value)
        {
        for(int i = 0; i < rows; i++)
            {
            data.push_back(std::vector<double>());
            for(int j = 0; j < cols; j++)
                data[i].push_back(value);
            }
        };

    void Matrix::transpose()
        {
        Matrix m(cols, rows); m.fill(0);
        for(int i = 0; i < cols; i++)
            for(int j = 0; j < rows; j++)
                m.set_value(i+1, j+1, data[j][i]);
        data = m.data; rows = m.rows; cols = m.cols;
        };
    
    void Matrix::set_value(int row, int col, double value) throw()
        {
        try
            {
            if(row > (int) rows || row < 1 || col > (int) cols || col < 1)
                throw outofbounds;
            data[row-1][col-1] = value;
            }
        catch(std::exception& e)  
            {
            std::cout << e.what() << " request: (" << row << ", " << col << ")" << " (rows, cols): (" << (int) rows << ", " << (int) cols << ")" << std::endl;
            std::abort();
            } 
        };

    double Matrix::get_value(int row, int col) throw()
        {
        try
            {
            if(row > (int) rows || row < 1 || col > (int) cols || col < 1)
                throw outofbounds;
            return data[row-1][col-1];
            }
        catch(std::exception& e)
            {
            std::cout << e.what() << " request: (" << row << ", " << col << ")" << " (rows, cols): (" << (int) rows << ", " << (int) cols << ")" << std::endl;
            std::abort();
            }
        };

    void Matrix::pretty_print()
        {
        std::cout << "[ ";
        
        for(int i = 0; i < data.size(); i++)
            {
            std::cout << "[";
            for(int j = 0; j < data[i].size()-1; j++)
                {
                std::cout << data[i][j] << ", ";                    
                }
            std::cout << data[i][data[i].size()-1];
            std::cout << "] ";
            }
        std::cout << "]" << std::endl;;
        };
    };

