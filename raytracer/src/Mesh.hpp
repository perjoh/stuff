#pragma once
#include <vector>
#include "TriangleMesh.hpp"
#include "GeometricObject.hpp"

namespace raytracer {

	struct Vertex
	{
		Vertex()
		{ }

		Vertex( Float x, Float y, Float z )
			: position( Point::make( x, y, z ) )
		{ }

		Point position;

		typedef Float FloatType;
	};

	typedef mesh::TriangleMesh<Vertex> TriangleMesh;

	class Mesh : public GeometricObject
	{
	public :
		virtual IntersectResult intersectNearest( const Ray& ) const override;
		virtual IntersectResult intersectNearest( const Line& ) const override;

		virtual BoundingBox boundingBox() const override;

		void setupSpacePartitioning();

	public :
		TriangleMesh triangleMesh;
	};

}
