#pragma once
#include "BasicTypes.hpp"

namespace raytracer {

	class Camera
	{
	public :
		Camera( const Point3d& position, 
				const Point3d& lookAt,
				Float aspectRatio = 16.0/9,
				Float fov = 90 )
			: position_(position)
			, lookAt_(lookAt)
			, aspectRatio_(aspectRatio)
			, fov_(fov)
		{ }

		const Point3d& position() const {
			return position_;
		}

		const Point3d& lookAt() const {
			return lookAt_;
		}

		Float aspectRatio() const {
			return aspectRatio_;
		}

		Float fov() const {
			return fov_;
		}

	private :
		void setup();
	
	private :
		Point3d position_;
		Point3d lookAt_;

		Float aspectRatio_;
		Float fov_;

		Point3d topLeft_;
		Point3d topRight_;
		Point3d bottomLeft_;
		Point3d bottomRight_;
	};
}
