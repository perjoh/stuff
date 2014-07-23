#include "TriangleMesh.hpp"
#include <limits>

namespace raytracer {

	void TriangleMesh::addTriangle( 
		const Triangle& triangle )
	{
		triangles_.push_back( triangle );
	}

	void TriangleMesh::prepare() 
	{ 
		calculateNormals();
		setupSpacePartitioning();
	}

	IntersectResult TriangleMesh::intersectNearest( const Ray& ray ) const 
	{
		return intersectNearestImpl( ray );
	}

	IntersectResult TriangleMesh::intersectNearest( const Line& line ) const 
	{
		return intersectNearestImpl( line );
	}

	BoundingBox TriangleMesh::boundingBox() const 
	{
		BoundingBox box;

		if ( !triangles_.empty() )
			box = BoundingBox( 
					triangles_[0].min(), 
					triangles_[0].max() );

		for ( const Triangle& triangle : triangles_ )
		{
			box.grow( triangle.getBoundingBox() );
		}

		return box;
	}

	void TriangleMesh::setupSpacePartitioning()
	{
	}

	void TriangleMesh::calculateNormals()
	{
		normals_.reserve( triangles_.size() );
		for ( const Triangle& triangle : triangles_ )
			normals_.push_back( triangle.normal() );
	}

}