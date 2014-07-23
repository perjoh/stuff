#pragma once
#include "BasicTypes.hpp"
#include "RayTracable.hpp"
#include <vector>

namespace raytracer {

	class TriangleMesh 
		: public RayTracable
	{
	public :
		TriangleMesh();

	public :
		void addTriangle( const Triangle& );

	private :
		void prepare() override;

		IntersectResult intersectNearest( const Ray& ) const override;
		IntersectResult intersectNearest( const Line& ) const override;

		template <typename RayType>
		IntersectResult intersectNearestImpl( const RayType& ray ) const
		{
			Float nearest = -1.0;
			size_t index = 0;

			// Do intersection test for all triangles
			for ( size_t i = 0; i < triangles_.size(); ++i )
			{
				const Triangle& triangle = triangles_[i];
				const Float t = triangle.intersect( ray );
				if ( nearest < -0.5 || t < nearest )
				{
					// Nearest intersection so far
					nearest = t;
					index = i;
				}
			}

			const bool intersectionFound = !(nearest < -0.5);
			if ( intersectionFound ) 
			{
				return IntersectResult( 
							true, 
							Intersection( 
								ray.sample( nearest ), 
								normals_[index] ) );
			}

			return IntersectResult();
		}

		BoundingBox boundingBox() const override;

	private :
		void calculateNormals();
		void setupSpacePartitioning();

	private :
		typedef std::vector<Triangle> Triangles;
		Triangles triangles_;

		typedef std::vector<Normal> Normals;
		Normals normals_;
	};
}