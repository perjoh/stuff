#pragma once

#include <math3d/box.hpp>
#include <math3d/AxisAlignedPlane.hpp>
#include <math3d/ray.hpp>
#include <math3d/line.hpp>
#include <math3d/triangle.hpp>

namespace raytracer {

    typedef double Float;
    typedef math3d::AxisAlignedPlane<Float> AxisAlignedPlane;
    typedef math3d::Plane<Float> Plane;
    typedef math3d::Aabb<Float> BoundingBox;
    typedef math3d::Ray<Float> Ray;
    typedef math3d::Line<Float> Line;
    typedef math3d::Triangle<Float> Triangle;
    typedef math3d::vector<Float, 3> Point;
	typedef math3d::vector<Float, 3> Normal;

	typedef math3d::vector<float, 3> Pixel;
}
