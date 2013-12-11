#pragma once

#include "vector.hpp"
#include "matrix.hpp"
#include "box.hpp"
#include "triangle.hpp"
#include "sphere.hpp"
#include <vector>

typedef math3d::vector<int, 2> vec2i;
typedef math3d::vector<int, 3> vec3i;
typedef math3d::vector<int, 4> vec4i;

typedef math3d::vector<float, 2> vec2f;
typedef math3d::vector<float, 3> vec3f;
typedef math3d::vector<float, 4> vec4f;

typedef math3d::vector<double, 2> vec2d;
typedef math3d::vector<double, 3> vec3d;
typedef math3d::vector<double, 4> vec4d;

typedef math3d::matrix<int, 3> mat33i;
typedef math3d::matrix<float, 3> mat33f;
typedef math3d::matrix<double, 3> mat33d;
typedef math3d::matrix<int, 4> mat44i;
typedef math3d::matrix<float, 4> mat44f;
typedef math3d::matrix<double, 4> mat44d;

typedef mat44f Matrix44f;

typedef math3d::Aabb<float> Aabbf;
typedef math3d::Aabb<double> Aabbd;

typedef math3d::Triangle<float> Trianglef;
typedef math3d::Triangle<double> Triangled;

typedef math3d::Sphere<float> Spheref;
typedef math3d::Sphere<double> Sphered;

typedef std::vector< vec3f > PointArray;
