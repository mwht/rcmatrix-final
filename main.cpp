#include "rcmatrix.hpp"
#include <iostream>
#include <exception>

using namespace std;

int main()
{
  try {
   rcmatrix A("matrix.txt");
   rcmatrix B("matrix2.txt");
   rcmatrix C;

   // cout << (C = A + B) <<  endl;
   // cout << (A += B) << endl;
   // cout << (C = B + A) <<  endl;
   // cout << (B += A) << endl;
   // cout << (C = A - B) <<  endl;
   // cout << (A -= B) << endl;
  // cout << A << endl << endl << B << endl;
    cout << (C = B * A) <<  endl;
   // cout << (B *= A) << endl;
} catch(exception& w) {
  cout << "Wystapil blad - " << w.what() << endl;
} catch(...) {
  cout << "Default error." << endl;
}
  return 0;
}
