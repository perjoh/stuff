#pragma once

namespace math3d {

	template <typename T>
	struct rect {
		rect( T x0_, T y0_, T x1_, T y1_ ) :
			x0( x0_ ),
			y0( y0_ ),
			x1( x1_ ),
			y1( y1_ )
		{ }

		T width() const
		{
			return x1 - x0;
		}

		T height() const
		{
			return y1 - y0;
		}

		T x0;
		T y0;
		T x1;
		T y1;
	};

	typedef rect<float> rectf;
}
