/**
 * Demo file for the exercise on numbers with units
 *
 * @author Erel Segal-Halevi
 * @since 2019-02
 * 
 * Edited by Tal Zichlinsky
 * @since 2022-02
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "Matrix.hpp"
using namespace zich;

int main() {
  
  std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
  Matrix a{identity, 3, 3};  // constructor taking a vector and a matrix size
  cout << a << endl;
  /* prints [1 0 0]
            [0 1 0]
            [0 0 1]*/

  cout << (-a) << endl;
  /* prints [-1 0 0]
            [0 -1 0]
            [0 0 -1]*/
  cout << (a*3) << endl;
  /* prints [-3 0 0]
            [0 -3 0]
            [0 0 -3]*/

  Matrix b{arr, 3, 3};
  a *= -3;

  cout << (a+b) << endl;  // prints the 0 matrix
  cout << (b-a) << endl;
  /* prints [6 0 0]
            [0 6 0]
            [0 0 6]*/
  cout << a * b << endl;
  cout << "End of demo!" << endl;


  cout << "*****************************" << endl;

  std::vector<double> arr2 = {1, 1, 0, 1, 0, 0, 1, 1};
  std::vector<double> arr3 = {3, 0, 3, 0, 3, 3, 0, 3};
  Matrix c{arr2, 2, 4};  // constructor taking a vector and a matrix size
  Matrix d{arr3, 4, 2};  // constructor taking a vector and a matrix size
  Matrix e{arr3, 4, 2};  // constructor taking a vector and a matrix size

  cout << c << "\n\n";
  cout << d << "\n\n";
  cout << "Multiplication" << endl;
  cout << (c * d) << endl;

  cout << "********* Relations *********" << endl;
  cout << (d > c) << endl;   // true  - 1
  cout << (d >= c) << endl;  // true  - 1
  cout << (d < c) << endl;   // false - 0
  cout << (d <= c) << endl;  // false - 0
  cout << (d == e) << endl;  // true  - 1
  cout << (d != e) << endl;  // false - 0

  cout << "******************************" << endl;
  Matrix s{{},0,0};
  cin >> s;
  cout << s << endl;

  return 0;
}
