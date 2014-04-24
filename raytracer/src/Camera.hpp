#pragma once
#include "BasicTypes.hpp"

namespace raytracer {

	class Camera
	{
	public :
		Camera( 
			const Point& position, 
			const Point& lookAt,
			Float aspectRatio = 16.0/9 )
			: position_(position)
			, lookAt_(lookAt)
			, aspectRatio_(aspectRatio)
		{ }

		const Point& position() const 
		{
			return position_;
		}

		const Point& lookAt() const 
		{
			return lookAt_;
		}

		Float aspectRatio() const
		{
			return aspectRatio_;
		}
	
	private :
		Point position_;
		Point lookAt_;

		Float aspectRatio_;
	};
}
