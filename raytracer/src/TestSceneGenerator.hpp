#pragma once
#include "SceneImporter.hpp"

namespace raytracer {
	
	class TestSceneGenerator : public SceneImporterInterface
	{
	public :
		void populateGeometricObjects( GeometricObjectArray& ) override;
		void getCamera( Camera& ) override;
	};

}
