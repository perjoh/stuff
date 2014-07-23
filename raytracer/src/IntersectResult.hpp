#pragma once
#include "BasicTypes.hpp"

namespace raytracer {

	struct IntersectResult
	{
		IntersectResult()
			: ok(false)
		{ }

		IntersectResult(
			bool ok_, 
			const Intersection& i )
			: ok(ok_)
			, intersection( i )
		{ }

		bool ok;
		Intersection intersection;
	};
}
