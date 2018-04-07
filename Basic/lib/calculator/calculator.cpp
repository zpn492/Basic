#include "calculator.hpp"

using namespace linalg;

void linalg::create_matrix(std::string line, std::string name, std::map<std::string, Matrix> &outputdata)
    {
    std::vector<std::string> rows = filehandler::split_string(line, '.'); // rows

    std::vector<std::string> cols = filehandler::split_string(rows[0], ','); // cols

    std::vector<std::string> evalues = cols;

    Matrix m(rows.size(), cols.size()); m.fill(0);
    
    for(int j = 0; j < rows.size(); j++)
        {
        if(j==0)
            evalues = cols;
        else
            evalues = filehandler::split_string(rows[j], ',');

        for(int k = 0; k < evalues.size(); k++)           
            m.set_value(j+1,k+1,atof(evalues[k].c_str()));
        }
    outputdata.insert( std::pair<std::string, Matrix>(name, m) );
    };

void linalg::arithmics(char &operation, std::string a, std::string b, std::string name, std::map<std::string, Matrix> &outputdata)
    {
    Matrix A = outputdata.find(a)->second;
    Matrix B = outputdata.find(b)->second;
       
    switch(operation)
        {
        case '+':
            A + B;
        break;
        case '*':
            A * B;
        break;
        }
    outputdata.insert( std::pair<std::string, Matrix>(name, A) );
    
    };


void linalg::scalar(char &operation, std::string a, std::string num, std::string name, std::map<std::string, Matrix> &outputdata)
    {
    Matrix A = outputdata.find(a)->second;
    switch(operation)
        {
        case '+': A + atoi(num.c_str()); break;
        case '*': A * atoi(num.c_str()); break;
        }
    outputdata.insert( std::pair<std::string, Matrix>(name, A) );
    };
    
std::map<std::string, Matrix> linalg::decode_file(const char *filename)
    {
    Logger log;
    std::string s = filehandler::get_file_contents(filename, log);

    s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());   
    s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());  

    std::vector<std::string> lines = filehandler::split_string(s, ':');

    std::map<std::string, Matrix> lvalues;
    std::vector<std::string> rvalues;
    
    for(int i = 0; i < lines.size(); i++)
        {
        rvalues = filehandler::split_string(lines[i], ';');
        
        switch(rvalues[0][0])
            {
            case 'A': { linalg::create_matrix(rvalues[2], rvalues[1], lvalues); } break;
            case 'C': {/* Comment */} break;
            case 'M': { linalg::arithmics(rvalues[3][0], rvalues[2], rvalues[4], rvalues[1], lvalues); } break;
            case 'S': { linalg::scalar(rvalues[3][0], rvalues[2], rvalues[4], rvalues[1], lvalues); } break;
            case 'T':
                {
                Matrix A = lvalues.find(rvalues[2])->second;
                A.transpose();
                if(rvalues[2] == rvalues[1])
                    lvalues.find(rvalues[2])->second = A;
                else
                    lvalues.insert( std::pair<std::string, Matrix>(rvalues[1], A) );
                }
            break;
            case 'R':
                {
                Matrix A = lvalues.find(rvalues[2])->second;
                switch(rvalues[3][0])
                    {
                    case 'M':
                        A.row_scalar_multiplication(atoi(rvalues[5].c_str()), atof(rvalues[4].c_str()) );
                    break;
                    case 'B':
                        A.row_move(atoi(rvalues[5].c_str()), atoi(rvalues[6].c_str()) );
                    break;
                    case 'S':
                        A.row_addition_multilpum(atoi(rvalues[5].c_str()), atoi(rvalues[6].c_str()), atoi(rvalues[4].c_str()), rvalues[7][0] );
                    break;
                    }
                if(rvalues[2] == rvalues[1])
                    lvalues.find(rvalues[2])->second = A;
                else
                    lvalues.insert( std::pair<std::string, Matrix>(rvalues[1], A) );
                }
            break;
            case 'L':
                {
                Matrix A = lvalues.find(rvalues[2])->second;
                Matrix b = lvalues.find(rvalues[3])->second;
                Matrix X = lup_solve(A, b);
                if(rvalues[2] == rvalues[1])
                    lvalues.find(rvalues[2])->second = X;
                else
                    lvalues.insert( std::pair<std::string, Matrix>(rvalues[1], X) );
                }
            break;
            }
        }
        return lvalues;
    };

/* ******************************************************** */
/* Solve system of linear equations */
/* ******************************************************** */
    
std::vector<Matrix> linalg::lu_decomposition(Matrix &A)
    {
    std::vector<Matrix> lu;
    Matrix TMP(A);
    Matrix L(A.rows, A.rows); L.fill(1);
    Matrix U(A.rows, A.rows); U.fill(1);

    int i, k, j;

    for(i = 0; i < A.rows; i++)
        for(j = 0; j < A.rows; j++) 
            {
            if(j < i) U.set_value(i+1,j+1,0);
            if(j > i) L.set_value(i+1,j+1,0);
            }

    for(k = 0; k < A.rows; k++)
        {
        U.set_value(k+1, k+1, A.get_value(k+1, k+1) ) ;
        for(i = k + 1; i < A.rows; i++)
            {
            L.set_value(i+1, k+1, A.get_value(i+1, k+1) / A.get_value(k+1, k+1) );
            U.set_value(k+1, i+1, A.get_value(k+1, i+1) );
            }
        for(i = k + 1; i < A.rows; i++)
            for(j = k + 1; j < A.rows; j++)
                A.set_value(i+1, j+1, A.get_value(i+1, j+1) - L.get_value(i+1, k+1) * U.get_value(k+1, j+1) );
        }
    lu.push_back(L);
    lu.push_back(U);
    
    A = TMP;

    return lu;
    };

Matrix linalg::ly_b_solve(Matrix &L, Matrix &b)
    {
    Matrix Y(L.rows, 1); Y.fill(0);
    int i, j; 
    double tmp;

    Y.set_value(1, 1, b.get_value(1, 1) );

    for(i = 1; i < L.rows; i++)
        {
        tmp = 0;
        for(j = 0; j < i; j++)
            tmp += L.get_value(i+1, j+1) * Y.get_value(j+1,1);
        Y.set_value(i+1, 1, b.get_value(i+1, 1) - tmp);
        }
    return Y;
    };

Matrix linalg::ux_y_solve(Matrix &U, Matrix &Y)
    {
    Matrix X(U.rows, 1); X.fill(0);
    int i, j;
    double tmp;

    X.set_value(U.rows, 1, Y.get_value(U.rows, 1) / U.get_value(U.rows, U.rows) );
    
    for(i = U.rows-2; i > -1; i--)
        {
        tmp = 0;
        for(j = i+1; j < U.rows; j++)
            {                
            tmp += U.get_value(i+1, j+1) * X.get_value(j+1, 1); 
            }
        X.set_value(i+1, 1, (Y.get_value(i+1, 1) - tmp) / U.get_value(i+1, i+1) );
        }

    return X;
    };

Matrix linalg::lup_solve(Matrix &A, Matrix &b)
    {
    std::vector<Matrix> lu = lu_decomposition(A);

    Matrix Y = ly_b_solve(lu[0], b);

    Matrix X = ux_y_solve(lu[1], Y);

    return X;
    };

void linalg::pretty_print(std::map<std::string, Matrix> lvalues)
    {
    std::map<std::string,Matrix>::iterator it;
    for (it=lvalues.begin(); it!=lvalues.end(); ++it) 
        {
        std::cout << it->first.c_str() << ": ";
        it->second.pretty_print();
        }
    };