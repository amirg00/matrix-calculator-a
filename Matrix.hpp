/**
 * @author Amir Gillette
 * @date 30-03-22
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace std;

namespace zich{
    class Matrix{

        /**************************************************/
        //================== Friend Functions =============/
        /**************************************************/
        /* Input & Output Operators */
        friend ostream& operator<<(ostream& os, const Matrix& matrix);   /* Output Operator */
        friend istream& operator>>(istream& is, Matrix& matrix);         /* Input Operator */

        /* Multiplication Operators */
        friend Matrix operator*(int scalar, Matrix& matrix);             /* Multiplication of a matrix by scalar */
        friend Matrix operator*(Matrix& matrix, int scalar);             /* Multiplication of a scalar by a matrix */

    private:
        unsigned long _row, _col;
        vector<double> _matrix;
    public:
        // Constructor
        Matrix (vector<double> matrix, unsigned long row, unsigned long col);

        // Mathematical Operators
        /* Plus Operators */
        Matrix operator+(const Matrix& other);       /* Regular matrices addition */
        Matrix operator+();                          /* Unary addition */
        Matrix& operator+=(const Matrix& other);     /* Insertion addition */
        Matrix& operator++();                        /* Prefix increment matrix by 1 */
        Matrix operator++(int);                      /* Postfix increment matrix by 1 */

        /* Minus Operators */
        Matrix operator-(const Matrix& other);       /* Regular matrices subtraction */
        Matrix operator-();                          /* Unary subtraction */
        Matrix& operator-=(const Matrix& other);     /* Desertion subtraction */
        Matrix& operator--();                        /* Prefix decrement matrix by 1 */
        Matrix operator--(int);                      /* Postfix decrement matrix by 1 */

        /* Multiplication Operators */
        Matrix operator*(const Matrix &other);       /* Multiplication of a matrix by matrix */
        Matrix& operator*=(int);                     /* Multiplication of a matrix by scalar insertion */

        // Comparison Operators
        bool operator>(const Matrix& other) const;   /* Matrix > Other_Matrix operator  */
        bool operator>=(const Matrix& other) const;  /* Matrix >= Other_Matrix operator */
        bool operator<(const Matrix& other) const;   /* Matrix < Other_Matrix operator  */
        bool operator<=(const Matrix& other) const;  /* Matrix <= Other_Matrix operator */
        bool operator==(const Matrix& other);        /* Matrix == Other_Matrix operator */
        bool operator!=(const Matrix& other);        /* Matrix != Other_Matrix operator */

        static bool compareByOperator(const Matrix&, const Matrix&, const string&) ;
    };
}