#include "Sphere.hpp"

namespace raytracer {

		IntersectResult Sphere::intersectNearest( const Ray& ) const 
		{
			return IntersectResult(); 
		}


		IntersectResult Sphere::intersectNearest( const Line& line ) const 
		{
			const Float t = sphere_.intersect(line);
			if ( t > 0 )
			{
				const Point point( line.direction()*t + line.origin() );
				const Point normal( (point - sphere_.center())/sphere_.radius() );
				return IntersectResult( true, IntersectionPoint( point, normal ) );
			}

			return IntersectResult(); 
		}


		BoundingBox Sphere::boundingBox() const 
		{
			return sphere_.getBoundingBox();
		}
}
