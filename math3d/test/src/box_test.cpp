#include "box_test.hpp"
#include <math3d/box.hpp>
#include <math3d/plane.hpp>
#include <math3d/sphere.hpp>
#include <boost/shared_ptr.hpp>
#include <math3d/mathtypes.hpp>
#include <iostream>

CPPUNIT_TEST_SUITE_REGISTRATION( MY_TEST_CLASS_NAME );

	using namespace math3d;
	typedef Aabb<int> Boxi;
	typedef Aabb<float> Boxf;
	typedef Aa_plane<int> Aa_planei;

	void MY_TEST_CLASS_NAME::setUp()
	{
	}

	void MY_TEST_CLASS_NAME::tearDown()
	{
	}

	void MY_TEST_CLASS_NAME::test_construction()
	{
		Boxi box( make_vec( -2, 5, 3 ), make_vec( 5, 11, 11 ) );
		CPPUNIT_ASSERT( box.corner()[ 0 ] == -2 );
		CPPUNIT_ASSERT( box.corner()[ 1 ] == 5 );
		CPPUNIT_ASSERT( box.corner()[ 2 ] == 3 );
		CPPUNIT_ASSERT( box.dim()[ 0 ] == 7 );
		CPPUNIT_ASSERT( box.dim()[ 1 ] == 6 );
		CPPUNIT_ASSERT( box.dim()[ 2 ] == 8 );
	}

	void MY_TEST_CLASS_NAME::test_split()
	{
		Boxi box( make_vec( 0, 0, 0 ), make_vec( 10, 7, 4 ) );

		CPPUNIT_ASSERT( box.volume() == 10*7*4 );

        // Split along x-axis
		Boxi box_a, box_b;
		bool ret = box.split( Aa_planei( X_axis, 5 ), box_a, box_b );
		CPPUNIT_ASSERT( ret );

		CPPUNIT_ASSERT_EQUAL( box_a.corner()[0], 0 );
		CPPUNIT_ASSERT_EQUAL( box_a.corner()[1], 0 );
		CPPUNIT_ASSERT_EQUAL( box_a.corner()[2], 0 );
		CPPUNIT_ASSERT_EQUAL( box_a.dim()[0], 5 );
		CPPUNIT_ASSERT_EQUAL( box_a.dim()[1], 7 );
		CPPUNIT_ASSERT_EQUAL( box_a.dim()[2], 4 );

		CPPUNIT_ASSERT_EQUAL( box_b.corner()[0], 5 );
		CPPUNIT_ASSERT_EQUAL( box_b.corner()[1], 0 );
		CPPUNIT_ASSERT_EQUAL( box_b.corner()[2], 0 );
		CPPUNIT_ASSERT_EQUAL( box_b.dim()[0], 5 );
		CPPUNIT_ASSERT_EQUAL( box_b.dim()[1], 7 );
		CPPUNIT_ASSERT_EQUAL( box_b.dim()[2], 4 );

        // Split along y-axis
		ret = box.split( Aa_planei( Y_axis, 3 ), box_a, box_b );
		CPPUNIT_ASSERT( ret );

		CPPUNIT_ASSERT_EQUAL( box_a.corner()[0], 0 );
		CPPUNIT_ASSERT_EQUAL( box_a.corner()[1], 0 );
		CPPUNIT_ASSERT_EQUAL( box_a.corner()[2], 0 );
		CPPUNIT_ASSERT_EQUAL( box_a.dim()[0], 10 );
		CPPUNIT_ASSERT_EQUAL( box_a.dim()[1], 3 );
		CPPUNIT_ASSERT_EQUAL( box_a.dim()[2], 4 );

		CPPUNIT_ASSERT_EQUAL( box_b.corner()[0], 0 );
		CPPUNIT_ASSERT_EQUAL( box_b.corner()[1], 3 );
		CPPUNIT_ASSERT_EQUAL( box_b.corner()[2], 0 );
		CPPUNIT_ASSERT_EQUAL( box_b.dim()[0], 10 );
		CPPUNIT_ASSERT_EQUAL( box_b.dim()[1], 4 );
		CPPUNIT_ASSERT_EQUAL( box_b.dim()[2], 4 );

        // Split along z-axis
		ret = box.split( Aa_planei( Z_axis, 1 ), box_a, box_b );
		CPPUNIT_ASSERT( ret );

		CPPUNIT_ASSERT_EQUAL( box_a.corner()[0], 0 );
		CPPUNIT_ASSERT_EQUAL( box_a.corner()[1], 0 );
		CPPUNIT_ASSERT_EQUAL( box_a.corner()[2], 0 );
		CPPUNIT_ASSERT_EQUAL( box_a.dim()[0], 10 );
		CPPUNIT_ASSERT_EQUAL( box_a.dim()[1], 7 );
		CPPUNIT_ASSERT_EQUAL( box_a.dim()[2], 1 );

		CPPUNIT_ASSERT_EQUAL( box_b.corner()[0], 0 );
		CPPUNIT_ASSERT_EQUAL( box_b.corner()[1], 0 );
		CPPUNIT_ASSERT_EQUAL( box_b.corner()[2], 1 );
		CPPUNIT_ASSERT_EQUAL( box_b.dim()[0], 10 );
		CPPUNIT_ASSERT_EQUAL( box_b.dim()[1], 7 );
		CPPUNIT_ASSERT_EQUAL( box_b.dim()[2], 3 );

		// Test failed splits
		ret = box.split( Aa_planei( X_axis, 12 ), box_a, box_b );
		CPPUNIT_ASSERT( !ret );
		ret = box.split( Aa_planei( X_axis, -1 ), box_a, box_b );
		CPPUNIT_ASSERT( !ret );
		ret = box.split( Aa_planei( Y_axis, 8 ), box_a, box_b );
		CPPUNIT_ASSERT( !ret );
		ret = box.split( Aa_planei( Y_axis, -1 ), box_a, box_b );
		CPPUNIT_ASSERT( !ret );
		ret = box.split( Aa_planei( Z_axis, 5 ), box_a, box_b );
		CPPUNIT_ASSERT( !ret );
		ret = box.split( Aa_planei( Z_axis, -1 ), box_a, box_b );
		CPPUNIT_ASSERT( !ret );
	}

	void MY_TEST_CLASS_NAME::test_bounding_box()
	{
		typedef float Scalar;
		typedef Sphere<Scalar> Sphere;
		typedef boost::shared_ptr<Sphere> Sphere_ptr;
		std::vector<Sphere_ptr> geometry;
		geometry.push_back( Sphere_ptr( new Sphere( make_vec( 5, 5, 6 ), 3) ) );
		geometry.push_back( Sphere_ptr( new Sphere( make_vec( 10, 13, 2 ), 2) ) );
		geometry.push_back( Sphere_ptr( new Sphere( make_vec( 17, 7, 12 ), 4) ) );
		geometry.push_back( Sphere_ptr( new Sphere( make_vec( 3, 16, 4 ), 1) ) );

		typedef math3d::Aabb<Scalar> Aabb;
		const Aabb aabb = get_bounding_box<Aabb>( geometry.begin(), geometry.end() );

		CPPUNIT_ASSERT( aabb.min() == make_vec(2.0f, 2.0f, 0.0f) );
		CPPUNIT_ASSERT( aabb.max() == make_vec(21.0f, 17.0f, 16.0f) );
	}

	void MY_TEST_CLASS_NAME::test_subDivideOct()
	{
		typedef Aabb<float> Aabbf;

		Aabbf sourceBox( vec3f::make(0,0,0), vec3f::make(1,1,1) );

		Aabbf result[8];

		subDivideOct< Aabbf, Aabbf* >( sourceBox, &result[0], &result[8] );

		for ( Aabbf* it = &result[0]; it != &result[8]; ++it ) {
			CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(it->width(), 0.5f) );
			CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(it->height(), 0.5f) );
			CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(it->depth(), 0.5f) );
		}

		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[0].min()[0], 0.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[0].min()[1], 0.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[0].min()[2], 0.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[0].max()[0], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[0].max()[1], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[0].max()[2], 0.5f ) );

		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[1].min()[0], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[1].min()[1], 0.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[1].min()[2], 0.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[1].max()[0], 1.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[1].max()[1], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[1].max()[2], 0.5f ) );

		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[2].min()[0], 0.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[2].min()[1], 0.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[2].min()[2], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[2].max()[0], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[2].max()[1], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[2].max()[2], 1.0f ) );

		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[3].min()[0], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[3].min()[1], 0.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[3].min()[2], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[3].max()[0], 1.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[3].max()[1], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[3].max()[2], 1.0f ) );

		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[4].min()[0], 0.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[4].min()[1], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[4].min()[2], 0.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[4].max()[0], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[4].max()[1], 1.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[4].max()[2], 0.5f ) );

		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[5].min()[0], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[5].min()[1], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[5].min()[2], 0.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[5].max()[0], 1.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[5].max()[1], 1.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[5].max()[2], 0.5f ) );

		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[6].min()[0], 0.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[6].min()[1], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[6].min()[2], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[6].max()[0], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[6].max()[1], 1.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[6].max()[2], 1.0f ) );

		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[7].min()[0], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[7].min()[1], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[7].min()[2], 0.5f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[7].max()[0], 1.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[7].max()[1], 1.0f ) );
		CPPUNIT_ASSERT( math3d::value_traits<float>::almost_equal(result[7].max()[2], 1.0f ) );
	}
