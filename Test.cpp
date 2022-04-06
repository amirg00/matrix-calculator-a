/**
 * @author Amir Gillette
 * @date 02-04-22
 */

#include <ctime>
#include <cmath>
#include "doctest.h"
#include "Matrix.hpp"
using namespace zich;

vector<double> getRandVecMat(int size);
Matrix getRandMatrix();
double floatRand(double min, double max);


// Check cases in which matrices dimension isn't the same.
// In such cases, an exception should be thrown by definition.
TEST_CASE("Matrices dimension isn't the same"){
    srand(time(0)); /* create random generator*/
    Matrix randMat = getRandMatrix();
    Matrix OtherRandMat = getRandMatrix();

    CHECK_THROWS(randMat + OtherRandMat);
    CHECK_THROWS(randMat += OtherRandMat);

    CHECK_THROWS(randMat - OtherRandMat);
    CHECK_THROWS(randMat -= OtherRandMat);

    CHECK_THROWS(bool b = randMat > OtherRandMat);
    CHECK_THROWS(bool b = randMat >= OtherRandMat);
    CHECK_THROWS(bool b = randMat < OtherRandMat);
    CHECK_THROWS(bool b = randMat <= OtherRandMat);
    CHECK_THROWS(bool b = randMat == OtherRandMat);
    CHECK_THROWS(bool b = randMat != OtherRandMat);
}

TEST_CASE("Comparison Operators"){

}


TEST_CASE("Increment - Decrement Matrix"){
    /* Create random matrix */
    int row = 1 + rand() % 100;
    int col = 1 + rand() % 100;
    cout << row << ", " << col << endl;
    vector<double> randVecMat = getRandVecMat(row * col);
    Matrix randMat{randVecMat, row, col};

    vector<double> randVecMatCopy(randVecMat);
    Matrix expectedRandMat{randVecMatCopy, row, col};

    /* Check postfix '--' operation */
    CHECK((randMat-- == expectedRandMat));
    for (double &element : randVecMatCopy) {element--;}
    Matrix expectedRandMat2{randVecMatCopy, row, col};
    CHECK((randMat == expectedRandMat2));

    /* Check postfix '++' operation */
    CHECK((randMat++ == expectedRandMat2));
    for (double &element : randVecMatCopy) {element++;}
    Matrix expectedRandMat3{randVecMatCopy, row, col};
    CHECK((randMat == expectedRandMat3));

    /* Check prefix '--' operation */
    for (double &element : randVecMatCopy) {--element;}
    Matrix expectedRandMat4{randVecMatCopy, row, col};
    CHECK((--randMat == expectedRandMat4));

    /* Check prefix '++' operation */
    for (double &element : randVecMatCopy) {++element;}
    Matrix expectedRandMat5{randVecMatCopy, row, col};
    CHECK((++randMat == expectedRandMat5));
}

TEST_CASE("Unary Operations"){
    /* Create random matrix */
    int row = 1 + rand() % 100;
    int col = 1 + rand() % 100;
    cout << row << ", " << col << endl;
    vector<double> randVecMat = getRandVecMat(row * col);
    Matrix randMat{randVecMat, row, col};
    CHECK((+randMat == randMat));
    Matrix randMatUnary = +randMat;
    CHECK_FALSE((&randMatUnary == &randMat)); /* Check that it returns a copy*/

    vector<double> randVecMatCopy(randVecMat);
    for (double &element : randVecMatCopy) {element *= -1;}
    Matrix expectedRandMat{randVecMatCopy, row, col};
    Matrix randMatUnaryMinus = -randMat;
    CHECK((randMatUnaryMinus == expectedRandMat));
    CHECK_FALSE((&randMatUnaryMinus == &randMat)); /* Check that it returns a copy*/
}

TEST_CASE("Scalar Multiplication"){
    /* Create random matrix and scalar*/
    int row = 1 + rand() % 100;
    int col = 1 + rand() % 100;
    double scalar = round(floatRand(-100, 100) * 100.0) / 100.0;
    cout << row << ", " << col << endl;
    vector<double> randVecMat = getRandVecMat(row * col);
    vector<double> randVecMatCopy(randVecMat);

    Matrix randMat{randVecMat, row, col};

    CHECK_NOTHROW(randMat * scalar);
    CHECK_NOTHROW(scalar * randMat); /* same for the prefix*/

    for (double &element : randVecMatCopy) {element *= scalar;}
    Matrix randMatCopy{randVecMatCopy, row, col};
    Matrix MultiplicationRight = randMat * scalar;
    CHECK((MultiplicationRight == randMatCopy));

    /* Check multiplication of matrix by a scalar, on left side of matrix */
    Matrix MultiplicationLeft = scalar * randMat;
    CHECK((MultiplicationLeft == randMatCopy));

    /* Check *= method for scalar */
    CHECK_NOTHROW(randMat *= scalar);
    CHECK((randMat == randMatCopy));
}

TEST_CASE("Matrix Multiplication"){
    std::vector<double> arr1 = {1, 1, 0, 1, 0, 0, 1, 1};
    std::vector<double> arr2 = {3, 0, 3, 0, 3, 3, 0, 3};
    std::vector<double> arr3 = {6, 3, 3, 6};
    Matrix a{arr1, 2, 4};  // constructor taking a vector and a matrix size
    Matrix b{arr2, 4, 2};  // constructor taking a vector and a matrix size
    Matrix result{arr3, 2, 2};
    CHECK((a*b == result));

    std::vector<double> arr4 = {1, 0, 0, 1, 0, 0, 1, 0, 0};
    std::vector<double> arr5 = {3, 0, 0, 3, 0, 0, 3, 0, 0};
    Matrix c{arr4, 3, 3};  // constructor taking a vector and a matrix size
    Matrix d{arr5, 3, 3};  // constructor taking a vector and a matrix size
    Matrix result2{arr5, 3, 3};
    CHECK((c*d == result2));

    /* Invalid case by matrix multiplication def.: e's cols isn't equal to f's row*/
    Matrix e{arr1, 4, 2};
    Matrix f{arr2, 4, 2};
    CHECK_THROWS(e*f);
}

TEST_CASE("Constructor"){
    /* Create random vector */
    vector<double> randVecMat = getRandVecMat(10);

    /* rows or cols are zero */
    CHECK_THROWS((Matrix{{}, 0, 0}));

    /* rows or cols are negative */
    int randNegNum =  (-1) * (rand() % 100);
    CHECK_THROWS((Matrix{randVecMat, randNegNum, 10}));
    CHECK_THROWS((Matrix{randVecMat, 10, randNegNum}));
    CHECK_THROWS((Matrix{randVecMat, -2, -5})); /* row * col = 10 and vector size is 10, but they are negative*/


    /* rows & cols are positive but don't match vector size*/
    CHECK_THROWS((Matrix{randVecMat, 3, 3}));

}

TEST_CASE("Print Random Matrix"){
    Matrix mat = getRandMatrix();
    CHECK_NOTHROW(cout << mat << '\n');
}





double floatRand(double min, double max)
{
    double randFloat = (double)rand() / RAND_MAX;
    return min + randFloat * (max - min);
}

vector<double> getRandVecMat(int size){
    vector<double> randVecMat;
    for (int i = 0; i < size; i++){
        double randNum = round(floatRand(-100, 100) * 100.0) / 100.0;
        randVecMat.push_back(randNum);
    }
    return randVecMat;
}

Matrix getRandMatrix(){
    int row = 1 + rand() % 100;
    int col = 1 + rand() % 100;
    cout << row << ", " << col << endl;
    vector<double> randVecMat = getRandVecMat(row * col);
    cout << randVecMat.size() << endl;
    Matrix randMat{randVecMat, row, col};
    return randMat;
}
