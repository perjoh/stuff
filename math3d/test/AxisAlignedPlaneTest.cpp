#include <boost/test/unit_test.hpp>
#include "../include/math3d/AxisAlignedPlane.hpp"
#include "../include/math3d/Triangle.hpp"

typedef float Float;
typedef math3d::Plane<Float> TestPlane;
typedef math3d::AxisAlignedPlane<Float> Aap;
typedef math3d::Triangle<Float> Tri;
typedef Aap::vector_type vec;

namespace 
{
    struct Fixture {};
}

BOOST_FIXTURE_TEST_SUITE(Math3dAxisAlignedPlaneSuite, Fixture)

using namespace math3d;

BOOST_AUTO_TEST_CASE(testConstructFromPlane) {

    const TestPlane px( vec::make(1, 0, 0), 0 );
    const TestPlane py( vec::make(0, -1, 0), 0 );
    const TestPlane pz( vec::make(0, 0, 1), 0 );

    const Aap aapx( px );
    const Aap aapy( py );
    const Aap aapz( pz );

    BOOST_REQUIRE( aapx.axis() == X );
    BOOST_REQUIRE( aapy.axis() == Y );
    BOOST_REQUIRE( aapz.axis() == Z );
}


BOOST_AUTO_TEST_CASE(testSideOf) {

    Aap p0(X, 1);

    BOOST_CHECK_EQUAL(p0.isOnPositiveSide(vec::make(2,0,0)), true);
    BOOST_CHECK_EQUAL(p0.isOnPositiveSide(vec::make(.5,0,0)), false);

    p0.flip();

    BOOST_CHECK_EQUAL(p0.isOnPositiveSide(vec::make(2,0,0)), false);
    BOOST_CHECK_EQUAL(p0.isOnPositiveSide(vec::make(.5,0,0)), true);
}


BOOST_AUTO_TEST_CASE( testIntersectTriangle )
{
    const Tri triA( vec::make( -1, 10, 20), vec::make( 5.5, 5, 0), vec::make( 3, 12, 10) );
    const Tri triB( vec::make( 5.5, -5, -10), vec::make( 10, -2, -10 ), vec::make( 12, -7, 5) );
    const Aap aapX( X, 5.0 );
    BOOST_CHECK_EQUAL(aapX.testTriangle(triA), true);
    BOOST_CHECK_EQUAL(aapX.testTriangle(triB), false);
    const Aap aapY( Y, 7 );
    BOOST_CHECK_EQUAL(aapY.testTriangle(triA), true);
    BOOST_CHECK_EQUAL(aapY.testTriangle(triB), false);
    const Aap aapZ( Z, 6 );
    BOOST_CHECK_EQUAL(aapZ.testTriangle(triA), true);
    BOOST_CHECK_EQUAL(aapZ.testTriangle(triB), false);
}


BOOST_AUTO_TEST_SUITE_END()
