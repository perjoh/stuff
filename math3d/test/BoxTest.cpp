#include <boost/test/unit_test.hpp>
#include "../include/math3d/box.hpp"
#include "../include/math3d/AxisAlignedPlane.hpp"
#include "../include/math3d/Sphere.hpp"
#include "../include/math3d/mathtypes.hpp"

    namespace {

        struct Fixture
        {
        };
    }

	using namespace math3d;
	typedef Aabb<int> Boxi;
	typedef Aabb<float> Boxf;
	typedef AxisAlignedPlane<int> Aa_planei;

    BOOST_FIXTURE_TEST_SUITE(Math3dBoxSuite, Fixture)

    BOOST_AUTO_TEST_CASE(testConstruction)
    {
        Boxi box( make_vec( -2, 5, 3 ), make_vec( 5, 11, 11 ) );
        BOOST_REQUIRE( box.corner()[ 0 ] == -2 );
        BOOST_REQUIRE( box.corner()[ 1 ] == 5 );
        BOOST_REQUIRE( box.corner()[ 2 ] == 3 );
        BOOST_REQUIRE( box.dim()[ 0 ] == 7 );
        BOOST_REQUIRE( box.dim()[ 1 ] == 6 );
        BOOST_REQUIRE( box.dim()[ 2 ] == 8 );
    }

    BOOST_AUTO_TEST_CASE(testSplit)
    {
		Boxi box( make_vec( 0, 0, 0 ), make_vec( 10, 7, 4 ) );

		BOOST_REQUIRE( box.volume() == 10*7*4 );

        // Split along x-axis
		Boxi box_a, box_b;
		bool ret = box.split( Aa_planei( X, 5 ), box_a, box_b );
		BOOST_REQUIRE( ret );

		BOOST_REQUIRE_EQUAL( box_a.corner()[0], 0 );
		BOOST_REQUIRE_EQUAL( box_a.corner()[1], 0 );
		BOOST_REQUIRE_EQUAL( box_a.corner()[2], 0 );
		BOOST_REQUIRE_EQUAL( box_a.dim()[0], 5 );
		BOOST_REQUIRE_EQUAL( box_a.dim()[1], 7 );
		BOOST_REQUIRE_EQUAL( box_a.dim()[2], 4 );

		BOOST_REQUIRE_EQUAL( box_b.corner()[0], 5 );
		BOOST_REQUIRE_EQUAL( box_b.corner()[1], 0 );
		BOOST_REQUIRE_EQUAL( box_b.corner()[2], 0 );
		BOOST_REQUIRE_EQUAL( box_b.dim()[0], 5 );
		BOOST_REQUIRE_EQUAL( box_b.dim()[1], 7 );
		BOOST_REQUIRE_EQUAL( box_b.dim()[2], 4 );

        // Split along y-axis
		ret = box.split( Aa_planei( Y, 3 ), box_a, box_b );
		BOOST_REQUIRE( ret );

		BOOST_REQUIRE_EQUAL( box_a.corner()[0], 0 );
		BOOST_REQUIRE_EQUAL( box_a.corner()[1], 0 );
		BOOST_REQUIRE_EQUAL( box_a.corner()[2], 0 );
		BOOST_REQUIRE_EQUAL( box_a.dim()[0], 10 );
		BOOST_REQUIRE_EQUAL( box_a.dim()[1], 3 );
		BOOST_REQUIRE_EQUAL( box_a.dim()[2], 4 );

		BOOST_REQUIRE_EQUAL( box_b.corner()[0], 0 );
		BOOST_REQUIRE_EQUAL( box_b.corner()[1], 3 );
		BOOST_REQUIRE_EQUAL( box_b.corner()[2], 0 );
		BOOST_REQUIRE_EQUAL( box_b.dim()[0], 10 );
		BOOST_REQUIRE_EQUAL( box_b.dim()[1], 4 );
		BOOST_REQUIRE_EQUAL( box_b.dim()[2], 4 );

        // Split along z-axis
		ret = box.split( Aa_planei( Z, 1 ), box_a, box_b );
		BOOST_REQUIRE( ret );

		BOOST_REQUIRE_EQUAL( box_a.corner()[0], 0 );
		BOOST_REQUIRE_EQUAL( box_a.corner()[1], 0 );
		BOOST_REQUIRE_EQUAL( box_a.corner()[2], 0 );
		BOOST_REQUIRE_EQUAL( box_a.dim()[0], 10 );
		BOOST_REQUIRE_EQUAL( box_a.dim()[1], 7 );
		BOOST_REQUIRE_EQUAL( box_a.dim()[2], 1 );

		BOOST_REQUIRE_EQUAL( box_b.corner()[0], 0 );
		BOOST_REQUIRE_EQUAL( box_b.corner()[1], 0 );
		BOOST_REQUIRE_EQUAL( box_b.corner()[2], 1 );
		BOOST_REQUIRE_EQUAL( box_b.dim()[0], 10 );
		BOOST_REQUIRE_EQUAL( box_b.dim()[1], 7 );
		BOOST_REQUIRE_EQUAL( box_b.dim()[2], 3 );

		// Test failed splits
		ret = box.split( Aa_planei( X, 12 ), box_a, box_b );
		BOOST_REQUIRE( !ret );
		ret = box.split( Aa_planei( X, -1 ), box_a, box_b );
		BOOST_REQUIRE( !ret );
		ret = box.split( Aa_planei( Y, 8 ), box_a, box_b );
		BOOST_REQUIRE( !ret );
		ret = box.split( Aa_planei( Y, -1 ), box_a, box_b );
		BOOST_REQUIRE( !ret );
		ret = box.split( Aa_planei( Z, 5 ), box_a, box_b );
		BOOST_REQUIRE( !ret );
		ret = box.split( Aa_planei( Z, -1 ), box_a, box_b );
		BOOST_REQUIRE( !ret );
    }

    BOOST_AUTO_TEST_CASE(testBoundingBox)
    {
		typedef float Scalar;
		typedef Sphere<Scalar> Sphere;
		std::vector<Sphere> geometry;
		geometry.push_back( Sphere( make_vec( 5, 5, 6 ), 3) );
		geometry.push_back( Sphere( make_vec( 10, 13, 2 ), 2) );
		geometry.push_back( Sphere( make_vec( 17, 7, 12 ), 4) );
		geometry.push_back( Sphere( make_vec( 3, 16, 4 ), 1) );

		typedef math3d::Aabb<Scalar> Aabb;
		const Aabb aabb = makeBoundingBox<Aabb>( geometry.begin(), geometry.end() );

		BOOST_REQUIRE( aabb.min() == make_vec(2.0f, 2.0f, 0.0f) );
		BOOST_REQUIRE( aabb.max() == make_vec(21.0f, 17.0f, 16.0f) );
    }

    BOOST_AUTO_TEST_CASE(testSubDivideOct)
    {
		typedef Aabb<float> Aabbf;

		Aabbf sourceBox( vec3f::make(0,0,0), vec3f::make(1,1,1) );

		Aabbf result[8];

		subDivideOct< Aabbf, Aabbf* >( sourceBox, &result[0], &result[8] );

		for ( Aabbf* it = &result[0]; it != &result[8]; ++it ) {
			BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(it->width(), 0.5f) );
			BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(it->height(), 0.5f) );
			BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(it->depth(), 0.5f) );
		}

		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[0].min()[0], 0.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[0].min()[1], 0.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[0].min()[2], 0.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[0].max()[0], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[0].max()[1], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[0].max()[2], 0.5f ) );

		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[1].min()[0], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[1].min()[1], 0.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[1].min()[2], 0.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[1].max()[0], 1.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[1].max()[1], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[1].max()[2], 0.5f ) );

		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[2].min()[0], 0.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[2].min()[1], 0.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[2].min()[2], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[2].max()[0], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[2].max()[1], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[2].max()[2], 1.0f ) );

		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[3].min()[0], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[3].min()[1], 0.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[3].min()[2], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[3].max()[0], 1.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[3].max()[1], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[3].max()[2], 1.0f ) );

		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[4].min()[0], 0.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[4].min()[1], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[4].min()[2], 0.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[4].max()[0], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[4].max()[1], 1.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[4].max()[2], 0.5f ) );

		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[5].min()[0], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[5].min()[1], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[5].min()[2], 0.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[5].max()[0], 1.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[5].max()[1], 1.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[5].max()[2], 0.5f ) );

		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[6].min()[0], 0.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[6].min()[1], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[6].min()[2], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[6].max()[0], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[6].max()[1], 1.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[6].max()[2], 1.0f ) );

		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[7].min()[0], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[7].min()[1], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[7].min()[2], 0.5f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[7].max()[0], 1.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[7].max()[1], 1.0f ) );
		BOOST_REQUIRE( math3d::value_traits<float>::almost_equal(result[7].max()[2], 1.0f ) );
    }

    BOOST_AUTO_TEST_CASE(testWidestAxis)
    {
        Boxi box( make_vec(0, 0, 0), make_vec(10, 1, 2) );
        BOOST_REQUIRE_EQUAL( box.widestAxis(), 0 );

        box = Boxi( make_vec(-10, 4, -2), make_vec(10, 25, 2) );
        BOOST_REQUIRE_EQUAL( box.widestAxis(), 1 );

        box = Boxi( make_vec(-10, 5, -2), make_vec(10, 25, 22) );
        BOOST_REQUIRE_EQUAL( box.widestAxis(), 2 );
    }

    BOOST_AUTO_TEST_CASE( testSurfaceArea )
    {
        Boxi box( make_vec( 0, 0, 0), make_vec( 5, 6, 7 ) );
        BOOST_REQUIRE_EQUAL( box.surfaceArea(), 5*6 + 5*7 + 6*7 );
    }

    BOOST_AUTO_TEST_SUITE_END()
