#ifndef test_template_hpp
#define test_template_hpp

#include <cppunit/extensions/HelperMacros.h>

#define MY_TEST_CLASS_NAME RayTest

	class MY_TEST_CLASS_NAME : public CppUnit::TestFixture
	{
		CPPUNIT_TEST_SUITE(MY_TEST_CLASS_NAME);
		CPPUNIT_TEST(test_construction);
		CPPUNIT_TEST(test_origin);
		CPPUNIT_TEST(test_direction);
		CPPUNIT_TEST(test_sample);
		CPPUNIT_TEST(test_split);
		CPPUNIT_TEST_SUITE_END();

	public :
		void	setUp();
		void	tearDown();

	private :
		void	test_construction();
		void	test_origin();
		void	test_direction();
		void	test_sample();
		void	test_split();
	};


#endif // intersecttest_hpp
