#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include "SceneImporter.hpp"
#include "Mesh.hpp"

namespace raytracer {

	struct SceneImporter::Impl
	{
		~Impl()
		{
			delete scene_;
		}

		const aiScene* scene_;
	};


	SceneImporter::SceneImporter( const char* resourceFilename )
		: impl_(new Impl())
	{
		Assimp::Importer imp;
		if ( imp.ReadFile( resourceFilename, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate ) )
		{
			impl_->scene_ = imp.GetOrphanedScene();
		}
	}


	SceneImporter::~SceneImporter()
	{
		delete impl_;
	}


	void copyVertices( TriangleMesh& dest, const aiMesh& src )
	{
		const size_t NumVertices = src.mNumVertices;
		TriangleMesh::VertexArray vertexArray(NumVertices);

		for ( size_t iVertex = 0; iVertex < NumVertices; ++iVertex )
		{
			vertexArray[iVertex].position = 
				Point::make(
					src.mVertices[iVertex].x,
					src.mVertices[iVertex].y,
					src.mVertices[iVertex].z );
		}

		dest.setVertices( vertexArray );
	}


	void copyTriangles( TriangleMesh& dest, const aiMesh& src )
	{
		const size_t NumFaces = src.mNumFaces;
		TriangleMesh::TriangleArray triangleArray(NumFaces);
		for ( size_t iFace = 0; iFace < NumFaces; ++iFace )
		{
			assert( src.mFaces[iFace].mNumIndices == 3 );

			triangleArray[iFace] = 
				vec3i::make(
					src.mFaces[iFace].mIndices[0],
					src.mFaces[iFace].mIndices[1],
					src.mFaces[iFace].mIndices[2] );
		}

		dest.setTriangles( triangleArray );
	}


	void SceneImporter::populateGeometricObjects( GeometricObjectArray& geometricObjectArray )
	{
		if ( impl_->scene_ )
		{
			const size_t NumMeshes = impl_->scene_->mNumMeshes;
			geometricObjectArray.reserve( NumMeshes );

			for ( size_t iMesh = 0; iMesh < NumMeshes; ++iMesh )
			{
				const aiMesh* mesh = impl_->scene_->mMeshes[iMesh];

				Mesh* newMesh = new Mesh();
				geometricObjectArray.push_back( newMesh );

				copyVertices( newMesh->triangleMesh, *mesh );
				copyTriangles( newMesh->triangleMesh, *mesh );
			}
		}
	}
}