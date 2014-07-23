#pragma once
#include "BasicTypes.hpp"
#include "IntersectResult.hpp"

namespace raytracer {

	class RayTracable
	{
	public :
		virtual ~RayTracable() {}

	public :
		virtual void prepare() = 0;

		virtual IntersectResult intersectNearest( const Ray& ) const = 0;
		virtual IntersectResult intersectNearest( const Line& ) const = 0;

		virtual BoundingBox boundingBox() const = 0;
	};
}
