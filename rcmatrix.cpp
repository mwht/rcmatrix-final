#include "rcmatrix.hpp"
#include <iostream>

using namespace std;

rcmatrix::rcmatrix() {
  mat = new matrix();
}

rcmatrix::rcmatrix(const char* fname)
{
  mat = new matrix(fname);
}

rcmatrix::rcmatrix(const rcmatrix& rc) {
  rc.mat->n++;
  mat = rc.mat;
}

rcmatrix::~rcmatrix() {
	if (--mat->n == 0) {
		delete mat;
  	}
}

double rcmatrix::read(int i, int j) const
{
 if(i < 0 || i > mat->rows || j < 0 || j > mat->cols) throw out_of_index_error();
 return mat->data[i*mat->cols+j];
}

void rcmatrix::write(int i, int j, double k)
{
 if(i < 0 || i > mat->rows || j < 0 || j > mat->cols) throw out_of_index_error();
 mat = mat->detach();
 mat->data[i*mat->cols+j] = k;
}


std::ostream & operator << (std::ostream & s, const rcmatrix & M)
{
  for(int i = 0; i < M.mat->rows;i++)
  {
    for(int j = 0; j< M.mat->cols;j++)
    {
      cout << M.mat->data[i*M.mat->cols+j] << " ";
    }
      cout << "\n";
  }

  return s;
}

rcmatrix& rcmatrix::operator=(const rcmatrix& MAT)
{

  if(--mat->n == 0)
    delete mat;
  mat = MAT.mat;
  mat->n++;
  return *this;
}

rcmatrix& rcmatrix::operator+=(const rcmatrix& MAT)
{
  matrix* new_matrix = new matrix(mat->rows, mat->cols, mat->data);
  new_matrix->add(MAT.mat);
  if (--mat->n == 0)
	  delete mat;
  mat = new_matrix;
  return *this;
}

rcmatrix rcmatrix::operator+(const rcmatrix& MAT) const
{
  rcmatrix temp(*this);
  temp+=MAT;
  return temp;
}

rcmatrix& rcmatrix::operator-=(const rcmatrix& MAT)
{
  matrix *new_matrix = new matrix(mat->rows, mat->cols, mat->data);
  new_matrix->sub(MAT.mat);
  if (--mat->n == 0)
	  delete mat;
  mat = new_matrix;
  return *this;
}

rcmatrix rcmatrix::operator-(const rcmatrix& MAT) const
{
 rcmatrix temp(*this);
 temp-=MAT;
 return temp;
}

rcmatrix& rcmatrix::operator*=(const rcmatrix& MAT)
{
  matrix *new_matrix = new matrix(mat->rows, MAT.mat->cols);
  new_matrix->mul(mat, MAT.mat);
  if (--mat->n == 0)
    delete mat;
  mat = new_matrix;
  return *this;
}

rcmatrix rcmatrix::operator*(const rcmatrix& MAT) const
{
  rcmatrix temp = *this;
  temp *= MAT;
  return temp;
}

//------------------- rcmatrix::matrix -------------------
void rcmatrix::matrix::add(const struct matrix* M1)
{
  if(cols == M1->cols && rows == M1->rows)
  {
    for(int i = 0; i < cols;i++)
      for(int j = 0; j < rows; j++)
        data[i*cols+j] += M1->data[i*cols+j];
  }
  else
  {
    throw wrong_matrix_error();
  }
}


void rcmatrix::matrix::sub(const struct matrix* M1)
{
  if(cols == M1->cols && rows == M1->rows)
  {
    for(int i = 0; i < cols;i++)
      for(int j = 0; j < rows; j++)
        data[i*cols+j] -= M1->data[i*cols+j];
  }
  else
  {
    throw wrong_matrix_error();
  }
}

void rcmatrix::matrix::mul(const struct matrix* M1, const struct matrix* M2)
{
  if(M1->cols == M2->rows && M1->rows == M2->cols)
  {
    matrix* temp = new matrix(M1->rows, M2->cols);
    for(int i = 0; i < M1->rows; i++)
    {
      for(int j = 0; j < M2->cols; j++)
      {
        double wynik = 0;
        for(int k = 0;k<M1->cols; k++)
        {
           wynik += M1->data[i*M1->cols+k] * M2->data[k*M2->cols+j];
        }
        temp->data[i*cols+j] = wynik;
      }
    }
    for(int i = 0; i < rows; i++)
      for(int j = 0; j < cols; j++)
        data[i*cols+j] = temp->data[i*cols+j];
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
  rcmatrix::matrix* m=new matrix(rows,cols,data);
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
