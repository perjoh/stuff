#include "RayGenerator.hpp"

namespace raytracer {

	RayGenerator::RayGenerator( 
		const ScreenDim& screenDim,
		const Camera& camera)
		: rays_(1) // Create one for now
		, screenDim_(screenDim)
		, camera_(camera)
	{
	}

	const std::vector<Line>& RayGenerator::generateRays( 
		const ScreenDim& pixel ) const 
	{
		return rays_;
	}
}