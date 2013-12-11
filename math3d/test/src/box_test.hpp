#ifndef box_test_hpp
#define box_test_hpp

#include <cppunit/extensions/HelperMacros.h>

#define MY_TEST_CLASS_NAME BoxTest

	class MY_TEST_CLASS_NAME : public CppUnit::TestFixture
	{
		CPPUNIT_TEST_SUITE(MY_TEST_CLASS_NAME);
		CPPUNIT_TEST(test_construction);
		CPPUNIT_TEST(test_split);
		CPPUNIT_TEST(test_bounding_box);
		CPPUNIT_TEST(test_subDivideOct);
		CPPUNIT_TEST_SUITE_END();

	public :
		void	setUp();
		void	tearDown();

	private :
		void	test_construction();
		void	test_split();
		void	test_bounding_box();
		void	test_subDivideOct();
	};


#endif // intersecttest_hpp
