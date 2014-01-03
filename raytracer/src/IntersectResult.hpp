#pragma once
#include "BasicTypes.hpp"

namespace raytracer {

	struct IntersectResult
	{
		IntersectResult()
			: ok(false)
		{ }

		IntersectResult( bool ok_, const Normal& normal_ )
			: ok(ok_)
			, normal(normal_)
		{ }

		bool ok;
		Normal normal;
	};
}
