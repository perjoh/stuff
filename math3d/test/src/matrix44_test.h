#ifndef matrix44test_h
#define matrix44test_h

#include <cppunit/extensions/HelperMacros.h>
#include <math3d/matrix.hpp>

	typedef math3d::matrix<int, 4, false> matrixi;
	typedef math3d::matrix<float, 4, false> matrixf;

	class Matrix44Test : public CppUnit::TestFixture
	{
                CPPUNIT_TEST_SUITE(Matrix44Test);
		CPPUNIT_TEST(testIndexing);
		CPPUNIT_TEST(testIdentity);
		CPPUNIT_TEST(testAssignment);
		CPPUNIT_TEST(testCompare);
		CPPUNIT_TEST(testMultiply);
		CPPUNIT_TEST_SUITE_END();

	public :
		void setUp();
		void tearDown();

	public :
		void testIndexing();
		void testIdentity();
		void testAssignment();
		void testCompare();
		void testMultiply();

	private :
	};

#endif
