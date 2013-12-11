#include "plane_test.hpp"
#include <math3d/plane.hpp>

CPPUNIT_TEST_SUITE_REGISTRATION( MY_TEST_CLASS_NAME );

	using namespace math3d;

	typedef vector<double, 3> vec;
	typedef Plane<double> planed;


	void MY_TEST_CLASS_NAME::setUp()
	{
	}

	void MY_TEST_CLASS_NAME::tearDown()
	{
	}

	void MY_TEST_CLASS_NAME::test_construction()
	{
		vector<int> v( make_vec( 1, 0, 0 ) );
		int s = 5;
		Plane<int> p( v, s );
		CPPUNIT_ASSERT( p.normal() == v );
		CPPUNIT_ASSERT( p.distance() == s );

		vec v1( make_vec( -1, -1, 5 ) );
		vec v2( make_vec( 2, -2, 5 ) );
		vec v3( make_vec( 3, 1, 5 ) );

		planed p1( v1, v2, v3 );
		planed p2( make_vec(0, 0, 1), 5 );

		CPPUNIT_ASSERT( p1 == p2 );
	}

	void MY_TEST_CLASS_NAME::test_front_side()
	{
		{
			planed p( make_vec( 1, 0, 0 ), 2 );
			vec pt1( make_vec( 3, 15, -2 ) ); // font side
			vec pt2( make_vec( 1.2, 15.0, -2.0 ) ); // back side

			CPPUNIT_ASSERT( p.front_side( pt1 ) );
			CPPUNIT_ASSERT( !p.front_side( pt2 ) );
		}

		{
			planed p( make_vec( 1, 0, 0 ), -2 );
			vec pt1( make_vec( -1, 15, -2 ) ); // front side
			vec pt2( make_vec( -2.2, 15.0, -2.0 ) ); // back side

			CPPUNIT_ASSERT( p.front_side( pt1 ) );
			CPPUNIT_ASSERT( !p.front_side( pt2 ) );
		}

		{
			planed p( make_vec( -1, 0, 0 ), -2 );
			vec pt1( make_vec( -1, 15, -2 ) ); // front side
			vec pt2( make_vec( 2.2, 15.0, -2.0 ) ); // back side

			CPPUNIT_ASSERT( p.front_side( pt1 ) );
			CPPUNIT_ASSERT( !p.front_side( pt2 ) );
		}

		{
			planed p( make_vec( 1, 0, 0 ), 0 );
			vec pt1( make_vec( 1, 15, -2 ) ); // front side
			vec pt2( make_vec( -2.2, 15.0, -2.0 ) ); // back side

			CPPUNIT_ASSERT( p.front_side( pt1 ) );
			CPPUNIT_ASSERT( !p.front_side( pt2 ) );
		}

		{
			planed p( make_vec( -1, 0, 0 ), 0 );
			vec pt1( make_vec( -1, 15, -2 ) ); // front side
			vec pt2( make_vec( 2.2, 15.0, -2.0 ) ); // back side

			CPPUNIT_ASSERT( p.front_side( pt1 ) );
			CPPUNIT_ASSERT( !p.front_side( pt2 ) );
		}
	}

	void MY_TEST_CLASS_NAME::test_normal()
	{
	}

	void MY_TEST_CLASS_NAME::test_distance()
	{
	}

	void MY_TEST_CLASS_NAME::test_equal_op()
	{
	}
