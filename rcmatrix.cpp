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
  if(this->col == M1->ver && this->ver == M1->col)
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
};

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
  matrix *nowa_macierz = new matrix(macierz->ver, MAT.macierz->col, macierz->data);
  nowa_macierz->mul(MAT.macierz);
  if (--macierz->n == 0)
    delete macierz;
  macierz = nowa_macierz;
  return *this;
}

rcmatrix rcmatrix::operator*(const rcmatrix& MAT) const
{
  rcmatrix MAT2 = (rcmatrix&) MAT;
  MAT2 *= *this;
  return MAT2;
}

rcmatrix rcmatrix::operator+(const rcmatrix& MAT) const
{
  rcmatrix temp(MAT);

  temp.macierz->add(MAT.macierz);
  cout << "Wykonuje operator+" << endl;
  //temp.macierz->n--;
  //MAT.macierz->n--;
  //macierz->n--;
  return temp;
}




rcmatrix rcmatrix::operator-(const rcmatrix& MAT) const
{
  rcmatrix MAT2 = (rcmatrix&) MAT;
 //MAT2.macierz = macierz;
 MAT2 -= MAT;


  return MAT2;
}



double rcmatrix::read(unsigned int i, unsigned int j) const
{
 if(i < 0 || i > macierz->ver || j < 0 || j > macierz->col) throw out_of_index_error();
 return macierz->data[i*macierz->col+j];
}

void rcmatrix::write(unsigned int i, unsigned int j, double k)
{
 if(i < 0 || i > macierz->ver || j < 0 || j > macierz->col) throw out_of_index_error();
 this->macierz = this->macierz->detach();
 macierz->data[i*macierz->col+j] = k;
}



/*double rcmatrix::Cref::operator()(unsigned int ii, unsigned int jj) const
{
  return m.read(ii,jj);
}*/

rcmatrix::Cref::operator double() {
  return m.read(i,j);
}

rcmatrix::Cref& rcmatrix::Cref::operator=(double d) {
  m.write(i,j,d);
  return *this;
}

rcmatrix::Cref rcmatrix::operator()(unsigned int i,unsigned int j)
{
  return Cref(*this,i,j);
}
