#ifndef MATRIX
#define MATRIX
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <exception>

using namespace std;

class file_error : public exception {
  virtual const char* what() const throw() { return "nie mozna odczytac pliku"; }
};

class wrong_matrix_error : public exception {
  virtual const char* what() const throw() { return "nieprawidlowe wymiary macierzy"; }
};

class out_of_index_error : public exception {
  virtual const char* what() const throw() { return "podano nieprawidlowa komorke macierzy"; }
};


class rcmatrix
{
private:
  struct matrix;


public:
  matrix *macierz;
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
  Cref operator() (unsigned int,unsigned int);
  friend std::ostream & operator << (std::ostream & , const rcmatrix &);
  double read(unsigned int, unsigned int) const;
  void write(unsigned int, unsigned int, double);
};

struct rcmatrix::matrix
{
  double *data;
  int n;
  int ver,col;
  matrix()
  {
    ver = 0;
    col = 0;
    data = NULL;
    n = 1;

  }

  matrix(int m_ver, int m_col, double* source) {
	  if (source != NULL) {
		  ver = m_ver;
		  col = m_col;
		  data = new double[ver*col];
		  for (int i = 0; i < ver; i++) {
			  for (int j = 0; j < col; j++) {
				  data[i*col + j] = source[i*col + j];
			  }
		  }
		  n = 1;
	  }
	  else {
		  ver = 0;
		  col = 0;
		  data = NULL;
		  n = 1;
	  }
  }

  matrix(const char* nameFile)
  {
    //cout << "123123123123";
    fstream file;
    file.open(nameFile,ios::in);
    if(file.good() == 0)
    {
      //cout << "Blad otwarcia pliku" << endl;
      throw file_error();
      //abort(); //tutaj dodaj obsluge bledu
    }
    file >> ver;
    //cout << ver << endl;
    file >> col;
    //cout << col << endl;
    data = new double[ver*col];


    for(int i=0;i<ver;i++){
      for(int j=0;j<col;j++)
      {
        // cout << file;
        file >> data[i*col+j];

      }
      }
	n = 1;
  }

  matrix(int m_ver,int m_col) {
    ver = m_ver;
    col = m_col;
    data = new double [ver*col];
    n = 1;
  }

  ~matrix() {
    // cout << "Jestem destruktorem w matrixie" << endl;
	  delete[] data;
  }

  void add(const struct matrix*);
  void sub(const struct matrix*);
  void mul(const struct matrix*);
  matrix* detach();
};


class rcmatrix::Cref
{
  friend class rcmatrix;
  rcmatrix& m;
  int i, j;
  public:
    Cref (rcmatrix& mm, unsigned int ii, unsigned int jj): m(mm), i(ii), j(jj) {};
   //double operator()(unsigned int,unsigned int) const;
   operator double();
   rcmatrix::Cref& operator=(double);
};



#endif
