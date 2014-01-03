#pragma once
#include <boost/ptr_container/ptr_vector.hpp>
#include "BasicTypes.hpp"
#include "IntersectResult.hpp"

namespace raytracer {

	class GeometricObject
	{
	public :
		virtual ~GeometricObject() {}

	public :
		virtual IntersectResult intersectNearest( const Ray& ) const = 0;
		virtual IntersectResult intersectNearest( const Line& ) const = 0;

		virtual BoundingBox boundingBox() const = 0;
	};

	typedef boost::ptr_vector<GeometricObject> GeometricObjectArray;
}
