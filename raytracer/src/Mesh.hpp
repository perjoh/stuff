#pragma once
#include "TriangleMesh.hpp"
#include <vector>

namespace raytracer {

	struct Vertex
	{
		Vertex()
			: position( vec3f::make( .0f, .0f, .0f ) )
		{ }

		Vertex( float x, float y, float z )
			: position( vec3f::make( x, y, z ) )
		{ }

		vec3f position;
	};

	typedef mesh::TriangleMesh<Vertex> Mesh;
	typedef std::vector<Mesh> MeshArray;
}
