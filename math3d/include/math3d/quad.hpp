#ifndef quad_hpp_included
#define quad_hpp_included

#include "triangle.hpp"

namespace math3d {

	template <typename T>
	class Quad {
	public :
		typedef T value_type;
		typedef vector<T, 3> vector_type;

	public :
		Quad( const vector_type& p1, const vector_type& p2, const vector_type& p3, const vector_type& p4 ) :
			tri_a_( p1, p2, p3 ),
			tri_b_( p3, p4, p1 )
		{ }

	private :
		Triangle<value_type> tri_a_;
		Triangle<value_type> tri_b_;
	};
}

#endif // quad_hpp_included
