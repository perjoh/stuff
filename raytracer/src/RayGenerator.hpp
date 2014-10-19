#pragma once
#include "Camera.hpp"
#include <vector>

namespace raytracer {

	class RayGenerator
	{
	public :
		RayGenerator(
			const ScreenCoordinate& screenSize,
			const Camera& camera);

		const std::vector<Line>& generateRays( const ScreenCoordinate& ) const;

	private :
		std::vector<Line> rays_;
		ScreenCoordinate screenDim_;
		Camera camera_;
	};

}