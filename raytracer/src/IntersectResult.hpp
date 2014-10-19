#pragma once
#include "BasicTypes.hpp"

namespace raytracer {

	class RayTracable;

	class IntersectResult
	{
	public:
		IntersectResult()
			: intersected_(nullptr)
		{ }

		IntersectResult(
			RayTracable* intersected, 
			const Intersection& i )
			: intersected_(intersected)
			, intersection_( i )
		{ }

		explicit operator bool() const {
			return intersected_ != nullptr;
		}

		const Intersection& intersection() const {
			return intersection_;
		}

	private :
		RayTracable* intersected_;
		Intersection intersection_;
	};

	ColorResult Shader(Line& line, int depth)
	{
		if (intersection)
		{
			ColorResult result;
			if (depth < tracer.GetMaxDepth())
			{
				return result + tracer.trace(reflectedRay)*0.2;
			}
		}

		return ColorResult(false);
	}

}
