#pragma once
#include "GeometricObject.hpp"
#include "Camera.hpp"

namespace raytracer {

	class SceneImporterInterface
	{
	public :
		virtual ~SceneImporterInterface() { }

	public :
		virtual void populateGeometricObjects( GeometricObjectArray& ) = 0;
		virtual void getCamera( Camera& ) = 0;
	};


    class SceneImporter : public SceneImporterInterface
    {
    public :
		SceneImporter( const char* resourceFilename );
        ~SceneImporter();

    public :
        void populateGeometricObjects( GeometricObjectArray& ) override;
		void getCamera( Camera& ) override;

	private :
		struct Impl;
		Impl* impl_;
    };
}
