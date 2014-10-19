#include "RayGenerator.hpp"

namespace raytracer {

	RayGenerator::RayGenerator( 
		const std::pair<size_t, size_t>& screenDim,
		const Camera& camera)
		: rays_(1) // Create one for now
		, screenDim_(screenDim)
		, camera_(camera)
	{
	}

	const std::vector<Line>& RayGenerator::generateRays( 
		const ScreenCoordinate& pixel ) const 
	{
		return rays_;
	}
}