#pragma once
#include <math3d/Sphere.hpp>
#include "BasicTypes.hpp"
#include "RayTracable.hpp"

namespace raytracer {

	class Sphere : public RayTracable
	{
	public :
		Sphere( const Point3d& center, Float radius )
			: sphere_( center, radius )
		{ }

		void prepare() override 
		{ }

		IntersectResult intersectNearest( const Ray& ) const override;
		IntersectResult intersectNearest( const Line& ) const override;

		BoundingBox boundingBox() const override;

	private :
		typedef math3d::Sphere<Float> SphereType;
		SphereType sphere_;
	};
}
