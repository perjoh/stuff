#pragma once
#include "BasicTypes.hpp"

namespace raytracer {

	struct IntersectResult
	{
		IntersectResult()
			: ok(false)
		{ }

		IntersectResult( bool ok_, const IntersectionPoint& intersectionPoint_ )
			: ok(ok_)
			, intersectionPoint(intersectionPoint_)
		{ }

		bool ok;
		IntersectionPoint intersectionPoint;
	};
}
