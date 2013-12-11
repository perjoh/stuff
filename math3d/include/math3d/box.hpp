#pragma once

#include "vector.hpp"
#include "AxisAlignedPlane.hpp"
#include "axis.hpp"
#include "intersections.hpp"

namespace math3d {

	//! Axis aligned bounding box
	template <typename T>
	class Aabb {
	public :
		typedef T value_type;
		typedef vector<T, 3> vector_type;

	public :
		Aabb()
		{ }

		Aabb( const vector_type& min, const vector_type& max ) :
			min_( min ),
			max_( max )
		{ }

	public :
		void set_corner_dim( const vector_type& c, const vector_type& d ) {
			min_ = c;
			max_ = c + d;
		}

	public :
		const vector_type& min() const {
			return min_;
		}

		const vector_type& max() const {
			return max_;
		}

		const vector_type& corner() const { // TODO This function does not make any sense.
			return min_;
		}

		const vector_type dim() const {
			return max_ - min_;
		}

		T volume() const {
			const vector_type d( dim() );
			return d[ 0 ] * d[ 1 ] * d[ 2 ];
		}

        vector_type center() const {
            return dim()*T(.5) + min_;
        }

	public :
		T width() const {
			return dim()[0];
		}

		T height() const {
			return dim()[1];
		}

		T depth() const {
			return dim()[2];
		}

    public :
        int widestAxis() const {
            int wa = 0;
            const vector_type v = dim();
            if ( v[wa] < v[1] )
                wa = 1;
            if ( v[wa] < v[2] )
                wa = 2;
            return wa;
        }

	public :
		vector_type closest_point( const vector_type& pt ) const {

			vector_type r;

			if (pt[0] < min_[0]) {
				r[0] = min_[0];
			} else if (pt[0] > max_[0]) {
				r[0] = max_[0];
			} else {
				r[0] = pt[0];
			}

			if (pt[1] < min_[1]) {
				r[1] = min_[1];
			} else if (pt[1] > max_[1]) {
				r[1] = max_[1];
			} else {
				r[1] = pt[1];
			}

			if (pt[2] < min_[2]) {
				r[2] = min_[2];
			} else if (pt[2] > max_[2]) {
				r[2] = max_[2];
			} else {
				r[2] = pt[2];
			}

			return r;
		}

	public :
		//! Test if given point lies inside the box.
		bool is_point_inside( const vector_type& pt ) const {

			return !(pt[0] < min_[0]) && !(max_[0] < pt[0]) &&
				!(pt[1] < min_[1]) && !(max_[1] < pt[1]) &&
				!(pt[2] < min_[2]) && !(max_[2] < pt[2]);
		}

		//! Test if rhs completely fits into box.
		bool contains( const Aabb& rhs ) const {
			return min_[0] <= rhs.min_[0] &&
				min_[1] <= rhs.min_[1] &&
				min_[2] <= rhs.min_[2] &&
				rhs.max_[0] <= max_[0] &&
				rhs.max_[1] <= max_[1] &&
				rhs.max_[2] <= max_[2];
		}

		//!
		template <typename SPHERE>
		bool containsSphere( const SPHERE& s ) const {

			const vector_type cmin( s.center() - s.radius() );
			const vector_type cmax( s.center() + s.radius() );

			return cmin[0] >= min()[0] &&
				cmin[1] >= min()[1] &&
				cmin[2] >= min()[2] &&
				cmax[0] <= max()[0] &&
				cmax[1] <= max()[1] &&
				cmax[2] <= max()[2];
		}

		//!
		template <typename SPHERE>
		bool intersectSphere( const SPHERE& s ) const {
			//return intersect_sphere_aabb_test( s, *this );
			return intersect::testSphereAabb( s, *this );
		}

		//!
		bool intersectAabb( const Aabb& box ) const {
			return intersect::testAabbAabb( *this, box );
		}

        template <typename TRIANGLE>
        bool intersectTriangle( const TRIANGLE& triangle ) const {
            return intersect::TestAabbTriangle::test( *this, triangle );
        }

	public :
		//! Split box along axis.
		//! @param axis Axis to split along.
		//! @param s Where on axis to split. (Globally, not relative to box)
		bool split( const AxisAlignedPlane<T>& split_plane, Aabb& left_box, Aabb& right_box ) const {

			/*const T s = split_plane.distance();
			const int axis = split_plane.axis();

			// Make sure split is inside box.
			if ( min_[ axis ] < s ) {
				if ( !( max_[ axis ] < s ) ) {

					vector_type left_max = max_;
					left_max[ axis ] = s;
					left_box = Aabb( min_, left_max );

					vector_type right_min( min_ );
					right_min[ axis ] = s;
					right_box = Aabb( right_min, max_ );

					return true;
				}
			}
			return false;*/
			left_box = *this;
			return left_box.split( split_plane, right_box );
		}

		//! Split box along axis.
		bool split( const AxisAlignedPlane<T>& splitPlane, Aabb& otherBox ) {
			const T s = splitPlane.distance();
			const int axis = splitPlane.axis();

			// Make sure split is inside box.
			if ( min_[ axis ] < s ) {
				if ( !( max_[ axis ] < s ) ) {

					vector_type left_max = max_;
					left_max[ axis ] = s;
					const vector_type max = max_;
					//left_box = Aabb( min_, left_max );
					max_ = left_max;

					vector_type right_min( min_ );
					right_min[ axis ] = s;
					otherBox = Aabb( right_min, max );

					return true;
				}
			}
			return false;
		}

		void moveRelative( const vector_type& delta ) {
			min_ += delta;
			max_ += delta;
		}

    public :
        T surfaceArea() const {
            return width()*( height() + depth() ) + height()*depth();
            //return width()*height() + width()*depth() + height()*depth();
        }

	private :
		vector_type min_;
		vector_type max_;
	};


	template <typename Aabb, typename It>
	const Aabb makeBoundingBox( It begin, It end ) {

		typename Aabb::vector_type min( make_vec( begin->min( 0 ), begin->min( 1 ), begin->min( 2 ) ) );
		typename Aabb::vector_type max( make_vec( begin->max( 0 ), begin->max( 1 ), begin->max( 2 ) ) );

		for ( It it = begin; it != end; ++it ) {
			for ( int axis = 0; axis < 3; ++axis ) {
				if ( min[ axis ] > it->min( axis ) )
					min[ axis ] = it->min( axis );

				if ( max[ axis ] < it->max( axis ) )
					max[ axis ] = it->max( axis );
			}
		}

		return Aabb( min, max );
	}

	template <typename Aabb_t, typename AabbIt>
	void subDivideOct( const Aabb_t& aabb, AabbIt first, AabbIt last ) {
		assert( std::distance( first, last ) == 8 );

		typedef AxisAlignedPlane<typename Aabb_t::value_type> Aap;
		typedef typename Aabb_t::vector_type vec;
		typedef typename Aabb_t::value_type T;

		const vec dimHalf( aabb.dim()/T(2) );
		Aabb_t box( aabb.min(), aabb.min() + dimHalf );

		*(first + 0) = box;
		//(first + 0)->moveRelative( T(), T(), T() ) );
		*(first + 1) = box;
		(first + 1)->moveRelative( vec::make( dimHalf[0], T(), T() ) );
		*(first + 2) = box;
		(first + 2)->moveRelative( vec::make( T(), T(), dimHalf[2] ) );
		*(first + 3) = box;
		(first + 3)->moveRelative( vec::make( dimHalf[0], T(), dimHalf[2] ) );

		*(first + 4) = box;
		(first + 4)->moveRelative( vec::make( T(), dimHalf[1], T() ) );
		*(first + 5) = box;
		(first + 5)->moveRelative( vec::make( dimHalf[0], dimHalf[1], T() ) );
		*(first + 6) = box;
		(first + 6)->moveRelative( vec::make( T(), dimHalf[1], dimHalf[2] ) );
		*(first + 7) = box;
		(first + 7)->moveRelative( vec::make( dimHalf[0], dimHalf[1], dimHalf[2] ) );
	}
}
