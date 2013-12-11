#ifndef math3d_primitive_hpp
#define math3d_primitive_hpp

#include "ray.hpp"
#include "line.hpp"
#include "box.hpp"

namespace math3d {

	template <typename T>
	class Primitive {
	public :
		typedef T value_type;

	public :
		virtual ~Primitive() { }

	public :
		virtual bool intersect_ray_nearest( const Ray<value_type>& ray, value_type& t ) const = 0;
		virtual bool intersect_ray_test( const Ray<value_type>& ray ) const = 0;

		virtual bool intersect_line_nearest( const Line<value_type>& line, value_type& t ) const = 0;
		virtual bool intersect_line_test( const Line<value_type>& line ) const = 0;

		virtual bool intersect_aabb_test( const Aabb<value_type>& aabb ) const = 0;
	};

	template <typename T>
	class Finite_prim : public Primitive<T> {
	public :
		virtual const T min( int axis ) const = 0;
		virtual const T max( int axis ) const = 0;

		virtual void get_aabb( Aabb<T>& aabb ) const = 0;
	};

}

#endif // math3d_primitive_hpp
