/**
 * @author Amir Gillette
 * @date 02-04-22
 */

#include <ctime>
#include <cmath>
#include "doctest.h"
#include "Matrix.hpp"
using namespace zich;

vector<double> getRandVecMat(unsigned long size);
Matrix getRandMatrix();



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
    unsigned long row = 1 + rand() % 100;
    unsigned long col = 1 + rand() % 100;
    cout << row << ", " << col << endl;
    vector<double> randVecMat = getRandVecMat(row * col);
    Matrix randMat{randVecMat, row, col};

    vector<double> randVecMatCopy(randVecMat);
    Matrix expectedRandMat{randVecMatCopy, row, col};

    CHECK((randMat-- == expectedRandMat));
    for (double &element : randVecMatCopy) {element--;}
    Matrix expectedRandMat2{randVecMatCopy, row, col};
    CHECK((randMat == expectedRandMat2));

    CHECK((randMat++ == expectedRandMat2));
    for (double &element : randVecMatCopy) {element++;}
    Matrix expectedRandMat3{randVecMatCopy, row, col};
    CHECK((randMat == expectedRandMat3));

    for (double &element : randVecMatCopy) {--element;}
    Matrix expectedRandMat4{randVecMatCopy, row, col};
    CHECK((--randMat == expectedRandMat4));

    for (double &element : randVecMatCopy) {++element;}
    Matrix expectedRandMat5{randVecMatCopy, row, col};
    CHECK((++randMat == expectedRandMat5));
}

TEST_CASE("Unary Operations"){
    unsigned long row = 1 + rand() % 100;
    unsigned long col = 1 + rand() % 100;
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
    unsigned long row = 1 + rand() % 100;
    unsigned long col = 1 + rand() % 100;
    int scalar = rand() % 100;
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

    /* Check *= method */
    CHECK_NOTHROW(randMat *= scalar);
    CHECK((randMat == randMatCopy));
}






double floatRand(double min, double max)
{
    double randFloat = (double)rand() / RAND_MAX;
    return min + randFloat * (max - min);
}

vector<double> getRandVecMat(unsigned long size){
    vector<double> randVecMat;
    for (unsigned long i = 0; i < size; i++){
        double randNum = round(floatRand(-100, 100) * 100.0) / 100.0;
        randVecMat.push_back(randNum);
    }
    return randVecMat;
}

Matrix getRandMatrix(){
    unsigned long row = 1 + rand() % 100;
    unsigned long col = 1 + rand() % 100;
    cout << row << ", " << col << endl;
    vector<double> randVecMat = getRandVecMat(row * col);
    cout << randVecMat.size() << endl;
    Matrix randMat{randVecMat, row, col};
    return randMat;
}
