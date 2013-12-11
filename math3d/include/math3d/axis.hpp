#pragma once

#include <cassert>

namespace math3d {

	enum Axis { X, Y, Z };

	// prefix
	inline Axis operator++(Axis& a)
    {
        switch ( a )
        {
			case X: return Y;
			case Y: return Z;
			case Z: return X;
		};
		assert( false );
		return X;
	}

	// postfix
	inline Axis operator++( Axis& a, int )
    {
		Axis tmp( a );
		++a;
		return tmp;
	}
}

