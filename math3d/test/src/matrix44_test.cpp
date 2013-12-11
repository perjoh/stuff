#include "matrix44_test.h"


CPPUNIT_TEST_SUITE_REGISTRATION( Matrix44Test );

	const int d[matrixi::dim][matrixi::dim] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
	matrixi ref_matrixi(d);

	void Matrix44Test::setUp()
	{
	}

	void Matrix44Test::tearDown()
	{
	}

	void Matrix44Test::testIndexing()
	{
		matrixi m(ref_matrixi);

		const int msize = matrixi::dim;
		for (int y = 0; y < msize; ++y)
		for (int x = 0; x < msize; ++x)
		{
			CPPUNIT_ASSERT_EQUAL( d[y][x], m(x, y) );		// indexing by () operator
			if ( matrixi::row_major ) 
				CPPUNIT_ASSERT_EQUAL( d[y][x], m[x + y*msize] );	// indexing by [] operator
		}
	}

	void Matrix44Test::testIdentity()
	{
		matrixi m; m.identity();

		CPPUNIT_ASSERT_EQUAL( m(0,0), 1 );
		CPPUNIT_ASSERT_EQUAL( m(1,0), 0 );
		CPPUNIT_ASSERT_EQUAL( m(2,0), 0 );
		CPPUNIT_ASSERT_EQUAL( m(3,0), 0 );

		CPPUNIT_ASSERT_EQUAL( m(0,1), 0 );
		CPPUNIT_ASSERT_EQUAL( m(1,1), 1 );
		CPPUNIT_ASSERT_EQUAL( m(2,1), 0 );
		CPPUNIT_ASSERT_EQUAL( m(3,1), 0 );

		CPPUNIT_ASSERT_EQUAL( m(0,2), 0 );
		CPPUNIT_ASSERT_EQUAL( m(1,2), 0 );
		CPPUNIT_ASSERT_EQUAL( m(2,2), 1 );
		CPPUNIT_ASSERT_EQUAL( m(3,2), 0 );

		CPPUNIT_ASSERT_EQUAL( m(0,3), 0 );
		CPPUNIT_ASSERT_EQUAL( m(1,3), 0 );
		CPPUNIT_ASSERT_EQUAL( m(2,3), 0 );
		CPPUNIT_ASSERT_EQUAL( m(3,3), 1 );
	}

	void Matrix44Test::testAssignment()
	{
		matrixi ma; ma.identity();
		matrixi mb(ref_matrixi);

		ma = mb;

		CPPUNIT_ASSERT( ma == mb );
	}

	void Matrix44Test::testCompare()
	{
		matrixi m(ref_matrixi);
		CPPUNIT_ASSERT( m == ref_matrixi );
	}

	void Matrix44Test::testMultiply()
	{
		matrixi ma(ref_matrixi);
		matrixi mb(ma);
		matrixi mr(ma*mb);

		if ( !matrixi::row_major ) {
			mr.transpose();
		}

		const int r[matrixi::dim*matrixi::dim] = { 	90, 100, 110, 120,
								202, 228, 254, 280,
								314, 356, 398, 440,
								426, 484, 542, 600 };

		CPPUNIT_ASSERT( mr == matrixi(r) );
	}
