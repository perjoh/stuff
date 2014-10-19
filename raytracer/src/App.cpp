#include "App.hpp"

namespace raytracer {

	using math3d::make_vec;

	App::App(
		const std::string& resource,
		const PixelPos& targetDim,
		const std::string& targetFileName)
		: targetDim_(targetDim)
		, camera_(make_vec(0, 0, 0), make_vec(0,0,1))
		, rayGenerator_(targetDim.first, targetDim.second, camera_)
	{
		//rayTracables_.import(resource);
		rayTracer_ = std::make_unique<RayTracer>(rayTracables_);
	}

    App::~App() 
	{
    }

    int App::run() 
	{
		typedef unsigned int uint;
		const uint BlockSize = 8;

		for (uint cellY = 0; cellY < targetDim_.second; cellY += BlockSize)
		{
			for (uint cellX = 0; cellX < targetDim_.first; cellX += BlockSize)
			{
				for (uint y = 0; y < BlockSize; ++y)
				{
					for (uint x = 0; x < BlockSize; ++x)
					{
						const std::pair<uint, uint> pixel(cellX + x, cellY + y);

						const std::vector<Line>& rays = rayGenerator_.generateRays(pixel.first, pixel.second);
						const Color output = rayTracer_->trace(rays);
						target_.setPixel(pixel.first, pixel.second, output);
					}
				}
			}
		}

        return 0;
    }

}
