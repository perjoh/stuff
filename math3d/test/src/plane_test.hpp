#ifndef test_template_hpp
#define test_template_hpp

#include <cppunit/extensions/HelperMacros.h>

#define MY_TEST_CLASS_NAME PlaneTest

	class MY_TEST_CLASS_NAME : public CppUnit::TestFixture
	{
		CPPUNIT_TEST_SUITE(MY_TEST_CLASS_NAME);
		CPPUNIT_TEST(test_construction);
		CPPUNIT_TEST(test_normal);
		CPPUNIT_TEST(test_distance);
		CPPUNIT_TEST(test_front_side);
		CPPUNIT_TEST(test_equal_op);
		CPPUNIT_TEST_SUITE_END();

	public :
		void	setUp();
		void	tearDown();

	private :
		void	test_construction();
		void	test_normal();
		void	test_distance();
		void	test_front_side();
		void	test_equal_op();
	};


#endif // intersecttest_hpp
