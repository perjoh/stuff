#ifndef math3d_line_hpp
#define math3d_line_hpp

#include "ray.hpp"
#include <cassert>
#include <limits>

namespace math3d
{

	template <typename T>
	class Line
	{
	public :
		typedef T value_type;
		typedef Ray<T> ray_type;
		typedef typename ray_type::vector_type vector_type;

	public :
		Line(const vector_type& p1, const vector_type& p2) :
			ray_( p1, norm( p2 - p1 ) ),
			max_t_( vec_length( p2 - p1 ) )
		{ }

		Line( const Ray<T>& ray ) :
			ray_( ray ),
			max_t_( std::numeric_limits<T>::max() )
		{ }

		Line( const Ray<T>& ray, const value_type& t ) : // TODO Rename t to max_t
			ray_( ray ),
			max_t_( t )
		{ }

        Line( const Line& line, const value_type& t0, const value_type& t1 )
        : ray_( line.ray_.origin() + line.ray_.direction()*t0, line.ray_.direction() )
        , max_t_(t1 - t0)
        { }

	public :
		const vector_type& point_a() const {

			return ray_.origin();
		}

		const vector_type point_b() const {

			return ray_.sample( max_t_ );
		}

		vector_type origin() const {
			return ray_.origin();
		}

		vector_type dir() const { // TODO rename to direction
			return ray_.direction();
		}

		value_type length() const {
			return max_t_;
		}

		vector_type sample( value_type t ) const {
			return point_a() + dir() * t;
		}


	public :
		const Ray<value_type>& to_ray() const {
			return ray_;
		}

	public :
        template <typename PlaneT>
		bool split( const PlaneT& plane, value_type& t ) const {
			if ( ray_.split( plane, t ) ) {
				return t < length();
			}
			return false;
		}


	private :
		Ray<T>	ray_;
		T max_t_;
	};


	template <typename T>
	Line<T> crop_ray( const Ray<T>& ray, const T& t0, const T& t1 ) {

		assert( t0 < t1 );

		const Ray<T> tmp_ray( ray.sample( t0 ), ray.direction() );
		return Line<T>( tmp_ray, t1 - t0 );
	}
}

#endif //math3d_line_hpp
