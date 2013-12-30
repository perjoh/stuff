#pragma once
#include "Mesh.hpp"

namespace raytracer {

    class SceneImporter 
    {
    public :
		SceneImporter( const char* resourceFilename );
        ~SceneImporter();

    public :
        void populateMeshes( MeshArray& );

	private :
		struct Impl;
		Impl* impl_;
    };
}
