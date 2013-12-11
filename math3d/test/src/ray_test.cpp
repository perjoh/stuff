//#include <cppunit/config/SourcePrefix.h>

#include "ray_test.hpp"
#include <math3d/ray.hpp>

CPPUNIT_TEST_SUITE_REGISTRATION( MY_TEST_CLASS_NAME );

	using namespace math3d;
	typedef float Scalar;
	typedef Ray<Scalar> Ray_t;
	typedef Ray_t::vector_type Vec;
	typedef Aa_plane<Scalar> Aap;

	void MY_TEST_CLASS_NAME::setUp()
	{
	}

	void MY_TEST_CLASS_NAME::tearDown()
	{
	}

	void MY_TEST_CLASS_NAME::test_construction()
	{
	}

	void MY_TEST_CLASS_NAME::test_origin()
	{
	}

	void MY_TEST_CLASS_NAME::test_direction()
	{
	}

	void MY_TEST_CLASS_NAME::test_sample()
	{
	}

	void MY_TEST_CLASS_NAME::test_split()
	{
		{ Vec target(make_vec(5,5,0));
		Vec origin(make_vec(0,0,0));
		Ray_t ray( origin, norm(target-origin) );
		Aap plane( X_axis, 1 );
		Scalar t;
		CPPUNIT_ASSERT( ray.split( plane, t ) );
		CPPUNIT_ASSERT( value_traits<Scalar>::almost_equal( ray.sample(t)[0],  1.0f ) ); }

		// test negative split
		{ Vec target(make_vec(-5,5,0));
		Vec origin(make_vec(0,0,0));
		Ray_t ray( origin, norm(target-origin) );
		Aap plane( X_axis, -1 );
		Scalar t;
		CPPUNIT_ASSERT( ray.split( plane, t ) );
		CPPUNIT_ASSERT( value_traits<Scalar>::almost_equal( ray.sample(t)[0], -1.0f ) ); }
	}
