#ifndef math3d_helpers_hpp
#define math3d_helpers_hpp

#include "vector.hpp"

namespace math3d
{

	//!
	template <typename T>
	const T square( const T& t )
	{
		return t * t;
	}

	//!
	template <typename T>
	const vector<T, 3> decay_vec( const vector<T, 4>& v )
	{
		return make_vec( v[0], v[1], v[2] );
	}

}

#endif // math3d_helpers_hpp
