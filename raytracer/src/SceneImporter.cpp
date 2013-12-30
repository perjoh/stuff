#include "SceneImporter.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

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

	void SceneImporter::populateMeshes( MeshArray& meshArray )
	{
		if ( impl_->scene_ )
		{
			const size_t NumMeshes = impl_->scene_->mNumMeshes;
			meshArray.resize( NumMeshes );

			for ( size_t iMesh = 0; iMesh < NumMeshes; ++iMesh )
			{
				const aiMesh* mesh = impl_->scene_->mMeshes[iMesh];

				{
					const size_t NumVertices = mesh->mNumVertices;
					Mesh::VertexArray vertexArray(NumVertices);

					for ( size_t iVertex = 0; iVertex < NumVertices; ++iVertex )
					{
						vertexArray[iVertex].position = 
							vec3f::make(
								mesh->mVertices[iVertex].x,
								mesh->mVertices[iVertex].y,
								mesh->mVertices[iVertex].z );
					}

					meshArray[iMesh].setVertices(vertexArray);
				}

				{
					const size_t NumFaces = mesh->mNumFaces;
					Mesh::TriangleArray triangleArray(NumFaces);
					for ( size_t iFace = 0; iFace < NumFaces; ++iFace )
					{
						assert( mesh->mFaces[iFace].mNumIndices == 3 );

						triangleArray[iFace] = 
							vec3i::make(
								mesh->mFaces[iFace].mIndices[0],
								mesh->mFaces[iFace].mIndices[1],
								mesh->mFaces[iFace].mIndices[2] );
					}

					meshArray[iMesh].setTriangles(triangleArray);
				}
			}
		}
	}
}