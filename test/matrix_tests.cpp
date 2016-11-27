#include "matrix_tests.h"
#include <Matrix.h>

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( matrixTests );


void matrixTests::setUp()
{
}


void matrixTests::tearDown()
{
}

void matrixTests::testDiagonal()
{
  Matrix m(10,10);

  m.setDiagonalMatrix(1.5);

  for(int r = 0; r < 10; r++)
  {
    for(int c = 0; c < 10; c++)
    {
      if(c == r)
      {
        CPPUNIT_ASSERT_EQUAL((double)1.5, m(r,c));
      }
      else
      {
        CPPUNIT_ASSERT_EQUAL((double)0.0, m(r,c));
      }
    }
  }
}


void matrixTests::testConstructor1()
{
  Matrix m(20, 10,  1.0);
  CPPUNIT_ASSERT_EQUAL(m.rows(), 20);
  CPPUNIT_ASSERT_EQUAL(m.cols(), 10);

  for(int i = 0; i < 20; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, m(i,j), 0.000001);
    }
  }
}

void matrixTests::testConstructor2()
{
  std::vector<double> v;
  for(int i = 0; i < 100; i++)
  {
    v.push_back((double)i);
  }
  Matrix m(10, 10,  v);
  CPPUNIT_ASSERT_EQUAL(m.rows(), 10);
  CPPUNIT_ASSERT_EQUAL(m.cols(), 10);

  double x = 0;
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(x, m(i,j), 0.000001);
      x += 1.0;
    }
  }
}

void matrixTests::testConstructor3()
{
  Matrix m(10, 10);
  CPPUNIT_ASSERT_EQUAL(m.rows(), 10);
  CPPUNIT_ASSERT_EQUAL(m.cols(), 10);

  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(i,j), 0.000001);
    }
  }
}


void matrixTests::testGettingAndSettingCells()
{
  Matrix m(24,15);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(1,2), 0.000001);
  m(1,2) = 1.2;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.2, m(1,2), 0.000001);
  for(int i = 0; i < 24; i++)
  {
    for(int j = 0; j < 15; j++)
    {
      if (i != 1 && j != 2)
      {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(i,j), 0.000001);
      }
    }
  }
  m(2,3) = 2.3;
  CPPUNIT_ASSERT_DOUBLES_EQUAL(2.3, m(2,3), 0.000001);
}

void matrixTests::testInvalidAccess()
{
  bool caught = false;
  Matrix m(10,10);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(1,2), 0.000001);
  try 
  {
    m(11,12) = 1.2;
    CPPUNIT_FAIL("no exception thrown");
  }
  catch(MatrixException me)
  {
    caught = true;
  }
  if(!caught)
  {
    CPPUNIT_FAIL("wrong exception thrown");
  }
}


void matrixTests::testCopyOperator()
{
  Matrix source(10,10);
  Matrix destination(10,10);
  double v = 0;
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      source(i,j) = v++;
    }
  }
  destination = source;
  for(int r = 0; r < 10; r++)
  {
    for(int c = 0; c < 10; c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(source(r,c), destination(r,c), 0.000001);
    }
  }
}

void matrixTests::testMulFactor()
{
  Matrix A(10,10);
  double v = 0.0;
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      A(i,j) = v++;
    }
  }
  A *= 0.1;
  v = 0.0;
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(v * 0.1, A(i,j), 0.0001);
      v++;
    }
  }
}

void matrixTests::testAddMatrix()
{
  Matrix A(10,10);
  Matrix B(10,10);

  double v = 0.0;
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      A(i,j) = v++;
    }
  }
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      B(i,j) = v--;
    }
  }

  B += A;

  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(100.0, B(i,j), 0.0001);
      v++;
    }
  }
}

#ifdef TEST_VIDEO
void matrixTests::testVideoOutput()
{
  Matrix m(10,10);
  Matrix mm(1,10);
  Matrix mm3(5,10);
  MatrixMovieMaker *mmm = new MatrixMovieMaker(&m,10,2,"name.mov");
  MatrixMovieMaker *mmm2 = new MatrixMovieMaker(&mm,10,2,"name2.mov");
  MatrixMovieMaker *mmm3 = new MatrixMovieMaker(&mm3,10,2,"name3.mov");

  //  for(int i = 0; i < 10; i++)
  //  {
  //    double k = 0;
  //    for(int r = 0; r < m.rows(); r++)
  //    {
  //      for(int c = 0; c < m.cols(); c++)
  //      {
  //        double v = ((double)(k))/((double)(m.rows()*m.cols()));
  //        m(r,c) = v;
  //        printf("%d %d = %f\n",r, c, v);
  //        k++;
  //      }
  //    }
  //    mmm->nextFrame();
  //  }

  for(int i = 0; i < 10; i++)
  {
    double k = 0;
    for(int r = 0; r < mm3.rows(); r++)
    {
      for(int c = 0; c < mm3.cols(); c++)
      {
        double v = ((double)(k))/((double)(mm3.rows()*mm3.cols()));
        mm3(r,c) = v;
        k++;
      }
    }
    mmm3->nextFrame();
  }

  //  for(int i = 0; i < 10; i++)
  //  {
  //    for(int r = 0; r < mm.rows(); r++)
  //    {
  //      for(int c = 0; c < mm.cols(); c++)
  //      {
  //        mm(r,c) = ((double)c/(double)mm.cols()) * (double)(1000.0-i)/1000.0;
  //      }
  //    }
  //    mmm2->nextFrame();
  //  }

  delete mmm;
  delete mmm2;
  delete mmm3;
}
#endif // TEST_VIDEO

void matrixTests::testEqual()
{
  Matrix A(10,10);
  double v = 0.0;
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      A(i,j) = v++;
    }
  }

  Matrix B = A;
  CPPUNIT_ASSERT_EQUAL(A.rows(), B.rows());
  CPPUNIT_ASSERT_EQUAL(A.cols(), B.cols());
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(A(i,j), B(i, j), 0.00000000001);
    }
  }

  Matrix C(1,1);
  C = A;
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(A(i,j), C(i, j), 0.00000000001);
    }
  }

}

void matrixTests::testReset()
{
  Matrix m(10,20, 1.0);

  m.reset(5,15);

  CPPUNIT_ASSERT_EQUAL(5, m.rows());
  CPPUNIT_ASSERT_EQUAL(15, m.cols());
  for(int r = 0; r < 5; r++)
  {
    for(int c = 0; c < 15; c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(m(r,c), 0.0, 0.00000000001);
    }
  }

  m.reset(7,12, 1.2);

  CPPUNIT_ASSERT_EQUAL(7, m.rows());
  CPPUNIT_ASSERT_EQUAL(12, m.cols());
  for(int r = 0; r < 7; r++)
  {
    for(int c = 0; c < 12; c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(m(r,c), (double)1.2, 0.000001);
    }
  }

}

void matrixTests::testSetDouble()
{
  Matrix m(5,5, 1.0);

  for(int r = 0; r < 5; r++)
  {
    for(int c = 0; c < 5; c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, m(r,c), 0.0000001);
    }
  }

  m = 2.0;

  for(int r = 0; r < 5; r++)
  {
    for(int c = 0; c < 5; c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, m(r,c), 0.00000000001);
    }
  }

}

void matrixTests::testSubDouble()
{
  Matrix m(5,5, 1.0);

  for(int r = 0; r < 5; r++)
  {
    for(int c = 0; c < 5; c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, m(r,c), 0.00000000001);
    }
  }

  m -= 2.0;

  for(int r = 0; r < 5; r++)
  {
    for(int c = 0; c < 5; c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(-1.0, m(r,c), 0.00000000001);
    }
  }
}

void matrixTests::testDivDouble()
{
  Matrix m(5,5, 1.0);

  for(int r = 0; r < 5; r++)
  {
    for(int c = 0; c < 5; c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, m(r,c), 0.00000000001);
    }
  }

  m /= 2.0;

  for(int r = 0; r < 5; r++)
  {
    for(int c = 0; c < 5; c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.5, m(r,c), 0.00000000001);
    }
  }
}

void matrixTests::testRowSum()
{
  Matrix m(5, 5, 0);

  int value = 0;
  for(int row = 0; row < m.rows(); row++)
  {
    for(int col = 0; col < m.cols(); col++)
    {
      m(row, col) = value;
      value++;
    }
  }

  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0 + 1.0 + 2.0 + 3.0 + 4.0, m.rowSum(0), 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(5.0 + 6.0 + 7.0 + 8.0 + 9.0, m.rowSum(1), 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(10.0 + 11.0 + 12.0 + 13.0 + 14.0, m.rowSum(2), 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(15.0 + 16.0 + 17.0 + 18.0 + 19.0, m.rowSum(3), 0.0000001);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(20.0 + 21.0 + 22.0 + 23.0 + 24.0, m.rowSum(4), 0.0000001);
}

void matrixTests::testL2()
{
  Matrix m(5,5, 0.0);
  double d = m.L2();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, d, 0.0001);

  m(1,1) = 1.0;
  d = m.L2();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, d, 0.0001);

  m(1,1) = 2.0;
  d = m.L2();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, d, 0.0001);

  m(1,1) = 2.0;
  m(2,2) = 2.0;
  d = m.L2();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sqrt((2.0 * 2.0) + (2.0 * 2.0)), d, 0.0001);

  m(1,1) = 2.0;
  m(2,2) = 2.0;
  m(3,3) = 3.0;
  d = m.L2();
  CPPUNIT_ASSERT_DOUBLES_EQUAL(sqrt((2.0 * 2.0) + (2.0 * 2.0) + (3.0 * 3.0)), d, 0.0001);

}

void matrixTests::testSubMatrix()
{
  Matrix A(5,5,0.0);
  Matrix B(5,5,0.0);
  Matrix C(5,5,0.0);
  Matrix D(5,5,0.0);
  Matrix E(5,5,0.0);
#ifdef __APPLE__
  sranddev();
#else
  srand(time(NULL));
#endif
  for(int r = 0; r < C.rows(); r++)
  {
    for(int c = 0; c < C.cols(); c++)
    {
      A(r,c) = ((double)rand()) / ((double)RAND_MAX) * 200.0 - 100.0;
      B(r,c) = ((double)rand()) / ((double)RAND_MAX) * 200.0 - 100.0;
    }
  }

  D = A;
  E = B;

  C = A - B;

  for(int r = 0; r < C.rows(); r++)
  {
    for(int c = 0; c < C.cols(); c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(A(r,c) - B(r,c), C(r,c), 0.0000001);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(A(r,c), D(r,c), 0.0000001);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(B(r,c), E(r,c), 0.0000001);
    }
  }

}

void matrixTests::testAddMatrix2()
{
  Matrix A(5,5,7.5);
  Matrix B(5,5,2.5);
  Matrix C(5,5);
  C = A + B;
  for(int r = 0; r < C.rows(); r++)
  {
    for(int c = 0; c < C.cols(); c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(7.5, A(r,c), 0.0000001);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(2.5, B(r,c), 0.0000001);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(10.0, C(r,c), 0.0000001);
    }
  }
}

void matrixTests::testSubMatrix2()
{
  Matrix A(5,5,0.0);
  Matrix B(5,5,0.0);
  Matrix C(5,5,0.0);
  Matrix D(5,5,0.0);
#ifdef __APPLE__
  sranddev();
#else
  srand(time(NULL));
#endif

  for(int r = 0; r < C.rows(); r++)
  {
    for(int c = 0; c < C.cols(); c++)
    {
      double d = ((double)rand()) / ((double)RAND_MAX);
      double e = ((double)rand()) / ((double)RAND_MAX);
      A(r,c) = d;
      B(r,c) = e;
    }
  }

  C = A;
  D = B;
  A -= B;
  for(int r = 0; r < A.rows(); r++)
  {
    for(int c = 0; c < A.cols(); c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(B(r,c),          D(r,c), 0.0000001);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(C(r,c) - D(r,c), A(r,c), 0.0000001);
    }
  }
}


void matrixTests::testDet()
{
  Matrix m(1,1, 2.0);
  CPPUNIT_ASSERT_DOUBLES_EQUAL(2.0, m.det(), 0.0000001);

  Matrix m2(2,2);
  m2(0,0) = 1.0;
  m2(0,1) = 2.0;
  m2(1,0) = 3.0;
  m2(1,1) = 4.0;

  double d = m2(0, 0) * m2(1, 1) - m2(0, 1) * m2(1, 0); 

  CPPUNIT_ASSERT_DOUBLES_EQUAL(d, m2.det(), 0.0000001);

  Matrix m3(4,4);
  m3(0,0) = 1.0;
  m3(0,1) = 3.0;
  m3(0,2) = 1.0;
  m3(0,3) = 3.0;
          
  m3(1,0) = 3.0;
  m3(1,1) = 0.1;
  m3(1,2) = 0.8;
  m3(1,3) = 9.0;
           
  m3(2,0) = 1.1;
  m3(2,1) = 2.2;
  m3(2,2) = 3.1;
  m3(2,3) = 4.1;
            
  m3(3,0) = 16.0;
  m3(3,1) = 17.0;
  m3(3,2) = 18.0;
  m3(3,3) = 19.0;

  double det = m3(0, 3) * m3(1, 2) * m3(2, 1) * m3(3, 0) - m3(0, 2) * m3(1, 3) * m3(2, 1) * m3(3, 0)-
    m3(0, 3) * m3(1, 1) * m3(2, 2) * m3(3, 0)+m3(0, 1) * m3(1, 3) * m3(2, 2) * m3(3, 0)+
    m3(0, 2) * m3(1, 1) * m3(2, 3) * m3(3, 0)-m3(0, 1) * m3(1, 2) * m3(2, 3) * m3(3, 0)-
    m3(0, 3) * m3(1, 2) * m3(2, 0) * m3(3, 1)+m3(0, 2) * m3(1, 3) * m3(2, 0) * m3(3, 1)+
    m3(0, 3) * m3(1, 0) * m3(2, 2) * m3(3, 1)-m3(0, 0) * m3(1, 3) * m3(2, 2) * m3(3, 1)-
    m3(0, 2) * m3(1, 0) * m3(2, 3) * m3(3, 1)+m3(0, 0) * m3(1, 2) * m3(2, 3) * m3(3, 1)+
    m3(0, 3) * m3(1, 1) * m3(2, 0) * m3(3, 2)-m3(0, 1) * m3(1, 3) * m3(2, 0) * m3(3, 2)-
    m3(0, 3) * m3(1, 0) * m3(2, 1) * m3(3, 2)+m3(0, 0) * m3(1, 3) * m3(2, 1) * m3(3, 2)+
    m3(0, 1) * m3(1, 0) * m3(2, 3) * m3(3, 2)-m3(0, 0) * m3(1, 1) * m3(2, 3) * m3(3, 2)-
    m3(0, 2) * m3(1, 1) * m3(2, 0) * m3(3, 3)+m3(0, 1) * m3(1, 2) * m3(2, 0) * m3(3, 3)+
    m3(0, 2) * m3(1, 0) * m3(2, 1) * m3(3, 3)-m3(0, 0) * m3(1, 2) * m3(2, 1) * m3(3, 3)-
    m3(0, 1) * m3(1, 0) * m3(2, 2) * m3(3, 3)+m3(0, 0) * m3(1, 1) * m3(2, 2) * m3(3, 3);

  CPPUNIT_ASSERT_DOUBLES_EQUAL(det, m3.det(), 0.01);

}

void matrixTests::testTranspose()
{
  Matrix m(1,2);
  m(0,0) = 1.0;
  m(0,1) = 2.0;

  Matrix mm = m;
  mm.transpose();

  Matrix m2(5,4);
  int v = 0;
  for(int r = 0; r < m2.rows(); r++)
  {
    for(int c = 0; c < m2.cols(); c++)
    {
      m2(r, c) = v++;
    }
  }

  Matrix mm2 = m2;
  mm2.transpose();

  CPPUNIT_ASSERT_EQUAL(m.cols(), mm.rows());
  CPPUNIT_ASSERT_EQUAL(m.rows(), mm.cols());

  CPPUNIT_ASSERT_EQUAL(m2.cols(), mm2.rows());
  CPPUNIT_ASSERT_EQUAL(m2.rows(), mm2.cols());

  for(int r = 0; r < m.rows(); r++)
  {
    for(int c = 0; c < m.cols(); c++)
    {
      CPPUNIT_ASSERT_EQUAL(m(r,c), mm(c,r));
    }
  }

  for(int r = 0; r < m2.rows(); r++)
  {
    for(int c = 0; c < m2.cols(); c++)
    {
      CPPUNIT_ASSERT_EQUAL(m2(r,c), mm2(c,r));
    }
  }

}

void matrixTests::testInverse()
{
  Matrix m(5,5);
  Matrix n(m.rows(),m.cols());

  CPPUNIT_ASSERT_EQUAL(5, m.rows());
  CPPUNIT_ASSERT_EQUAL(5, m.cols());

#ifdef __APPLE__
  sranddev();
#else
  srand(time(NULL));
#endif

  for(int r = 0; r < m.rows(); r++)
  {
    for(int c = 0; c < m.cols(); c++)
    {
      m(r,c) = ((double)rand()) / ((double)RAND_MAX) * 200.0 - 100.0;
      n(r,c) = m(r,c);
    }
  }

  Matrix mi = m;
  mi.invert();

  Matrix m_product = m;
  m_product *= mi;

  for(int r = 0; r < m_product.rows(); r++)
  {
    for(int c = 0; c < m_product.cols(); c++)
    {
      if(r != c)
      {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m_product(r,c), 0.00001);
      }
      else
      {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, m_product(r,c), 0.00001);
      }
    }
  }

  Matrix ni = n;
  ni.invert();


  Matrix n_product = n;
  n_product *= ni;

  // cout << endl;
  // cout << "M product" << endl;
  // cout << m_product  << endl;
  // cout << "N product" << endl;
  // cout << n_product  << endl;
  // cout << endl;
  // cout << "M invert" << endl;
  // cout << mi << endl << endl;
  // cout << "N invert" << endl;
  // cout << ni << endl << endl;
  
  for(int r = 0; r < n_product.rows(); r++)
  {
    for(int c = 0; c < n_product.cols(); c++)
    {
      if(r != c)
      {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, n_product(r,c), 0.00001);
      }
      else
      {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, n_product(r,c), 0.00001);
      }
    }
  }



  for(int r = 0; r < m.rows(); r++)
  {
    for(int c = 0; c < n.cols(); c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(mi(r,c), ni(r,c), 0.00001);
    }
  }
}

void matrixTests::testMulMatrix()
{
  Matrix A(3,3);
  Matrix B(3,3);

  double v = 0;
  for(int r = 0; r < A.rows(); r++)
  {
    for(int c = 0; c < A.cols(); c++)
    {
      A(r, c) = v++;
      B(r, c) = v++;
    }
  }

  Matrix AT = A;
  Matrix BT = B;

  AT.transpose();
  BT.transpose();

  Matrix C = A;
  C *= B;
  C.transpose();

  Matrix D = BT;
  D *= AT;

  // (A * B)^T = B^T * A^T
  for(int r = 0; r < C.rows(); r++)
  {
    for(int c = 0; c < C.rows(); c++)
    {
      // test if A * B = A^T * B
      CPPUNIT_ASSERT_DOUBLES_EQUAL(D(r,c), C(r,c), 0.0000001);
    }
  }
}

void matrixTests::testCut()
{
  Matrix m(4,4);
  for(int r = 0; r < 4; r++)
  {
    for(int c = 0; c < 4; c++)
    {
      if(r == 2 || c == 2)
      {
        m(r, c) = 1;
      }
      else
      {
        m(r, c) = 0;
      }
    }
  }

  m.cut(2,2);

  for(int i = 0; i < m.rows(); i++)
  {
    for(int j = 0; j < m.cols(); j++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(i,j), 0.0000001);
    }
  }
  
  // test col only

  m.reset(4,4);
  for(int r = 0; r < 4; r++)
  {
    for(int c = 0; c < 4; c++)
    {
      if(r == 2 || c == 2)
      {
        m(r, c) = 1;
      }
      else
      {
        m(r, c) = 0;
      }
    }
  }

  m.cut(-1,2);

  CPPUNIT_ASSERT_EQUAL(4, m.rows());
  CPPUNIT_ASSERT_EQUAL(3, m.cols());

  for(int i = 0; i < m.rows(); i++)
  {
    for(int j = 0; j < m.cols(); j++)
    {
      if(i == 2)
      {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, m(i,j), 0.0000001);
      }
      else
      {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(i,j), 0.0000001);
      }
    }
  }

  // test rows only

  m.reset(4,4);
  for(int r = 0; r < 4; r++)
  {
    for(int c = 0; c < 4; c++)
    {
      if(r == 2 || c == 2)
      {
        m(r, c) = 1;
      }
      else
      {
        m(r, c) = 0;
      }
    }
  }

  m.cut(2);

  CPPUNIT_ASSERT_EQUAL(3, m.rows());
  CPPUNIT_ASSERT_EQUAL(4, m.cols());

  for(int i = 0; i < m.rows(); i++)
  {
    for(int j = 0; j < m.cols(); j++)
    {
      if(j == 2)
      {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(1.0, m(i,j), 0.0000001);
      }
      else
      {
        CPPUNIT_ASSERT_DOUBLES_EQUAL(0.0, m(i,j), 0.0000001);
      }
    }
  }
}

void matrixTests::testConvexCombine()
{
  int rows = 4; int cols = 4;
  Matrix a(rows,cols);
  Matrix b(rows, cols);
  Matrix convex(rows, cols);
  Matrix a_copy(rows, cols);
  Matrix b_copy(rows, cols);
#ifdef __APPLE__
  sranddev();
#else
  srand(time(NULL));
#endif

  for(int r = 0; r < rows; r++)
  {
    for(int c = 0; c < cols; c++)
    {
      a(r,c) = ((double)rand()) / ((double)RAND_MAX);
      b(r,c) = ((double)rand()) / ((double)RAND_MAX);
    }
  }

  a_copy = a;
  b_copy = b;

  convex = 0.2 * a + 0.8 * b;

  for(int r = 0; r < rows; r++)
  {
    for(int c = 0; c < cols; c++)
    {
      CPPUNIT_ASSERT_DOUBLES_EQUAL(a_copy(r, c), a(r, c), 0.0000001);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(b_copy(r, c), b(r, c), 0.0000001);
      CPPUNIT_ASSERT_DOUBLES_EQUAL(convex(r, c), (double)(0.2 * a(r, c) + 0.8 * b(r, c)), 0.001);
    }
  }
}
