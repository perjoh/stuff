#pragma once
#include "Camera.hpp"
#include <vector>

namespace raytracer {

	typedef Point2d<unsigned int> ScreenDim;

	class RayGenerator
	{
	public :
		RayGenerator(
			const ScreenDim& screenDim,
			const Camera& camera);

		const std::vector<Line>& generateRays( const ScreenDim& ) const;

	private :
		std::vector<Line> rays_;
		ScreenDim screenDim_;
		Camera camera_;
	};

}