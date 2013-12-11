#include <boost/test/unit_test.hpp>
#include "../include/math3d/ray.hpp"

namespace {

	using namespace math3d;
	typedef float Scalar;
	typedef Ray<Scalar> Ray_t;
	typedef Ray_t::vector_type Vec;
	typedef AxisAlignedPlane<Scalar> Aap;

    struct Fixture {

        Fixture() {
        }
    };

};


BOOST_FIXTURE_TEST_SUITE(Math3dRaySuite, Fixture)


BOOST_AUTO_TEST_CASE(testSplit) {

    { Vec target(make_vec(5,5,0));
    Vec origin(make_vec(0,0,0));
    Ray_t ray( origin, norm(target-origin) );
    Aap plane( X, 1 );
    Scalar t;
    BOOST_REQUIRE( ray.split( plane, t ) );
    BOOST_REQUIRE( value_traits<Scalar>::almost_equal( ray.sample(t)[0],  1.0f ) ); }

    // test negative split
    { Vec target(make_vec(-5,5,0));
    Vec origin(make_vec(0,0,0));
    Ray_t ray( origin, norm(target-origin) );
    Aap plane( X, -1 );
    Scalar t;
    BOOST_REQUIRE( ray.split( plane, t ) );
    BOOST_REQUIRE( value_traits<Scalar>::almost_equal( ray.sample(t)[0], -1.0f ) ); }

}

BOOST_AUTO_TEST_CASE(testSplit2) {

    const Plane<Scalar> plane(make_vec(-10, 10, 10), make_vec(10, 10, 10), make_vec(5, -10, 10));

    {
        const Ray<Scalar> ray(make_vec(0, 0, -10), make_vec(0, 0, 1));
        Scalar t = 0;
        const bool result = ray.split(plane, t);
        BOOST_REQUIRE(result);
        BOOST_REQUIRE_CLOSE(t, Scalar(20), Scalar(0.00001));
    }

    {
        const Ray<Scalar> ray(make_vec(0, 0, -10), make_vec(0, 0, -1));
        Scalar t = 123;
        const bool result = ray.split(plane, t);
        BOOST_REQUIRE(!result);
        BOOST_REQUIRE_CLOSE(t, Scalar(123), Scalar(0.00001)); // Test t remains untouched.
    }
}


BOOST_AUTO_TEST_SUITE_END()
