#include "rcmatrix.hpp"
#include <iostream>

using namespace std;

int main()
{
   rcmatrix xd("macierz.txt");
   //rcmatrix xs("macierz.txt");
   rcmatrix francja;
  //int a = 3, b = 4, c=0;
  //xd += xs;
  // cout << '\n' <<xd;
  // cout << xd.read(1,1);
  // cout << endl << "Test ()" << endl;
  // cout << xd(1,1) << endl;
   //xd -= xs;
  //cout << '\n' <<xd;
   //cout << xd.read(1,1);
  // cout << "--- ss = xd+xs ---" << endl;
  rcmatrix jebacLKS = xd;
  //rcmatrix RTS = jebacLKS;

      francja = xd;
     //cout << francja;
     cout << francja.macierz->n << " " << xd.macierz->n << endl;
    xd(1,1) = 997;

    cout << xd(1,1) << endl;

  //  cout << '\n' << ss;
  // cout << "--- ss = xd-xs ---" << endl;
  // ss = xd - xs;
  // cout << '\n' << ss;
  // cout << "--- sd = xd-xs ---" << endl;
  // sd = xd-xs;
  // cout << '\n' << sd;

  //cout << "TEST" << endl;

  //cin.get();
  return 0;
}
