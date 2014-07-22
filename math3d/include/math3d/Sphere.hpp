#pragma once

#include "intersections.hpp"
#include "ray.hpp"
#include "line.hpp"
#include "box.hpp"

namespace math3d {

	template <typename T>
	class Sphere {
	public :
		typedef T value_type;
		typedef vector<T, 3> vector_type;

	public :
		Sphere()
        { }

		Sphere( const vector_type& center, value_type radius )
            : center_( center )
            , radius_( radius )
        { }

	public :
		const vector_type& center() const {
			return center_;
		}

		const value_type radius() const {
			return radius_;
		}

	public :
		const vector_type min() const {
			return center() - radius();
		}

		const vector_type max() const {
			return center() + radius();
		}

		const value_type min( int axis ) const {
			return center()[ axis ] - radius();
		}

		const value_type max( int axis ) const {
			return center()[ axis ] + radius();
		}

	public :
		// TODO Obsolete, remove this
		template <typename Aabb>
		bool intersectAabb( const Aabb& aabb ) const {
			return intersect::testSphereAabb( *this, aabb );
		}

		bool testIntersect( const Aabb<T>& aabb ) const {
			return intersect::testSphereAabb( *this, aabb );
		}

		bool testIntersect( const Ray<T>& ray ) const
		{
			return intersect::intersect_ray_sphere_test( ray, *this );
		}

		T intersect( const Ray<T>& ray ) const
		{
			// TODO Fix this when intersect functions return a T value instead of a boolean.
			T t;
			if (!intersect::intersect_ray_sphere_nearest(ray, *this, t))
				t = T(-1);
			return t;
		}

		bool testIntersect( const Line<T>& line ) const
		{
			return intersect::intersect_line_sphere_test( line, *this );
		}

		T intersect( const Line<T>& line ) const
		{
			// TODO Fix this when intersect functions return a T value instead of a boolean.
			T t;
			if (!intersect::intersect_line_sphere_nearest(line, *this, t))
				t = T(-1);
			return t;
		}

	public :
		const Aabb<value_type> getBoundingBox() const {
			return Aabb<value_type>( min(), max() );
		}

	private :
		vector_type center_;
		value_type radius_;
	};

}

