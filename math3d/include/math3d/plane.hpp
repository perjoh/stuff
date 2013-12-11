#ifndef math3d_plane_hpp
#define math3d_plane_hpp

#include "vector.hpp"
#include <cassert>

namespace math3d
{

	template <typename T>
	class Plane {
	public :
		typedef T value_type;
		typedef vector<T, 3> vector_type;
		typedef vector<T, 3> Vector3;

	public :
        Plane()
            : normal_(0)
            , d_()
        { }

		Plane( const vector_type& normal, T d ) 
            : normal_( normal )
            , d_( d )
		{ }


		//! Construct Plane from three vertices(in clock-wise order).
		Plane( const vector_type& v1, const vector_type& v2, const vector_type& v3 ) 
        {
			assert( v1 != v2 );
			assert( v1 != v3 );

			normal_ = norm( cross( v2 - v1, v3 - v1 ) );
			d_ = dot( v1, normal_ );
		}

	public :
		//! Plane normal unit vector
		const vector_type& normal() const 
        {
			return normal_;
		}

		//! Shortest distance from origo to plane
		T distance() const 
        {
			return d_;
		}

	public :
		//! Point on plane that is nearest to point p.
		const vector_type neareastPoint( const vector_type& p ) const 
        {
			return p - (dot(p, normal()) - dot(normal(), distance()));
		}

		//! Shortest distance from plane to point p.
		const T distanceTo( const vector_type& p ) const 
        {
			return dot(p, normal()) - distance();
		}

		//! Check if point lies on the front side of the plane.
		bool frontSide( const vector_type& p ) const 
        {
			return dot( p, normal() ) > distance();
		}

	public :
		bool operator==( const Plane& p ) const 
        {
			return normal_ == p.normal_ && value_traits<value_type>::almost_equal( d_, p.d_ );
		}

        /*Plane& operator=( const Plane& p ) 
        {
            normal_ = p.normal_;
            d_ = p.d_;
            return *this;
        }*/

	private :
		vector_type	normal_;	// Plane normal
		T d_;			// distance from origin
	};
}

#endif // math3d_plane_hpp
