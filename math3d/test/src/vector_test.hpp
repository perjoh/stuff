#ifndef vectortest_hpp
#define vectortest_hpp

#include <cppunit/extensions/HelperMacros.h>
#include <math3d/mathtypes.hpp>

	class VectorTest : public CppUnit::TestFixture
	{
                CPPUNIT_TEST_SUITE(VectorTest);
                CPPUNIT_TEST(testAlmostEqual);
		CPPUNIT_TEST(testConstruction);
		CPPUNIT_TEST(testZeroConstruction);
		CPPUNIT_TEST(testIndexing);
		CPPUNIT_TEST(testAssignment);
		CPPUNIT_TEST(testCompare);
		CPPUNIT_TEST(testFloatCompare);
		CPPUNIT_TEST(testMultiply);
		CPPUNIT_TEST(testDivide);
		CPPUNIT_TEST(testAdd);
		CPPUNIT_TEST(testSubtract);
		CPPUNIT_TEST(testMultiplyScalar);
		CPPUNIT_TEST(testDivideScalar);
		CPPUNIT_TEST(testAddScalar);
		CPPUNIT_TEST(testSubtractScalar);
		CPPUNIT_TEST(testLength);
		CPPUNIT_TEST(testNormalize);
		CPPUNIT_TEST(testDotProduct);
		CPPUNIT_TEST(testCrossProduct);
		CPPUNIT_TEST(testMetaPrograms);
		CPPUNIT_TEST(testClamp);
        CPPUNIT_TEST(testOptmizingDot);
		CPPUNIT_TEST_SUITE_END();

	public :
		void setUp();
		void tearDown();

	public :
        void testAlmostEqual();
		void testConstruction();
		void testZeroConstruction();
		void testIndexing();
		void testAssignment();
		void testCompare();
		void testFloatCompare();
		void testMultiply();
		void testDivide();
		void testAdd();
		void testSubtract();
		void testMultiplyScalar();
		void testDivideScalar();
		void testAddScalar();
		void testSubtractScalar();
		void testLength();
		void testNormalize();
		void testDotProduct();
		void testCrossProduct();
		void testMetaPrograms();

		void testClamp()
		{
			using namespace math3d;
			vec4i vec = vec4i::make( 1, 2, -1, 1 );
			clamp(vec, 1);
			CPPUNIT_ASSERT_EQUAL( 1, vec[0] );
			CPPUNIT_ASSERT_EQUAL( 1, vec[1] );
			CPPUNIT_ASSERT_EQUAL( -1, vec[2] );
			CPPUNIT_ASSERT_EQUAL( 1, vec[3] );
		}

        void testOptmizingDot() {
            using namespace math3d;

            int dot = OptimizingDot<1,1,1, 0,1,1>::calc(1,2,3, 4,5,6);
            CPPUNIT_ASSERT_EQUAL( 2*5 + 3*6, dot );
        }
	};

#endif
