#ifndef math3d_triangle_hpp
#define math3d_triangle_hpp

#include <algorithm>
#include "plane.hpp"
#include "ray.hpp"
#include "line.hpp"
#include "box.hpp"

namespace math3d {

	template <typename TriangleImpl>
	class TriangleInterface {

    public :
		typedef typename TriangleImpl::value_type value_type;
        typedef typename TriangleImpl::vector_type vector_type;

	public :
        TriangleInterface()
        { }

		TriangleInterface( const vector_type& pointA, const vector_type& pointB, const vector_type& pointC ) 
        : impl_( pointA, pointB, pointC )
	   	{ }

    protected :
        ~TriangleInterface() { }

	public :
		const vector_type& pointA() const {
			return impl_.pointA();
		}

		const vector_type& pointB() const {
			return impl_.pointB();
		}

		const vector_type& pointC() const {
			return impl_.pointC();
		}

	public :
		vector_type normal() const {
			return to_plane().normal();
		}

	public :
		value_type min( unsigned int axis ) const {
			return std::min<value_type>( std::min<value_type>( pointA()[ axis ], pointB()[ axis ] ), pointC()[ axis ] );
		}

		value_type max( unsigned int axis ) const {
			return std::max<value_type>( std::max<value_type>( pointA()[ axis ], pointB()[ axis ] ), pointC()[ axis ] );
		}

		const vector_type min() const {
			return vector_type::make( min(0), min(1), min(2) );
		}

		const vector_type max() const {
			return vector_type::make( max(0), max(1), max(2) );
		}

	public :
		Plane<value_type> to_plane() const {
			return Plane<value_type>( pointA(), pointB(), pointC() );
		}

		const Aabb<value_type> getBoundingBox() const {
			return Aabb<value_type>( min(), max() );
		}

	public :
		bool testIntersect( const Ray<value_type>& ray ) const
		{
			return intersect::testRayTriangle( ray, *this );
		}

		value_type intersect( const Ray<value_type>& ray ) const
		{
			// TODO Fix this when intersect functions return a value_type value instead of a boolean.
            vector_type uvw;
			value_type t;
			if (!intersect::rayTriangle(ray, *this, uvw, t))
				t = value_type(-1);
			return t;
		}

		bool testIntersect( const Line<value_type>& line ) const
		{
			return intersect::testLineTriangle( line, *this );
		}

		value_type intersect( const Line<value_type>& line ) const
		{
			// TODO Fix this when intersect functions return a value_type value instead of a boolean.
            vector_type uvw;
			value_type t;
			if (!intersect::lineTriangle(line, *this, uvw, t))
				t = value_type(-1);
			return t;
		}


		bool testIntersect( const Aabb<value_type>& aabb ) const 
        {
            return intersect::TestAabbTriangle<Aabb<value_type>, TriangleInterface>::test( aabb, *this );
		}

	private :
        TriangleImpl impl_;
	};

    template <typename Float>
    struct TriangleInternals {

        typedef Float value_type;
        typedef vector<Float, 3> vector_type;

        TriangleInternals()
        { }
        
        TriangleInternals( const vector_type& pointA, const vector_type& pointB, const vector_type& pointC )
            : pointA_( pointA )
            , pointB_( pointB )
            , pointC_( pointC )
        { }

        vector_type& pointA() {
            return pointA_;
        }
        vector_type& pointB() {
            return pointB_;
        }
        vector_type& pointC() {
            return pointC_;
        }

        const vector_type& pointA() const {
            return pointA_;
        }
        const vector_type& pointB() const {
            return pointB_;
        }
        const vector_type& pointC() const {
            return pointC_;
        }

    private :
        vector_type pointA_;
        vector_type pointB_;
        vector_type pointC_;
    };

    template <typename Float>
    struct Triangle : public TriangleInterface<TriangleInternals<Float> > {

        Triangle( const vector_type& pointA, const vector_type& pointB, const vector_type& pointC )
            : TriangleInterface( pointA, pointB, pointC )
        { }
    };
}

#endif // math3d_triangle_hpp
