#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <vector>
#include <string>
#include <iostream>

class MatrixException : public std::exception
{
  public:
    explicit MatrixException(const std::string& what)
      :m_what(what)
    {}

    virtual ~MatrixException() throw() {}

    virtual const char * what() const throw()
    {
      return m_what.c_str();
    }

    virtual void message() const throw()
    {
      std::cout << "MatrixException: " << m_what << std::endl;
    }


  private:
    std::string m_what;
};

class Matrix
{
  public:
    /** Most simple constructor. Every cell is initialised with 0.*/
    Matrix();
    Matrix(Matrix &m);
    Matrix(const Matrix &m);
    Matrix(int rows, int cols);

    /** Most simple constructor. Every cell is initialised with the given
     * value.*/
    Matrix(int rows, int cols, double initialValue);

    /** Most simple constructor. The cells are initialised with the values of
     * the vector. If the vector is smaller than the numbers of cells, the
     * remaining cells are filled with 0. The filling occurs rows first.
     */
    Matrix(int rows, int cols, std::vector<double> initialValues);

    /** Destructor. */
    ~Matrix();

    /** Allows to access and modification of the values by indexing */
    double&   operator()(int row, int col) throw(MatrixException);
    double    operator()(int row, int col) const throw(MatrixException);
    Matrix&   operator+=(const Matrix &m)  throw(MatrixException);
    Matrix&   operator-=(const Matrix &m)  throw(MatrixException);

    // TODO: Matrix A(10,10); Matrix A = B; does not work
    const Matrix operator*(const double factor);
    Matrix&      operator*=(const double factor);

    bool         operator==(const Matrix&) const;
    bool         operator!=(const Matrix& b) const;

    Matrix&      operator= (const Matrix &m);
    Matrix&      operator*=(const Matrix &m) throw(MatrixException);

    Matrix&      operator= (const double d);
    Matrix&      operator-=(const double d);
    Matrix&      operator/=(const double d);

    const Matrix operator-(const Matrix &m) const;
    const Matrix operator+(const Matrix &m) const;
    const Matrix operator*(const Matrix &m);

    double L2();

    int    cols() const;
    int    rows() const;

    void   setDiagonalMatrix(double value);

    double rowSum(const int row);
    double colSum(const int col);
    double sum();

    void   reset(int rows, int cols, double value = (double)0.0);
    void   rescaleRows(double value, bool verbose);

    double det() throw(MatrixException);
    void   invert();
    void   transpose();
    Matrix T();
    Matrix colMean();
    Matrix rowMean();
    void   adjunct();
    void   cut(int r_index = -1, int c_index = -1);
    double get(const int row, const int col);

    void   resize(int rows, int columns);

    friend Matrix operator*(double, const Matrix&);

    friend std::ostream& operator<<(std::ostream& str, const Matrix& m)
    {
      str << m._rows << "x" << m._cols << std::endl;
      str.precision(10);
      str.setf(std::ios::fixed,std::ios::floatfield);
      for(int r = 0; r < m._rows; r++)
      {
        for(int c = 0; c < m._cols - 1; c++)
        {
          str << m._cell[r][c] << " ";
        }
        str << m._cell[r][m._cols -1] << std::endl;
      }
      return str;
    };

  protected:
    void     __set(const  int row, const int col, const  double value);
    double   __get(const  int row, const int col);
    void     __add(const  int row, const int col, const  double value);
    void     __deleteCells();
    void     __copy(const Matrix &m);
    void     __init(const int rows, const int cols, double initialValue);
    void     __check(int  row, int col) throw(MatrixException);
    int      _rows;
    int      _cols;
    double** _cell;

};

#endif // __MATRIX_H__
