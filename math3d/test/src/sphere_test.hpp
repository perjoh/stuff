#ifndef test_template_hpp
#define test_template_hpp

#include <cppunit/extensions/HelperMacros.h>

#define MY_TEST_CLASS_NAME SphereTest

	class MY_TEST_CLASS_NAME : public CppUnit::TestFixture
	{
		CPPUNIT_TEST_SUITE(MY_TEST_CLASS_NAME);
		CPPUNIT_TEST(test_min_max);
		CPPUNIT_TEST_SUITE_END();

	public :
		void	setUp();
		void	tearDown();

	private :
		void	test_min_max();
	};


#endif // intersecttest_hpp
