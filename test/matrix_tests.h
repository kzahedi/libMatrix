#ifndef __MATRIX_TEST_H__
#define __MATRIX_TEST_H__

#include <matrix/Matrix.h>
#include <cppunit/extensions/HelperMacros.h>

class matrixTests : public CppUnit::TestFixture
{
  CPPUNIT_TEST_SUITE(matrixTests);
  CPPUNIT_TEST(testConstructor1);
  CPPUNIT_TEST(testConstructor2);
  CPPUNIT_TEST(testConstructor3);
  CPPUNIT_TEST(testGettingAndSettingCells);
  CPPUNIT_TEST(testInvalidAccess);
  CPPUNIT_TEST(testCopyOperator);
  CPPUNIT_TEST(testMulFactor);
  CPPUNIT_TEST(testEqual);
  CPPUNIT_TEST(testDiagonal);
  CPPUNIT_TEST(testReset);
  CPPUNIT_TEST(testSetDouble);
  CPPUNIT_TEST(testSubDouble);
  CPPUNIT_TEST(testDivDouble);
  CPPUNIT_TEST(testRowSum);
  CPPUNIT_TEST(testL2);
  CPPUNIT_TEST(testAddMatrix);
  CPPUNIT_TEST(testAddMatrix2);
  CPPUNIT_TEST(testSubMatrix);
  CPPUNIT_TEST(testSubMatrix2);
  CPPUNIT_TEST(testCut);
  CPPUNIT_TEST(testMulMatrix);
  CPPUNIT_TEST(testMulMatrix2);
  CPPUNIT_TEST(testDet);
  CPPUNIT_TEST(testTranspose);
  CPPUNIT_TEST(testInverse);
  CPPUNIT_TEST(testConvexCombine);
#ifdef TEST_VIDEO
  CPPUNIT_TEST(testVideoOutput);
#endif // TEST_VIDEO
  CPPUNIT_TEST_SUITE_END();

public:
  void setUp();
  void tearDown();

  void testConvexCombine();
  void testDet();
  void testTranspose();
  void testConstructor1();
  void testConstructor2();
  void testConstructor3();
  void testGettingAndSettingCells();
  void testInvalidAccess();
  void testFormatter();
  void testCopyOperator();
  void testEqual();
  void testMulFactor();
  void testMulMatrix();
  void testMulMatrix2();
  void testAddMatrix();
  void testDiagonal();
  void testReset();
  void testSetDouble();
  void testSubDouble();
  void testDivDouble();
  void testRowSum();
  void testL2();
  void testSubMatrix();
  void testAddMatrix2();
  void testSubMatrix2();
  void testInverse();
  void testCut();
#ifdef TEST_VIDEO
  void testVideoOutput();
#endif // TEST_VIDEO
};

#endif // __MATRIX_TEST_H__
