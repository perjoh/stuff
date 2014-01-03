#pragma once
#include "SceneImporter.hpp"

namespace raytracer {
	
	class TestSceneGenerator : public SceneImporterInterface
	{
	public :
		void populateMeshes( MeshArray& ) override;
	};

}
