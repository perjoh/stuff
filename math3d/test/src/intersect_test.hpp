#ifndef intersecttest_hpp
#define intersecttest_hpp

#include <cppunit/extensions/HelperMacros.h>
#include <math3d/vector.hpp>
#include <math3d/ray.hpp>
#include <math3d/sphere.hpp>
#include <math3d/line.hpp>
#include <math3d/box.hpp>
#include <math3d/triangle.hpp>
#include <math3d/mathtypes.hpp>

	class IntersectTest : public CppUnit::TestFixture
	{
		CPPUNIT_TEST_SUITE(IntersectTest);
		CPPUNIT_TEST(test_ray_sphere_inside);
		CPPUNIT_TEST(test_ray_sphere_no_intersect);
		CPPUNIT_TEST(test_ray_sphere_intersect);
		CPPUNIT_TEST(test_line_sphere_inside_no_intersect);
		CPPUNIT_TEST(test_line_sphere_inside_no_intersect);
		CPPUNIT_TEST(test_line_sphere_intersect);
		CPPUNIT_TEST(test_sphere_aabb_intersect);
		CPPUNIT_TEST(test_ray_aabb_intersect);
		CPPUNIT_TEST(test_rayTriangle);
		CPPUNIT_TEST(test_lineTriangle);
		CPPUNIT_TEST(test_aabbTriangle);
		CPPUNIT_TEST_SUITE_END();

	public :
		void setUp();
		void tearDown();

	private :
		void	test_ray_sphere_inside();
		void	test_ray_sphere_no_intersect();
		void	test_ray_sphere_intersect();
		//void	test_ray_sphere_tangent();
		void	test_line_sphere_inside_no_intersect();
		void	test_line_sphere_outside_no_intersect();
		void	test_line_sphere_intersect();
		void	test_sphere_aabb_intersect();
		void	test_ray_aabb_intersect();

		typedef math3d::Ray<float> Rayf;
		typedef math3d::Triangle<float> Trianglef;
		typedef math3d::Line<float> Linef;

		void test_rayTriangle()
		{
			using namespace math3d;
			using namespace math3d::intersect;

			const vec3f pt1(vec3f::make(-2.0f, 1.0f, 10.0f));
			const vec3f pt2(vec3f::make( 3.0f, 2.0f, 12.0f));
			const vec3f pt3(vec3f::make( 0.5f, -2.5f, 11.0f));
			const Trianglef triangle(pt1, pt2, pt3);

			const vec3f direction = norm(( pt1 + pt2 + pt3 ) / 3.0f);
			const Rayf ray( vec3f::make(0.0f, 0.0f, 0.0f), direction );

            vec3f uvw;
			float t = 0.0f;
			bool hit = rayTriangle( ray, triangle, uvw, t );
			CPPUNIT_ASSERT( hit );

            // Test miss.
            const Rayf rayMiss(vec3f::make(20, 20, 20), direction);
			hit = rayTriangle( rayMiss, triangle, uvw, t );
			CPPUNIT_ASSERT( !hit );
		}

		void test_lineTriangle()
		{
			using namespace math3d;
			using namespace math3d::intersect;

			const vec3f pt1(vec3f::make(-2.0f, 1.0f, 10.0f));
			const vec3f pt2(vec3f::make( 3.0f, 2.0f, 12.0f));
			const vec3f pt3(vec3f::make( 0.5f, -2.5f, 11.0f));
			const Trianglef triangle(pt1, pt2, pt3);

			const vec3f direction = norm(( pt1 + pt2 + pt3 ) / 3.0f);
			const Rayf ray( vec3f::make(0.0f, 0.0f, 0.0f), direction );
			const Linef line( ray.sample(5.0f), ray.sample(15.0f) );

            vec3f uvw;
			float t = 0.0f;
			bool hit = lineTriangle( line, triangle, uvw, t );
			CPPUNIT_ASSERT( hit );

            // Test miss.
			const Rayf rayMiss( vec3f::make(20, 20, 20), direction );
			const Linef lineMiss( rayMiss.sample(5.0f), rayMiss.sample(15.0f) );
			hit = lineTriangle( lineMiss, triangle, uvw, t );
			CPPUNIT_ASSERT( !hit );
		}
        
        void test_aabbTriangle()
        {
			using namespace math3d;
			using namespace math3d::intersect;

            typedef math3d::Aabb<float> Aabbf;
            const Aabbf aabb(-vec3f(2), vec3f(2));
            const vec3f pt0 = vec3f::make(-4.0f, 1.0f, 3.0f);
            const vec3f pt1 = vec3f::make(3.0f, .8f, 4.0f);
            const vec3f pt2 = vec3f::make( 1.0f, .5f, -3);
            const Trianglef triangle(pt0, pt1, pt2);

            bool result = TestAabbTriangle<Aabbf, Trianglef>::test(aabb, triangle);
            CPPUNIT_ASSERT(result);
        }

		//void	test_testTriangleSphere();
		//void	test_testTriangleAabb();

	private :
		typedef float scalar;
		typedef math3d::Ray<scalar> ray;
		typedef math3d::Sphere<scalar> Sphere;
		typedef math3d::Aabb<scalar> Aabb;
		typedef ray::vector_type vec;

		Sphere s_;
	};


#endif // intersecttest_hpp
