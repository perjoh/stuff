#include <boost/test/unit_test.hpp>
#include "../include/math3d/intersections.hpp"
#include "../include/math3d/Sphere.hpp"
#include "../include/math3d/vector.hpp"
#include "../include/math3d/ray.hpp"
#include "../include/math3d/line.hpp"
#include "../include/math3d/box.hpp"
#include "../include/math3d/triangle.hpp"
#include "../include/math3d/mathtypes.hpp"

    typedef math3d::Ray<float> Rayf;
    typedef math3d::Triangle<float> Trianglef;
    typedef math3d::Line<float> Linef;
    typedef float scalar;
    typedef math3d::Ray<scalar> ray;
    typedef math3d::Sphere<scalar> Spheref;
    typedef math3d::Aabb<scalar> Aabbf;
    typedef ray::vector_type vec;

	const float radius = 7.5;

    namespace {

        struct Fixture
        {
            Fixture()
                : s_( Spheref( math3d::make_vec( -5.8f, 2.8f, 1.5f ), radius ) )
            { }

		    Spheref s_;
        };
    }

    using namespace math3d;
    using namespace math3d::intersect;

    BOOST_FIXTURE_TEST_SUITE(Math3dBoxSuite, Fixture)

    BOOST_AUTO_TEST_CASE(test_ray_sphere_inside)
	{
		ray r( s_.center(), norm( make_vec( 0, 1, 0) ) );
		float t;
		BOOST_REQUIRE( intersect_ray_sphere_nearest( r, s_, t ) );
		BOOST_REQUIRE( intersect_ray_sphere_test( r, s_ ) );
		BOOST_REQUIRE( r.sample(t) == s_.center() + make_vec(0.0f,s_.radius(),0.0f) );
	}

	BOOST_AUTO_TEST_CASE(test_ray_sphere_no_intersect)
	{
		vec a(make_vec(-19,19,-5));
		vec b(make_vec(25,-12,-15));

		ray r( a, norm( b - a ) );

		float t;
		BOOST_REQUIRE( !intersect_ray_sphere_nearest( r, s_, t ) );
		BOOST_REQUIRE( !intersect_ray_sphere_test( r, s_ ) );
	}

	BOOST_AUTO_TEST_CASE(test_ray_sphere_intersect)
	{
		vec a(s_.center() - make_vec(30,0,0));
		ray r( a, make_vec(1,0,0) );
		float t;
		BOOST_REQUIRE( intersect_ray_sphere_nearest( r, s_, t ) );
		BOOST_REQUIRE( intersect_ray_sphere_test( r, s_ ) );
		BOOST_REQUIRE( r.sample(t) == s_.center() - make_vec(s_.radius(), 0.0f, 0.0f) );
	}

	BOOST_AUTO_TEST_CASE(test_line_sphere_inside_no_intersect)
	{
	}

	BOOST_AUTO_TEST_CASE(test_line_sphere_outside_no_intersect)
	{
	}

	BOOST_AUTO_TEST_CASE(test_line_sphere_intersect)
	{
	}

	BOOST_AUTO_TEST_CASE(test_sphere_aabb_intersect)
	{
		{ Aabbf aabb( make_vec( -1, -1, -1 ), make_vec( 1, 1, 1 ) );
		Spheref s0( make_vec( 1.6f, 0.0f, 0.0f ), 0.5f );
		Spheref s1( make_vec( 1.0f, 0.0f, 0.0f ), 0.5f );
		Spheref s2( make_vec( 0.0f, 0.0f, 0.0f ), 0.5f );

		BOOST_REQUIRE( !testSphereAabb( s0, aabb ) );
		BOOST_REQUIRE( testSphereAabb( s1, aabb ) );
		BOOST_REQUIRE( testSphereAabb( s2, aabb ) ); }

		// Sphere lies on edge of box
		{ Aabbf aabb( make_vec( -1, -1, -1 ), make_vec( 1, 1, 1 ) );
		Spheref s0( make_vec( 2.0f, 0.0f, 0.0f ), 1.0f );
		Spheref s1( make_vec( -2.0f, 0.0f, 0.0f ), 1.0f );
		BOOST_REQUIRE( !testSphereAabb( s0, aabb ) );
		BOOST_REQUIRE( !testSphereAabb( s1, aabb ) ); }
	}

	BOOST_AUTO_TEST_CASE(test_ray_aabb_intersect)
	{
		Aabbf aabb( make_vec( -1,-1,-1 ), make_vec( 1,1,1 ) );

		{
			// test intersection
			vec origin( make_vec( 5, 2, -3 ) );
			vec target( make_vec( 0, 0, 0 ) );
			ray r( origin, norm(target-origin) );
			scalar t0, t1;
			BOOST_REQUIRE( intersect_ray_aabb(r, aabb, t0, t1 ) );
		}

		{
			// test no intersection
			vec origin( make_vec( 5, 0, 0 ) );
			vec target( make_vec( 0, 2, 0 ) );
			ray r( origin, norm(target-origin) );
			scalar t0, t1;
			BOOST_REQUIRE( !intersect_ray_aabb(r, aabb, t0, t1 ) );
		}

		{
			// test output parameters
			vec origin( make_vec( 5, 0, 0 ) );
			vec target( make_vec( 0, 0, 0 ) );
			ray r( origin, norm(target-origin) );
			scalar t0, t1;
			BOOST_REQUIRE( intersect_ray_aabb(r, aabb, t0, t1 ) );
			BOOST_REQUIRE( value_traits<scalar>::almost_equal( t0, 4.0f ) );
			BOOST_REQUIRE( value_traits<scalar>::almost_equal( t1, 6.0f ) );
		}

		{
			// test ray origin inside box
			vec target( make_vec( 5, 0, 0 ) );
			vec origin( make_vec( 0, 0, 0 ) );
			ray r( origin, norm(target-origin) );
			scalar t0, t1;
			BOOST_REQUIRE( intersect_ray_aabb(r, aabb, t0, t1 ) );
			BOOST_REQUIRE( value_traits<scalar>::almost_equal( t0, 0.0f ) );
			BOOST_REQUIRE( value_traits<scalar>::almost_equal( t1, 1.0f ) );
		}

	}

    BOOST_AUTO_TEST_CASE(test_rayTriangle)
    {
        using namespace math3d;
        using namespace math3d::intersect;

        const vec3f pt1(vec3f::make(-2.0f, 1.0f, 10.0f));
        const vec3f pt2(vec3f::make( 3.0f, 2.0f, 12.0f));
        const vec3f pt3(vec3f::make( 0.5f, -2.5f, 11.0f));
        const Trianglef triangle(pt1, pt2, pt3);

        const vec3f direction = norm(( pt1 + pt2 + pt3 ) / 3.0f);
        const Rayf ray( vec3f::make(0.0f, 0.0f, 0.0f), direction );

        vec3f uvw;
        float t = 0.0f;
        bool hit = rayTriangle( ray, triangle, uvw, t );
        BOOST_REQUIRE( hit );

        // Test miss.
        const Rayf rayMiss(vec3f::make(20, 20, 20), direction);
        hit = rayTriangle( rayMiss, triangle, uvw, t );
        BOOST_REQUIRE( !hit );
    }

    BOOST_AUTO_TEST_CASE(test_lineTriangle)
    {
        using namespace math3d;
        using namespace math3d::intersect;

        const vec3f pt1(vec3f::make(-2.0f, 1.0f, 10.0f));
        const vec3f pt2(vec3f::make( 3.0f, 2.0f, 12.0f));
        const vec3f pt3(vec3f::make( 0.5f, -2.5f, 11.0f));
        const Trianglef triangle(pt1, pt2, pt3);

        const vec3f direction = norm(( pt1 + pt2 + pt3 ) / 3.0f);
        const Rayf ray( vec3f::make(0.0f, 0.0f, 0.0f), direction );
        const Linef line( ray.sample(5.0f), ray.sample(15.0f) );

        vec3f uvw;
        float t = 0.0f;
        bool hit = lineTriangle( line, triangle, uvw, t );
        BOOST_REQUIRE( hit );

        // Test miss.
        const Rayf rayMiss( vec3f::make(20, 20, 20), direction );
        const Linef lineMiss( rayMiss.sample(5.0f), rayMiss.sample(15.0f) );
        hit = lineTriangle( lineMiss, triangle, uvw, t );
        BOOST_REQUIRE( !hit );
    }
    
    BOOST_AUTO_TEST_CASE(test_aabbTriangle)
    {
        using namespace math3d;
        using namespace math3d::intersect;

        const Aabbf aabb(-vec3f(2), vec3f(2));
        const vec3f pt0 = vec3f::make(-4.0f, 1.0f, 3.0f);
        const vec3f pt1 = vec3f::make(3.0f, .8f, 4.0f);
        const vec3f pt2 = vec3f::make( 1.0f, .5f, -3);
        const Trianglef triangle(pt0, pt1, pt2);

        bool result = TestAabbTriangle<Aabbf, Trianglef>::test(aabb, triangle);
        BOOST_REQUIRE(result);
    }

    BOOST_AUTO_TEST_SUITE_END()
