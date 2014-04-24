#include "TestSceneGenerator.hpp"
#include "Sphere.hpp"

namespace raytracer {

	void TestSceneGenerator::populateGeometricObjects( GeometricObjectArray& geometricObjectArray )
	{
		geometricObjectArray.push_back( 
			new Sphere( 
				Point::make(0, 0, 0), 
				5 ) );
	}


	void TestSceneGenerator::getCamera( Camera& camera )
	{
		camera = 
			Camera( 
				Point::make(0, 0, -25), 
				Point::make(0, 0, 0) );
	}
}
