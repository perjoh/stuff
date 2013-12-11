#include "intersect_test.hpp"
#include <math3d/intersections.hpp>


CPPUNIT_TEST_SUITE_REGISTRATION( IntersectTest );

	using namespace math3d;
	using namespace math3d::intersect;

	const float radius = 7.5;

	void IntersectTest::setUp()
	{
		s_ = Sphere( make_vec( -5.8f, 2.8f, 1.5f ), radius );
	}

	void IntersectTest::tearDown()
	{
	}

	void IntersectTest::test_ray_sphere_inside()
	{
		ray r( s_.center(), norm( make_vec( 0, 1, 0) ) );
		float t;
		CPPUNIT_ASSERT( intersect_ray_sphere_nearest( r, s_, t ) );
		CPPUNIT_ASSERT( intersect_ray_sphere_test( r, s_ ) );
		CPPUNIT_ASSERT( r.sample(t) == s_.center() + make_vec(0.0f,s_.radius(),0.0f) );
	}

	void IntersectTest::test_ray_sphere_no_intersect()
	{
		vec a(make_vec(-19,19,-5));
		vec b(make_vec(25,-12,-15));

		ray r( a, norm( b - a ) );

		float t;
		CPPUNIT_ASSERT( !intersect_ray_sphere_nearest( r, s_, t ) );
		CPPUNIT_ASSERT( !intersect_ray_sphere_test( r, s_ ) );
	}

	void IntersectTest::test_ray_sphere_intersect()
	{
		vec a(s_.center() - make_vec(30,0,0));
		ray r( a, make_vec(1,0,0) );
		float t;
		CPPUNIT_ASSERT( intersect_ray_sphere_nearest( r, s_, t ) );
		CPPUNIT_ASSERT( intersect_ray_sphere_test( r, s_ ) );
		CPPUNIT_ASSERT( r.sample(t) == s_.center() - make_vec(s_.radius(), 0.0f, 0.0f) );
	}

	void IntersectTest::test_line_sphere_inside_no_intersect()
	{
	}

	void IntersectTest::test_line_sphere_outside_no_intersect()
	{
	}

	void IntersectTest::test_line_sphere_intersect()
	{
	}

	void IntersectTest::test_sphere_aabb_intersect()
	{
		{ Aabb aabb( make_vec( -1, -1, -1 ), make_vec( 1, 1, 1 ) );
		Sphere s0( make_vec( 1.6f, 0.0f, 0.0f ), 0.5f );
		Sphere s1( make_vec( 1.0f, 0.0f, 0.0f ), 0.5f );
		Sphere s2( make_vec( 0.0f, 0.0f, 0.0f ), 0.5f );

		CPPUNIT_ASSERT( !testSphereAabb( s0, aabb ) );
		CPPUNIT_ASSERT( testSphereAabb( s1, aabb ) );
		CPPUNIT_ASSERT( testSphereAabb( s2, aabb ) ); }

		// Sphere lies on edge of box
		{ Aabb aabb( make_vec( -1, -1, -1 ), make_vec( 1, 1, 1 ) );
		Sphere s0( make_vec( 2.0f, 0.0f, 0.0f ), 1.0f );
		Sphere s1( make_vec( -2.0f, 0.0f, 0.0f ), 1.0f );
		CPPUNIT_ASSERT( !testSphereAabb( s0, aabb ) );
		CPPUNIT_ASSERT( !testSphereAabb( s1, aabb ) ); }
	}

	void IntersectTest::test_ray_aabb_intersect()
	{
		Aabb aabb( make_vec( -1,-1,-1 ), make_vec( 1,1,1 ) );

		{
			// test intersection
			vec origin( make_vec( 5, 2, -3 ) );
			vec target( make_vec( 0, 0, 0 ) );
			ray r( origin, norm(target-origin) );
			scalar t0, t1;
			CPPUNIT_ASSERT( intersect_ray_aabb(r, aabb, t0, t1 ) );
		}

		{
			// test no intersection
			vec origin( make_vec( 5, 0, 0 ) );
			vec target( make_vec( 0, 2, 0 ) );
			ray r( origin, norm(target-origin) );
			scalar t0, t1;
			CPPUNIT_ASSERT( !intersect_ray_aabb(r, aabb, t0, t1 ) );
		}

		{
			// test output parameters
			vec origin( make_vec( 5, 0, 0 ) );
			vec target( make_vec( 0, 0, 0 ) );
			ray r( origin, norm(target-origin) );
			scalar t0, t1;
			CPPUNIT_ASSERT( intersect_ray_aabb(r, aabb, t0, t1 ) );
			CPPUNIT_ASSERT( value_traits<scalar>::almost_equal( t0, 4.0f ) );
			CPPUNIT_ASSERT( value_traits<scalar>::almost_equal( t1, 6.0f ) );
		}

		{
			// test ray origin inside box
			vec target( make_vec( 5, 0, 0 ) );
			vec origin( make_vec( 0, 0, 0 ) );
			ray r( origin, norm(target-origin) );
			scalar t0, t1;
			CPPUNIT_ASSERT( intersect_ray_aabb(r, aabb, t0, t1 ) );
			CPPUNIT_ASSERT( value_traits<scalar>::almost_equal( t0, 0.0f ) );
			CPPUNIT_ASSERT( value_traits<scalar>::almost_equal( t1, 1.0f ) );
		}

	}
