#pragma once
#include <string>
#include "BasicTypes.hpp"
#include "Camera.hpp"
#include "RayTracable.hpp"
#include <vector>
#include <array>

namespace raytracer
{

	
	class RayTracableCollection
	{
	public : 
		void import(const std::string& resource);
		const RayTracable* intersectNearest(const Line&) const;

	private : 
	};

	class RayTracer
	{
	public :
		RayTracer( const RayTracableCollection& );

	public :
		Color trace(const Line& ray, int depth = 0) const;

	private :
	};

}
