#pragma once
#include <string>
#include "GeometricTypes.hpp"

namespace raytracer
{
	class Camera;

	class GeometryDb
	{
	public :
	private :
	};

	class Scene
	{
	public :
		Scene();

	public :
		void import( const std::string& filename );
		void setCamera( const Camera& );

	public :
		QueryResult query( const Ray& ray ) const;
	};

	class Raytracer
	{
	public :
		Raytracer( const Scene& );

	public :
		void setScreenSize( const Point2d& );

	private :
	};

}
