#pragma once
#include "BasicTypes.hpp"

namespace raytracer {

	class Raytracer
	{
	public :
		Pixel trace( unsigned int x, unsigned int y ) const;

	private :
		Pixel traceFraction( Float x, Float y ) const;
	};

}