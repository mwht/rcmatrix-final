#ifndef MATRIX
#define MATRIX
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <exception>

using namespace std;

class file_error : public exception {
  virtual const char* what() const throw() { return "nie mozna wczytac macierzy z pliku"; }
};

class wrong_matrix_error : public exception {
  virtual const char* what() const throw() { return "nieprawidlowy rozmiar macierzy"; }
};

class out_of_index_error : public exception {
  virtual const char* what() const throw() { return "nieprawidlowy adres komorki macierzy"; }
};


class rcmatrix
{
private:
  struct matrix;
  matrix *macierz;
public:
  class Cref;
  rcmatrix();
  rcmatrix(const char*);
  rcmatrix(const rcmatrix&);
  ~rcmatrix();
  rcmatrix& operator= (const rcmatrix&);
  rcmatrix& operator+= (const rcmatrix&);
  rcmatrix operator+ (const rcmatrix&) const;
  rcmatrix& operator-= (const rcmatrix&);
  rcmatrix operator- (const rcmatrix&) const;
  rcmatrix& operator*= (const rcmatrix&);
  rcmatrix operator* (const rcmatrix&) const;
  Cref operator() (int,int);
  friend std::ostream & operator << (std::ostream & , const rcmatrix &);
  double read(int, int) const;
  void write(int, int, double);
};


struct rcmatrix::matrix
{
  double *data;
  int n;
  int rows,cols;
  matrix()
  {
    rows = 0;
    cols = 0;
    data = NULL;
    n = 1;

  }

  matrix(int m_rows, int m_cols, double* source) {
	  if (source != NULL) {
		  rows = m_rows;
		  cols = m_cols;
		  data = new double[rows*cols];
		  for (int i = 0; i < rows; i++) {
			  for (int j = 0; j < cols; j++) {
				  data[i*cols + j] = source[i*cols + j];
			  }
		  }
		  n = 1;
	  }
	  else {
		  rows = 0;
		  cols = 0;
		  data = NULL;
		  n = 1;
	  }
  }

  matrix(const char* nameFile)
  {
    fstream file;
    file.open(nameFile,ios::in);
    if(file.good() == 0)
    {
      throw file_error();
    }
    file >> rows;
    file >> cols;
    data = new double[rows*cols];
    for(int i=0;i<rows;i++)
      for(int j=0;j<cols;j++)
        file >> data[i*cols+j];
    n = 1;
  }

  matrix(int m_rows,int m_cols) {
    rows = m_rows;
    cols = m_cols;
    data = new double [*cols];
    n = 1;
  }

  ~matrix() {
	  delete[] data;
  }

  void add(const struct matrix*);
  void sub(const struct matrix*);
  void mul(const struct matrix*, const struct matrix*);
  matrix* detach();
};


class rcmatrix::Cref
{
  friend class rcmatrix;
  rcmatrix& m;
  int i, j;
  public:
   Cref (rcmatrix& mm, int ii, int jj): m(mm), i(ii), j(jj) {};
   operator double();
   rcmatrix::Cref& operator=(double);
};



#endif
