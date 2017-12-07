#include "rcmatrix.hpp"
#include <iostream>

using namespace std;
rcmatrix::rcmatrix()
{
  macierz = new matrix();
  //rcmatrix::matrix();
}

rcmatrix::rcmatrix(const char* nameFile)
{
  macierz = new matrix(nameFile);
  //rcmatrix::matrix(nameFile);
}

rcmatrix::rcmatrix(const rcmatrix& rc) {
  //if(--this->macierz->n == 0) delete this->macierz;
  rc.macierz->n++;
  macierz = rc.macierz;
  //macierz = new matrix(rc.macierz->ver,rc.macierz->col);
  // for(int i=0;i<macierz->ver;i++) {
  //   for(int j=0;j<macierz->col;j++) {
  //     macierz->data[i*macierz->col+j] = rc.macierz->data[i*macierz->col+j];
  //   }
  // }
}

rcmatrix::~rcmatrix() {
  // cout << "USUWAM: " << macierz->n << endl;
	if (--macierz->n == 0)
  {
    // cout << "Jestem wywoływany"  << endl;
		delete macierz;
  }
}

std::ostream & operator << (std::ostream & s, const rcmatrix & M)
{
  for(int i = 0; i < M.macierz->ver;i++)
  {
    for(int j = 0; j< M.macierz->col;j++)
    {
      cout << M.macierz->data[i*M.macierz->col+j] << " ";
    }
      cout << "\n";
  }

  return s;
}


void rcmatrix::matrix::add(const struct matrix* M1)
{
  if(this->col == M1->col && this->ver == M1->ver)
  {
    for(int i = 0; i < col;i++)
      for(int j = 0; j < ver; j++)
        this->data[i*col+j] += M1->data[i*col+j];
  }
  else
  {
    //cout << "Macierze nie są takie same!!" << endl;
    throw wrong_matrix_error();
  }
}


void rcmatrix::matrix::sub(const struct matrix* M1)
{
  if(this->col == M1->col && this->ver == M1->ver)
  {
    for(int i = 0; i < col;i++)
      for(int j = 0; j < ver; j++)
        this->data[i*col+j] -= M1->data[i*col+j];
  }
  else
  {
    //cout << "Macierze nie są takie same!!" << endl;
    throw wrong_matrix_error();
  }
}

void rcmatrix::matrix::mul(const struct matrix* M1)
{
  cout << "xd" << endl;
  cout << "kolumna this: "<< this->col << "  " << "wiersz m1: "<< M1->ver << endl;
  cout << "wiersza this: " <<this-> ver << "  " << "kolumna m1: " << M1-> col << endl;
  if(this->col == M1->ver)
  {
    matrix* temp = new matrix(this->ver, M1->col);
    for(int i = 0; i < this->ver; i++)
    {
      for(int j = 0; j < M1->col; j++)
      {
        double wynik = 0;
        //cout << this->data[i*this->col+j] << " ";
        for(int k = 0;k<this->col; k++)
        {
           wynik += this->data[i*this->col+k] * M1->data[k*this->col+j];
        }
        temp->data[i*this->col+j] = wynik;
      }
    }
    for(int i = 0; i < this->ver; i++)
      for(int j = 0; j < M1->col; j++)
        this->data[i*this->col+j] = temp->data[i*this->col+j];
    delete temp;
  }
  else{
    throw wrong_matrix_error();
  }
}

rcmatrix::matrix* rcmatrix::matrix::detach()
{
  if(n==1)
    return this;
  rcmatrix::matrix* m=new matrix(ver,col,data);
  n--;
  return m;
}

rcmatrix& rcmatrix::operator=(const rcmatrix& MAT)
{
  // TODO: if(this==this) return;
  if(--this->macierz->n == 0) delete this->macierz;
  this->macierz = MAT.macierz;
  this->macierz->n++;
  return *this;



}

rcmatrix& rcmatrix::operator+=(const rcmatrix& MAT)
{
  matrix* nowa_macierz = new matrix(macierz->ver, macierz->col, macierz->data);
  nowa_macierz->add(MAT.macierz);
  if (--macierz->n == 0)
	  delete macierz;
  macierz = nowa_macierz;
  return *this;
}

rcmatrix& rcmatrix::operator-=(const rcmatrix& MAT)
{
  matrix *nowa_macierz = new matrix(macierz->ver, macierz->col, macierz->data);
  nowa_macierz->sub(MAT.macierz);
  if (--macierz->n == 0)
	  delete macierz;
  macierz = nowa_macierz;
  return *this;
}

rcmatrix& rcmatrix::operator*=(const rcmatrix& MAT)
{
  cout << endl << "Jestem w operator*=" << endl << "wiersza MAT: "<< MAT.macierz->ver << endl << "kolumna mat: " << MAT.macierz->col << endl;

  matrix *nowa_macierz = new matrix(macierz->ver, MAT.macierz->col, macierz->data);
  cout << endl << "Jestem w operator*=2 " << endl << "wiersza MAT: "<< nowa_macierz->ver << endl << "kolumna mat: " << nowa_macierz->col << endl;
  nowa_macierz->mul(MAT.macierz);
  if (--macierz->n == 0)
    delete macierz;
  macierz = nowa_macierz;
  return *this;
}

rcmatrix rcmatrix::operator*(const rcmatrix& MAT) const
{
  rcmatrix temp = *this;
  temp *= MAT;
  return temp;
}

rcmatrix rcmatrix::operator+(const rcmatrix& MAT) const
{
  rcmatrix temp(*this);

  temp+=MAT;
  cout << "Wykonuje operator+" << endl;
  return temp;
}




rcmatrix rcmatrix::operator-(const rcmatrix& MAT) const
{
 rcmatrix temp(*this);

 temp-=MAT;
 cout << "Wykonuje operator-" << endl;

 return temp;
}



double rcmatrix::read(int i, int j) const
{
 if(i < 0 || i > macierz->ver || j < 0 || j > macierz->col) throw out_of_index_error();
 return macierz->data[i*macierz->col+j];
}

void rcmatrix::write(int i, int j, double k)
{
 if(i < 0 || i > macierz->ver || j < 0 || j > macierz->col) throw out_of_index_error();
 this->macierz = this->macierz->detach();
 macierz->data[i*macierz->col+j] = k;
}





rcmatrix::Cref::operator double() {
  return m.read(i,j);
}

rcmatrix::Cref& rcmatrix::Cref::operator=(double d) {
  m.write(i,j,d);
  return *this;
}

rcmatrix::Cref rcmatrix::operator()(int i,int j)
{
  return Cref(*this,i,j);
}
