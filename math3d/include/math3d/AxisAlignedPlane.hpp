#pragma once

#include "axis.hpp"
#include "plane.hpp"

namespace math3d {

	template <typename T>
	class AxisAlignedPlane 
    {
	public :
		typedef T value_type;
		typedef vector<T, 3> vector_type;

	public :
        AxisAlignedPlane()
            : axisFacing( X, true )
            , d_()
        { }

		AxisAlignedPlane( Axis axis, T d, bool facing = true )
            : axisFacing( axis, facing )
            , d_( d )
		{ }

        template <typename ScalarType>
        AxisAlignedPlane( const Plane<ScalarType>& plane )
            : axisFacing( X, true )
            , d_( plane.distance() )
        {
            const value_type x = abs(plane.normal()[0]);
            const value_type y = abs(plane.normal()[1]);
            const value_type z = abs(plane.normal()[2]);

            if ( x < y )
                axisFacing.axis = ( y < z ) ? Z : Y;
            else
                axisFacing.axis = ( x < z ) ? Z : X;
        }

    public :
        void flip()
        {
            axisFacing.facing = !axisFacing.facing;
        }

	public :
		Axis axis() const
        {
			return static_cast<Axis>(axisFacing.axis);
		}

		T distance() const
        {
			return d_;
		}

        bool facing() const
        {
            return axisFacing.facing;
        }

	public :
		bool isOnPositiveSide( const vector_type& pt ) const
        {
			if (pt[ axis() ] < distance())
                return !facing();
            return facing();
		}

    public :
        template <typename Triangle>
        bool testTriangle( const Triangle& triangle ) const
        {
            return intersect::testTriangleAxisAlignedPlane( triangle, *this );
        }

        const Plane<value_type> toPlane() const {
            static const vector_type AxisVectors[3] = { make_vec(1, 0, 0),
                                                        make_vec(0, 1, 0),
                                                        make_vec(0, 0, 1) };

            const value_type sign = axisFacing.facing ? 1 : -1;
            return Plane<value_type>( AxisVectors[axisFacing.axis]*sign, d_ );
        }

	private :
		struct Axis_
        {
            Axis_(unsigned int a, bool f)
            : axis(a), facing(f) { }
            unsigned int axis : 4;
            bool facing : 1;
        } axisFacing;
		T d_;
	};

}

