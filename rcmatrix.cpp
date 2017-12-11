#include "rcmatrix.hpp"
#include <iostream>

using namespace std;

rcmatrix::rcmatrix() {
  macierz = new matrix();
}

rcmatrix::rcmatrix(const char* nameFile)
{
  macierz = new matrix(nameFile);
}

rcmatrix::rcmatrix(const rcmatrix& rc) {
  rc.macierz->n++;
  macierz = rc.macierz;
}

rcmatrix::~rcmatrix() {
	if (--macierz->n == 0)
  {
		delete macierz;
  }
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

rcmatrix& rcmatrix::operator=(const rcmatrix& MAT)
{
  // if(this->macierz == MAT.macierz)
  //   return *this;

  if(--this->macierz->n == 0)
    delete this->macierz;
  this->macierz = MAT.macierz;
  this->macierz->n++;
  return *this;
}

//------------------- operator + i += -------------------
rcmatrix& rcmatrix::operator+=(const rcmatrix& MAT)
{
  matrix* nowa_macierz = new matrix(macierz->ver, macierz->col, macierz->data);
  nowa_macierz->add(MAT.macierz);
  if (--macierz->n == 0)
	  delete macierz;
  macierz = nowa_macierz;
  return *this;
}

rcmatrix rcmatrix::operator+(const rcmatrix& MAT) const
{
  rcmatrix temp(*this);
  temp+=MAT;
  return temp;
}

//------------------- operator - i -= -------------------
rcmatrix& rcmatrix::operator-=(const rcmatrix& MAT)
{
  matrix *nowa_macierz = new matrix(macierz->ver, macierz->col, macierz->data);
  nowa_macierz->sub(MAT.macierz);
  if (--macierz->n == 0)
	  delete macierz;
  macierz = nowa_macierz;
  return *this;
}

rcmatrix rcmatrix::operator-(const rcmatrix& MAT) const
{
 rcmatrix temp(*this);
 temp-=MAT;
 return temp;
}

//------------------- operator - i -= -------------------
rcmatrix& rcmatrix::operator*=(const rcmatrix& MAT)
{
  matrix *nowa_macierz = new matrix(macierz->ver, MAT.macierz->col);
  nowa_macierz->mul(macierz, MAT.macierz);
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
//--------------------------------------

//------------------- rcmatrix::matrix -------------------
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
    throw wrong_matrix_error();
  }
}

void rcmatrix::matrix::mul(const struct matrix* M1, const struct matrix* M2)
{
  if(M1->col == M2->ver && M1->ver == M2->col)
  {
    matrix* temp = new matrix(M1->ver, M2->col);
    for(int i = 0; i < M1->ver; i++)
    {
      for(int j = 0; j < M2->col; j++)
      {
        double wynik = 0;
        for(int k = 0;k<M1->col; k++)
        {
           wynik += M1->data[i*M1->col+k] * M2->data[k*M2->col+j];
        }
        temp->data[i*this->col+j] = wynik;
      }
    }
    for(int i = 0; i < this->ver; i++)
      for(int j = 0; j < this->col; j++)
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

//------------------- rcmatrix::Cref -------------------
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
