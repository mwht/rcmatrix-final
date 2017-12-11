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
   rcmatrix D("mat_3x3_1.txt");
   rcmatrix E("mat_3x3_2.txt");
   rcmatrix F;
   cout << "--- Macierz 1 ---" << endl << endl << D << endl;
   cout << "--- Macierz 2 ---" << endl << endl << E << endl;
   cout << "--- + i - ---" << endl;
   cout << (F = D + E) <<  endl;
   cout << (F = E - D) <<  endl;
   cout << (D += E) << endl;
   cout << "--- += i -= ---" << endl;
   cout << (D += E) << endl;
   cout << (E -= D) << endl;
   cout << "--- *= i * ---" << endl;
   cout << "--- Macierz 1 ---" << endl << endl << A << endl;
   cout << "--- Macierz 2 ---" << endl << endl << B << endl;
   cout << (C = B * A) <<  endl;
   cout << (B *= A) << endl;
} catch(exception& e) {
  cout << "Wystapil blad - " << e.what() << endl;
} catch(...) {
  cout << "Wystapil nieznany blad." << endl;
}
  return 0;
}
