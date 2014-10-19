#include "Camera.hpp"

namespace raytracer {
	
	void Camera::setup()
	{
			const  Point3d cameraVector = lookAt() - position();

			// Calculate length of vector perpendicular to camera vector.
			const Float d = cameraVector.length();
			const Float f = fov()*.5;
			const Float lenHorizontal = std::sin(f)*(d / std::cos(f)); 
			const Float lenVertical = lenHorizontal / aspectRatio();

			const Point3d tmpDown(math3d::make_vec(0, -1, 0));
			const Point3d perpendicularLeft = norm(cross(cameraVector, tmpDown)) * (lenHorizontal * 0.5);
			const Point3d perpendicularDown = norm(cross(perpendicularLeft, cameraVector))*(lenVertical*0.5);

			topLeft_ = lookAt() + perpendicularLeft - perpendicularDown - position();
			topRight_ = lookAt() - perpendicularLeft - perpendicularDown - position();
			bottomLeft_ = lookAt() + perpendicularLeft + perpendicularDown - position();
			bottomRight_ = lookAt() - perpendicularLeft + perpendicularDown - position();
	}

}