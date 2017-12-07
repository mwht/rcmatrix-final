#include "rcmatrix.hpp"
#include <iostream>
#include <exception>

using namespace std;

int main()
{
  try {
   rcmatrix xd("macierz.txt");
   rcmatrix ss("macierz2.txt");
   rcmatrix xs;
   //dodać mnożenie i detach !!
   //xs = xd * ss;

   xd*=ss;
   cout << endl << xd << endl;
   xs = xd * ss;
   //xs(1,1) = 26;
  cout <<xs <<  endl << xd << endl << ss << endl;
} catch(exception& e) {
  cout << "Wystapil blad - " << e.what() << endl;
} catch(...) {
  cout << "Wystapil nieznany blad." << endl;
}
  return 0;
}
