#pragma once
#include <math3d/Sphere.hpp>
#include "BasicTypes.hpp"
#include "GeometricObject.hpp"

namespace raytracer {

	class Sphere : public GeometricObject
	{
	public :
		Sphere( const Point& center, Float radius )
			: sphere_( center, radius )
		{ }

		virtual IntersectResult intersectNearest( const Ray& ) const override;
		virtual IntersectResult intersectNearest( const Line& ) const override;

		virtual BoundingBox boundingBox() const override;

	private :
		typedef math3d::Sphere<Float> SphereType;
		SphereType sphere_;
	};
}
