#ifndef math3d_intersections_hpp
#define math3d_intersections_hpp

#include "helpers.hpp"
#include <limits>

namespace math3d {
namespace intersect {

	//!
	template <typename T>
	struct Intersection
	{
		typedef vector<T, 3> vector_type;

		Intersection() 
			: point_( 0 )
			, normal_( 0 )
		{ }

		Intersection( 
			const vector_type& point, 
			const vector_type& normal ) 
			: point_( point )
			, normal_( normal )
		{ }

	public :
		const vector_type& point() const
		{
			return point_;
		}

		const vector_type& normal() const
		{
			return normal_;
		}

	private :
		vector_type point_;
		vector_type normal_;
	};


	//! Calculate ray plane intersection point.
	template < typename RAY, typename PLANE, typename T>
	bool intersect_ray_plane_nearest( const RAY& r, const PLANE& p, T& t ) { // TODO Remove 'nearest' suffix.

		t = ( p.distance() - dot( r.origin(), p.normal() ) ) / dot( r.direction(), p.normal() );
		return !( t < 0 );
	}


	//! Ray plane intersection test.
	template <typename RAY, typename PLANE>
	bool intersect_ray_plane_test( const RAY& r, const PLANE& p ) {

		typename RAY::value_type t;
		return intersect_ray_plane_nearest( r, p, t );
	}


	//! Calculate line plane intersection point.
	template <typename LINE, typename PLANE, typename T>
	bool intersect_line_plane_nearest( const LINE& l, const PLANE& p, T& t ) {

		if ( intersect_ray_plane_nearest( l.to_ray(), p, t) ) {
			return t <= l.length();
		}
		return false;
	}


	//! Line plane intersection.
	template <typename LINE, typename PLANE>
	bool intersect_line_plane_test( const LINE& l, const PLANE& p ) {

		typename LINE::value_type t;
		return intersect_line_plane_nearest( l, p, t);
	}


	//! Calculate the ray sphere intersection point.
	template <typename RAY, typename SPHERE, typename T>
	bool intersect_ray_sphere_nearest( const RAY& r, const SPHERE& s, T& t ) {

		typedef typename RAY::vector_type vec;
		typedef typename vec::value_type val;

		const vec m = r.origin() - s.center();
		const val b = dot( m, r.direction() );
		const val c = dot( m, m ) - s.radius() * s.radius();

		// check if ray origin is outside sphere and it points away from the sphere center
		if ( c > 0 && b > 0 ) {
			return false;
		}

		const val discr = b * b - c;

		// check if any roots exists, if none there is no intersection
		if ( discr < 0 ) {
			return false;
		}

		t = -b; // - sqrt( discr );

		// if ray origin is outside sphere, pick the negative root, if inside pick positive
		if ( c > 0 ) {
			t -= sqrt( discr );
		} else {
			t += sqrt( discr );
		}

		return true;
	}


	//! Ray sphere intersection test.
	template <typename RAY, typename SPHERE>
	bool intersect_ray_sphere_test( const RAY& r, const SPHERE& s ) {

		typedef typename RAY::vector_type vec;
		typedef typename vec::value_type val;

		const vec m = r.origin() - s.center();
		const val c = dot( m, m ) - s.radius() * s.radius();

		// check if ray origin is inside sphere, if so there is an intersection
		if ( c < 0 ) {
			return true;
		}

		const val b = dot( m, r.direction() );

		// check if ray origin is outside sphere and it points away from the sphere center
		if ( c > 0 && b > 0 ) {
			return false;
		}

		const val discr = b * b - c;

		// check if any roots exists, if none there is no intersection
		if ( discr < 0 ) {
			return false;
		}

		return true;
	}


	//! Calculate the line sphere intersection point.
	template <typename LINE, typename SPHERE, typename T>
	bool intersect_line_sphere_nearest( const LINE& l, const SPHERE& p, T& t ) {

		if ( intersect_ray_sphere_nearest( l.to_ray(), p, t ) ) {
			return t < l.length();
		}
		return false;
	}


	//! Line sphere intersection test.
	template <typename LINE, typename SPHERE>
	bool intersect_line_sphere_test( const LINE& l, const SPHERE& s ) {

		typename LINE::value_type t;
		return intersect_line_sphere_nearest( l, s, t );
	}


	//! Sphere aabb intersection test.
	template <typename SPHERE, typename AABB>
	bool testSphereAabb( const SPHERE& s, const AABB& aabb ) {

		const typename SPHERE::vector_type cp( aabb.closest_point( s.center() ) );
		return dot_square( cp - s.center() ) < square( s.radius() );
	}


	//! Ray / axis aligned bounding box intersection test.
	//! @param ray Ray to intersect.
	//! @param aabb Box to intersect.
	//! @param t0 Point closest to ray origin that intersects the box, or if the ray origin is inside the box this value is zero.
	//! @param t1 Point furthest away from ray origin that intersects the box.
	//! @return True if intersection occurs, false if not.
	template <typename RAY, typename AABB, typename T>
	bool intersect_ray_aabb( const RAY& ray, const AABB& aabb, T& t0, T& t1 ) {

		// Based on code from the book 'Realtime collision detection'.

		using namespace std;

		T tmin( 0 );
		T tmax( numeric_limits<T>::max() );

		for ( int i = 0; i < 3; ++i ) {

			// Check if ray is parallel to planes.
			if ( abs( ray.direction()[ i ] ) < numeric_limits<T>::epsilon() ) {

				// Check if ray origin is outside box, if so no intersection occurs.
				if ( ray.origin()[i] < aabb.min()[i] || aabb.max()[i] < ray.origin()[i] ) {
					return false;
				}

			} else {

				t0 = ( aabb.min()[i] - ray.origin()[i] ) / ray.direction()[i];
				t1 = ( aabb.max()[i] - ray.origin()[i] ) / ray.direction()[i];

				if ( t1 < t0 ) {
					swap( t0, t1 );
				}

				if ( tmin < t0 ) {
					tmin = t0;
				}

				if ( t1 < tmax ) {
					tmax = t1;
				}

				// If tmax 'passes' tmin, no intersection exists.
				if ( tmax < tmin ) {
					return false;
				}
			}
		}

		if ( t0 < 0 ) {
			t0 = 0;
		}

		return true;
	}


	//!
	template <typename LINE, typename AABB, typename T>
	bool intersect_line_aabb( const LINE& line, const AABB& aabb, T& t0, T& t1 ) {
		if ( intersect_ray_aabb( line.to_ray(), aabb, t0, t1 ) ) {
			if ( line.length() >= t0 ) {
				if ( line.length() < t1 ) {
					t1 = line.length();
				}
				return true;
			}
		}
		return false;
	}

    template <typename Ray, typename Triangle, typename T>
    bool intersect_ray_triangle(const Ray& ray, const Triangle& triangle, typename Ray::vector_type& uvw, T& t) {
        // Shamelessly stolen from the book 'Real-time collision detection'.
        typedef typename Ray::vector_type vec;

        const vec ab = triangle.pointB() - triangle.pointA();
        const vec ac = triangle.pointC() - triangle.pointA();
        const vec qp = -ray.direction();

        // Optimization: Using static geometry, this can be pre-calculated for each triangle.
        const vec n = cross(ab, ac);

        const T d = dot(qp, n);
        const vec ap = ray.origin() - triangle.pointA();
        t = dot(ap, n);
        if (t < 0)
            return false;
        // Add this check for lines.
        //if (t > d)
        //return false;

        enum { u, v, w };

        const vec e = cross(qp, ap);
        uvw[v] = dot(ac, e);
        if (uvw[v] < 0 || uvw[v] > d)
            return false;

        uvw[w] = -dot(ab, e);
        if (uvw[w] < 0 || uvw[v] + uvw[w] > d)
            return false;

        // Optimization: This can be removed for tests.
        const T ood = 1/d;
        t *= ood;
        uvw[v] *= ood;
        uvw[w] *= ood;
        uvw[u] = 1 - uvw[v] - uvw[w];

        return true;
    }


	// Triangle intersection tests
    // TODO Need to fix names of these functions so they follow the same pattern.

	//!
	template <typename Ray, typename Triangle, typename Vector, typename T>
	inline bool rayTriangle( const Ray& ray, const Triangle& triangle, Vector& uvw, T& t ) {
		return intersect_ray_triangle(ray, triangle, uvw, t);
	}

	//!
	template <typename Ray, typename Triangle>
	inline bool testRayTriangle( const Ray& ray, const Triangle& triangle ) {
        typename Ray::vector_type uvw;
        typedef typename Ray::vector_type::value_type T;
		T t;
		return intersect_ray_triangle(ray, triangle, uvw, t);
	}

	//!
	template <typename Line, typename Triangle, typename Vector, typename T>
	inline bool lineTriangle( const Line& line, const Triangle& triangle, Vector& uvw, T& t ) {
		if ( rayTriangle( line.to_ray(), triangle, uvw, t ) ) {
			return t <= line.length();
		}
		return false;
	}

	//!
	template <typename LINE, typename TRI>
	inline bool testLineTriangle( const LINE& line, const TRI& triangle ) {
        typename TRI::vector_type uvw;
        typename TRI::value_type t;
		return lineTriangle( line, triangle, uvw, t );
	}

	template <typename VEC, typename PLANE, typename T>
	inline const std::pair<bool, T> sweepIntersectSpherePlane( const VEC& c0, const VEC& c1, T radius, const PLANE& plane )
	{
		T a = plane.distanceTo(c0);
		T b = plane.distanceTo(c1);

		T d = b - a;
		if ( d != T() )
		{
			T t = (radius - a)/d;
			if ( t > T() && t <= T(1) )
			{
				return std::pair<bool, T>( true, t );
			}

			return std::pair<bool, T>( false, t );
		}

		return std::pair<bool, T>( false, T() );
	}

	template <typename AABB>
	inline bool testAabbAabb( const AABB& lhs, const AABB& rhs ) {
		return lhs.min()[0] < rhs.max()[0] && lhs.max()[0] > rhs.min()[0] &&
			lhs.min()[1] < rhs.max()[1] && lhs.max()[1] > rhs.min()[1] &&
			lhs.min()[2] < rhs.max()[2] && lhs.max()[2] > rhs.min()[2];
	}

    template <typename Aabb, typename Plane>
    inline bool testAabbPlane(const Aabb& aabb, const Plane& plane) {
        typedef typename Aabb::vector_type Vector;
        const Vector center = aabb.center();
        const Vector extents = aabb.max() - center;
        return testCenteredAabbPlane(center, extents, plane.normal(), plane.distance());
    }

    template <typename Vector, typename Float>
    inline bool testCenteredAabbPlane(const Vector& center, const Vector& extents, const Vector& pn, const Float& pd) {
        const Float r = extents[0]*abs(pn[0]) + extents[1]*abs(pn[1]) + extents[2]*abs(pn[2]);
        const Float s = dot(pn, center) - pd;
        return abs(s) <= r;
    }

    template <typename T>
    T max(const T& a, const T& b) {
        if (a < b)
            return b;
        return a;
    }

    template <typename T>
    T min(const T& a, const T& b) {
        if (a < b)
            return a;
        return b;
    }

    template <typename T>
    T max(const T& a, const T& b, const T& c) {
        return max(max(a, b), c);
    }

    template <typename T>
    T min(const T&a, const T& b, const T& c) {
        return min(min(a, b), c);
    }

    template <typename Aabb, typename Triangle>
    struct TestAabbTriangle {

        enum { x, y, z };
        typedef typename Triangle::vector_type vec;
        typedef typename vec::value_type Float;

        static bool test(const Aabb& aabb, const Triangle& triangle) {
            // Shamelessly stolen from the book 'Real-time collision detection'.
            const vec c = aabb.center();
            const vec e = aabb.dim() * Float(.5);

            const vec v0 = triangle.pointA() - c;
            const vec v1 = triangle.pointB() - c;
            const vec v2 = triangle.pointC() - c;

            const vec f0 = v1 - v0;
            const vec f1 = v2 - v1;
            const vec f2 = v0 - v2;

            if (separatingAxisTest3(v0, v1, v2, f0, f1, f2, e)) {
                if (separatingAxisTest1(v0, v1, v2, e)) {
                    return separatingAxisTest2(c, e, v0, f0, f1);
                }
            }

            return false;
        }

        // Test 1: Three face normals from the AABB.
        static bool separatingAxisTest1(const vec& v0, const vec& v1, const vec& v2, const vec& e) {
            return (!(max(v0[x], v1[x], v2[x]) < -e[x] || min(v0[x], v1[x], v2[x]) > e[x])) &&
                (!(max(v0[y], v1[y], v2[y]) < -e[y] || min(v0[y], v1[y], v2[y]) > e[y])) &&
                (!(max(v0[z], v1[z], v2[z]) < -e[z] || min(v0[z], v1[z], v2[z]) > e[z]));
        }

        // Test 2: One face normal from the triangle.
        static bool separatingAxisTest2(const vec& center, const vec& extents, const vec& v0, const vec& f0, const vec& f1) {
            const vec normal = cross(f0, f1);
            typedef typename vec::value_type Float;
            const Float d = dot(normal, v0);
            return testCenteredAabbPlane(center, extents, normal, d);
        }

        // Test 3: Nine axes given by the cross products of any combination of axes from both the triangle and the AABB.
        static bool separatingAxisTest3(const vec& v0, const vec& v1, const vec& v2, const vec& f0, const vec& f1, const vec& f2, const vec& e) {
            return  testAxis00(v0, v1, v2, f0, e) &&
                    testAxis01(v0, v1, v2, f1, e) &&
                    testAxis02(v0, v1, v2, f2, e) &&
                    testAxis10(v0, v1, v2, f0, e) &&
                    testAxis11(v0, v1, v2, f1, e) &&
                    testAxis12(v0, v1, v2, f2, e) &&
                    testAxis20(v0, v1, v2, f0, e) &&
                    testAxis21(v0, v1, v2, f1, e) &&
                    testAxis22(v0, v1, v2, f2, e);
        }

        template <typename T>
        static inline T calcp0_00(const vec& v0, const vec& v1) {
            return v0[z]*v1[y] - v0[y]*v1[z];
        }
        
        template <typename T>
        static inline T calcp2_00(const vec& v0, const vec& v1, const vec& v2) {
            return -v2[y]*(v1[z] - v0[z]) + v2[z]*(v1[y] - v0[y]);
        }

        template <typename T>
        static inline T calcr_00(const vec& e, const vec& f0) {
            return e[1]*abs(f0[z]) + e[2]*abs(f0[y]);
        }

        static inline bool testAxis00(const vec& v0, const vec& v1, const vec& v2, const vec& f0, const vec& e) {
            // 0, -f0z, f0y
            const Float p0 = calcp0_00<Float>(v0, v1);
            const vec a = vec::make(0, -f0[z], f0[y]);
            const Float p2 = calcp2_00<Float>(v0, v1, v2);
            const Float r = calcr_00<Float>(e, f0);
            return !(max(-max(p0, p2), min(p0, p2)) > r);
        }

        static inline bool testAxis01(const vec& v0, const vec& v1, const vec& v2, const vec& f1, const vec& e) {
            // 0, -f1z, f1y (0, -(v2.z - v1.z), v2.y - v1.y)
            const Float p0 = v0[y]*-(v2[z] - v1[z]) + v0[z]*(v2[y] - v1[y]);
            const Float p1 = v1[z]*v2[y] - v1[y]*v2[z];
            const Float r = e[y]*abs(f1[z]) + e[z]*abs(f1[y]);
            const vec a = vec::make(0, -f1[z], f1[y]);
            return !(max(-max(p0, p1), min(p0, p1)) > r);
        }

        static inline bool testAxis02(const vec& v0, const vec& v1, const vec& v2, const vec& f2, const vec& e) {
            // 0, -f2z, f2y (0, -(v0.z - v2.z), v0.y - v2.y
            const Float p0 = v0[y]*v2[z] - v0[z]*v2[y];
            const Float p1 = v1[y]*-(v0[z] - v2[z]) + v1[z]*(v0[y] - v2[y]);
            const Float r = e[y]*abs(f2[z]) + e[z]*abs(f2[y]);
            const vec a = vec::make(0, -f2[z], f2[y]);
            return !(max(-max(p0, p1), min(p0, p1)) > r);
        }

        static inline bool testAxis10(const vec& v0, const vec& v1, const vec& v2, const vec& f0, const vec& e) {
            // f0z, 0, -f0x ((v1.z - v0.z), 0, -(v1.x - v0.x)
            const Float p0 = v0[x]*v1[z] - v0[z]*v1[x];
            const Float p2 = v2[x]*(v1[z] - v0[z]) + v2[z]*-(v1[x] - v0[x]);
            const Float r = e[x]*abs(f0[z]) + e[z]*abs(f0[x]);
            const vec a = vec::make(f0[z], 0, -f0[x]);
            return !(max(-max(p0, p2), min(p0, p2)) > r);
        }

        static inline bool testAxis11(const vec& v0, const vec& v1, const vec& v2, const vec& f1, const vec& e) {
            // f1z, 0, -f1x -> (v2.z - v1.z), 0, -(v2.x - v1.x)
            const Float p0 = v0[x]*(v2[z] - v1[z]) + v0[z]*-(v2[x] - v1[x]);
            const Float p1 = v1[x]*v2[z] - v1[z]*v2[x];
            const Float r = e[x]*abs(f1[z]) + e[z]*abs(f1[x]);
            const vec a = vec::make(f1[z], 0, -f1[x]);
            return !(max(-max(p0, p1), min(p0, p1)) > r);
        }

        static inline bool testAxis12(const vec& v0, const vec& v1, const vec& v2, const vec& f2, const vec& e) {
            // f2z, 0, -f2x -> (v0.z - v2.z), 0, -(v0.x - v2.x)
            const Float p0 = v0[z]*v2[x] - v0[x]*v2[z];
            const Float p1 = v1[x]*(v0[z] - v2[z]) + v1[z]*-(v0[x] - v2[x]);
            const Float r = e[x]*abs(f2[z]) + e[z]*abs(f2[x]);
            const vec a = vec::make(f2[z], 0, -f2[x]);
            return !(max(-max(p0, p1), min(p0, p1)) > r);
        }

        static inline bool testAxis20(const vec& v0, const vec& v1, const vec& v2, const vec& f0, const vec& e) {
            // -f0y, f0x, 0 -> -(v1.y - v0.y), (v1.x - v0.x), 0
            const Float p0 = v0[y]*v1[x] - v0[x]*v1[y];
            const Float p2 = v2[x]*-(v1[y] - v0[y]) + v2[y]*(v1[x] - v0[x]);
            const Float r = e[x]*abs(f0[y]) + e[y]*abs(f0[x]);
            const vec a = vec::make(-f0[y], f0[x], 0);
            return !(max(-max(p0, p2), min(p0, p2)) > r);
        }

        static inline bool testAxis21(const vec& v0, const vec& v1, const vec& v2, const vec& f1, const vec& e) {
            // -f1y, f1x, 0 -> -(v2.y - v1.y), (v2.x - v1.x), 0
            const Float p0 = v0[x]*-(v2[y] - v1[y]) + v0[y]*(v2[x] - v1[x]);
            const Float p1 = -v1[x]*v2[y] + v1[y]*v2[x];
            const Float r = e[x]*abs(f1[y]) + e[y]*abs(f1[x]);
            const vec a = vec::make(-f1[y], f1[x], 0);
            return !(max(-max(p0, p1), min(p0, p1)) > r);
        }

        static inline bool testAxis22(const vec& v0, const vec& v1, const vec& v2, const vec& f2, const vec& e) {
            // -f2y, f2x, 0 -> -(v0.y - v2.y), (v0.x - v2.x), 0
            const Float p0 = v0[x]*v2[y] - v0[y]*v2[x];
            const Float p1 = v1[x]*-(v0[y] - v2[y]) + v1[y]*(v0[x] - v2[x]);
            const Float r = e[x]*abs(f2[y]) + e[y]*abs(f2[x]);
            const vec a = vec::make(-f2[y], f2[x], 0);
            return !(max(-max(p0, p1), min(p0, p1)) > r);
        }

    };


    template <typename TRIANGLE, typename AAPLANE>
    bool testTriangleAxisAlignedPlane(const TRIANGLE& triangle, const AAPLANE& plane) 
    {
        return triangle.min()[plane.axis()] < plane.distance() &&
            triangle.max()[plane.axis()] > plane.distance();
    }

} }

#endif // math3d_intersections_hpp
