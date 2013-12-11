#include "vector_test.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION( VectorTest );

	typedef math3d::vector<int, 3> vec3i;
	typedef math3d::vector<float, 3> vec3f;

	using namespace math3d;

	void VectorTest::setUp()
	{
	}

	void VectorTest::tearDown()
	{
	}

	void VectorTest::testAlmostEqual()
	{
	    CPPUNIT_ASSERT( value_traits<float>::almost_equal(0.0F, 0.0F) );
	    CPPUNIT_ASSERT( !value_traits<float>::almost_equal(0.0F, 1.0F) );
	    CPPUNIT_ASSERT( !value_traits<float>::almost_equal(1.0F, 0.0F) );
	    CPPUNIT_ASSERT( value_traits<float>::almost_equal(0.000001F, 0.000001F) );
	    CPPUNIT_ASSERT( !value_traits<float>::almost_equal(0.000001F, 0.000002F) );
	    CPPUNIT_ASSERT( value_traits<float>::almost_equal(1.0F, 1.0F) );
	    CPPUNIT_ASSERT( !value_traits<float>::almost_equal(1.0F, 1.00001F) );
	    CPPUNIT_ASSERT( value_traits<float>::almost_equal(10000000.0F, 10000000.0F) );
	    CPPUNIT_ASSERT( !value_traits<float>::almost_equal(10000000.0F, 10050000.0F) );
	}

	void VectorTest::testConstruction()
	{
		vec3i v( make_vec(1,2,3) );

		CPPUNIT_ASSERT_EQUAL(v[0], 1);
		CPPUNIT_ASSERT_EQUAL(v[1], 2);
		CPPUNIT_ASSERT_EQUAL(v[2], 3);
	}

	void VectorTest::testZeroConstruction()
	{
		vec3i v(make_vec(0, 0, 0));

		CPPUNIT_ASSERT_EQUAL(v[0], 0);
		CPPUNIT_ASSERT_EQUAL(v[1], 0);
		CPPUNIT_ASSERT_EQUAL(v[2], 0);
	}

	void VectorTest::testIndexing()
	{
		vec3i v(make_vec(1,2,3));

		CPPUNIT_ASSERT_EQUAL(v[0], 1);
		CPPUNIT_ASSERT_EQUAL(v[1], 2);
		CPPUNIT_ASSERT_EQUAL(v[2], 3);
	}

	void VectorTest::testAssignment()
	{
		vec3i v0(make_vec(1,2,3));
		vec3i v1(v0);

		CPPUNIT_ASSERT_EQUAL(v1[0], 1);
		CPPUNIT_ASSERT_EQUAL(v1[1], 2);
		CPPUNIT_ASSERT_EQUAL(v1[2], 3);

		v0[0] = 4;
		v0[1] = 5;
		v0[2] = 6;

		v1 = v0;

		CPPUNIT_ASSERT_EQUAL(v1[0], 4);
		CPPUNIT_ASSERT_EQUAL(v1[1], 5);
		CPPUNIT_ASSERT_EQUAL(v1[2], 6);
	}

	void VectorTest::testCompare()
	{
		vec3i v1(make_vec(1,2,3));
		vec3i v2(v1);

		CPPUNIT_ASSERT(v1 == v2);
	}

	void VectorTest::testFloatCompare()
	{
		vec3f v1(make_vec(1,2,3));
		vec3f v2(v1);

		CPPUNIT_ASSERT(v1 == v2);
	}

	void VectorTest::testMultiply()
	{
		vec3i v1(make_vec(1,2,3));
		vec3i v2(make_vec(4,5,6));
		vec3i v3(v1*v2);

		CPPUNIT_ASSERT_EQUAL(v3[0], 4);
		CPPUNIT_ASSERT_EQUAL(v3[1], 10);
		CPPUNIT_ASSERT_EQUAL(v3[2], 18);
	}

	void VectorTest::testDivide()
	{
		vec3i v1(make_vec(30,15,24));
		vec3i v2(make_vec(3,5,6));
		vec3i v3(v1/v2);

		CPPUNIT_ASSERT_EQUAL(v3[0], 10);
		CPPUNIT_ASSERT_EQUAL(v3[1], 3);
		CPPUNIT_ASSERT_EQUAL(v3[2], 4);
	}

	void VectorTest::testAdd()
	{
		vec3i v1(make_vec(1,2,3));
		vec3i v2(make_vec(4,5,6));
		vec3i v3(v1+v2);

		CPPUNIT_ASSERT_EQUAL(v3[0], 5);
		CPPUNIT_ASSERT_EQUAL(v3[1], 7);
		CPPUNIT_ASSERT_EQUAL(v3[2], 9);

	}

	void VectorTest::testSubtract()
	{
		vec3i v1(make_vec(1,23,14));
		vec3i v2(make_vec(4,5,6));
		vec3i v3(v1-v2);

		CPPUNIT_ASSERT_EQUAL(v3[0], -3);
		CPPUNIT_ASSERT_EQUAL(v3[1], 18);
		CPPUNIT_ASSERT_EQUAL(v3[2], 8);
	}

	void VectorTest::testMultiplyScalar()
	{
		const int s = 4;

		vec3i v1(make_vec(1,2,3));
		vec3i v3(v1*s);

		CPPUNIT_ASSERT_EQUAL(v3[0], 4);
		CPPUNIT_ASSERT_EQUAL(v3[1], 8);
		CPPUNIT_ASSERT_EQUAL(v3[2], 12);
	}

	void VectorTest::testDivideScalar()
	{
		const int s = 4;

		vec3i v1(make_vec(40,16,24));
		vec3i v3(v1/s);

		CPPUNIT_ASSERT_EQUAL(v3[0], 10);
		CPPUNIT_ASSERT_EQUAL(v3[1], 4);
		CPPUNIT_ASSERT_EQUAL(v3[2], 6);
	}

	void VectorTest::testAddScalar()
	{
		const int s = 4;

		vec3i v1(make_vec(40,16,24));
		vec3i v3(v1+s);

		CPPUNIT_ASSERT_EQUAL(v3[0], 44);
		CPPUNIT_ASSERT_EQUAL(v3[1], 20);
		CPPUNIT_ASSERT_EQUAL(v3[2], 28);
	}

	void VectorTest::testSubtractScalar()
	{
		const int s = 4;

		vec3i v1(make_vec(40, 16, 24));
		vec3i v3(v1-s);

		CPPUNIT_ASSERT_EQUAL(v3[0], 36);
		CPPUNIT_ASSERT_EQUAL(v3[1], 12);
		CPPUNIT_ASSERT_EQUAL(v3[2], 20);
	}

	void VectorTest::testLength()
	{
		vec3i v(make_vec(20, 4, 7));

		CPPUNIT_ASSERT_EQUAL(v.length(), 21); //21.563...
	}

	void VectorTest::testNormalize()
	{
		vec3f v(make_vec(20, 4, 7));

		v.norm();
		const float len = v.length();

		CPPUNIT_ASSERT( math3d::value_traits<vec3f::value_type>::almost_equal(len, 1.0F) );
	}

	void VectorTest::testDotProduct()
	{
		vec3i v1(make_vec(2,3,4));

		vec3i v2(make_vec(5,6,7));

		CPPUNIT_ASSERT_EQUAL(static_cast<int>(dot(v1,v2)), 56);
		//CPPUNIT_ASSERT_EQUAL(dot(v1, v2), 56);
	}

	void VectorTest::testCrossProduct()
	{
		vec3f v1(make_vec(1, 0, 0));
		vec3f v2(make_vec(0, 1, 0));

		vec3f v3 = cross(v1, v2);
		vec3f ref(make_vec(0, 0, 1));

		CPPUNIT_ASSERT(v3 == ref);
	}

	void VectorTest::testMetaPrograms()
	{
		int a[5] = { 2, 3, 4, 5, 6 };
		int result = do_binary_op_cumulative<5, int, op_mul>::exec(a);
		CPPUNIT_ASSERT( result == 720 );
	}
