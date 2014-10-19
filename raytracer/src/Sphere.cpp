#include "Sphere.hpp"

namespace raytracer {

		/*IntersectResult Sphere::intersectNearest( const Ray& ) const 
		{
			return IntersectResult(); 
		}*/


		IntersectResult Sphere::intersectNearest( const Line& line ) const 
		{
			const Float t = sphere_.intersect(line);
			if ( t > 0 )
			{
				const Point3d point( line.direction()*t + line.origin() );
				const Point3d normal( (point - sphere_.center())/sphere_.radius() );

				return IntersectResult( 
					true, 
					Intersection( 
						point, 
						normal ) );
			}

			return IntersectResult(); 
		}


		BoundingBox Sphere::boundingBox() const 
		{
			return sphere_.getBoundingBox();
		}
}
