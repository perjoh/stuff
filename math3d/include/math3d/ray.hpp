#pragma once

#include "vector.hpp"
#include "AxisAlignedPlane.hpp"
#include "plane.hpp"
#include <cassert>
#include <limits>

namespace math3d
{
	template < typename T >
	class Ray
	{
	public :
		typedef T value_type;
        typedef T Float;
		typedef vector< T, 3 > vector_type;

	public :

		Ray()
		{ }

		Ray( const vector_type& origin, const vector_type& direction ) :
			origin_( origin ),
			direction_( direction )
		{
			//assert( dot_square( direction_ ) == T(1) );
		}


	public :

		const vector_type& origin() const
		{
			return origin_;
		}

		const vector_type& direction() const
		{
			return direction_;
		}


	public :

		vector_type sample( value_type t ) const
		{
			return origin() + direction() * t;
		}

	public :
		bool split( const AxisAlignedPlane<value_type>& aa_plane, value_type& t ) const {

			using namespace std;

			const int axis = aa_plane.axis();

			// check if ray is parallel to plane
			if ( !( abs( direction_[ axis ] ) < numeric_limits<value_type>::epsilon() ) ) {
				t = ( aa_plane.distance() - origin_[ axis ] ) / direction_[ axis ];
				return !( t < 0 );
			}
			return false;
		}


        bool split( const Plane<Float>& plane, Float& t ) const {

            // t = (d - dot(n, origin))/(dot(dir, n))
            const Float div = dot(direction(), plane.normal());
            if (fabs(div) > 0) {
                const Float tTmp = ( plane.distance() - dot(plane.normal(), origin()) )/div;
                if (tTmp > 0) {
                    t = tTmp;
                    return true;
                }
            }

            return false;
        }

	private :

		vector_type	origin_;
		vector_type	direction_;
	};
}

