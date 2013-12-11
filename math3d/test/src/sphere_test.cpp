#include "sphere_test.hpp"
#include <math3d/sphere.hpp>

CPPUNIT_TEST_SUITE_REGISTRATION( MY_TEST_CLASS_NAME );

	using namespace math3d;

	void MY_TEST_CLASS_NAME::setUp()
	{
	}

	void MY_TEST_CLASS_NAME::tearDown()
	{
	}

	void MY_TEST_CLASS_NAME::test_min_max()
	{
		Sphere<int> s( make_vec( 1,2,3 ), 5 );

		CPPUNIT_ASSERT( s.min( 0 ) == -4 );
		CPPUNIT_ASSERT( s.min( 1 ) == -3 );
		CPPUNIT_ASSERT( s.min( 2 ) == -2 );

		CPPUNIT_ASSERT( s.max( 0 ) == 6 );
		CPPUNIT_ASSERT( s.max( 1 ) == 7 );
		CPPUNIT_ASSERT( s.max( 2 ) == 8 );
	}
