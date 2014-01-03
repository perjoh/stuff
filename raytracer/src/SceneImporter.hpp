#pragma once
#include "GeometricObject.hpp"

namespace raytracer {

	class SceneImporterInterface
	{
	public :
		virtual ~SceneImporterInterface() { }

	public :
		virtual void populateGeometricObjects( GeometricObjectArray& ) = 0;
	};

    class SceneImporter : public SceneImporterInterface
    {
    public :
		SceneImporter( const char* resourceFilename );
        ~SceneImporter();

    public :
        void populateGeometricObjects( GeometricObjectArray& );

	private :
		struct Impl;
		Impl* impl_;
    };
}
