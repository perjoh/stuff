#pragma once
#include "BasicTypes.hpp"
//#include "IntersectResult.hpp"

namespace raytracer {

	class RayTracer;

	class RayTracable
	{
	public :
		virtual ~RayTracable() { }

	public :
		virtual void prepare() = 0;

		virtual BoundingBox boundingBox() const = 0;

		//virtual IntersectResult intersectNearest( const Ray& ) const = 0;
		virtual Float intersectNearest( const Line& ) const = 0;

		virtual Color generateColor( 
			const RayTracer& rayTracer, 
			const Ray& ray, 
			Float intersection ) const = 0;
	};

}
