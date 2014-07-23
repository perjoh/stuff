#include "gtest.h"
#include "../src/KdTree.hpp"

typedef BinaryTree::BasicTree<int> BinTree;
typedef BinTree::Node Node;

using namespace raytracer;

namespace 
{
    const Point3d makePoint(Float x, Float y, Float z) 
    { 
        return math3d::make_vec(x, y, z);
    }


    class KdTreeTest : public ::testing::Test
    { 
	protected :
        KdTreeTest() 
        { 
            std::vector<Triangle> triangles;

            triangles.push_back(
                Triangle(
                    makePoint(1, -1, 0), 
                    makePoint(-1, -1, 0), 
                    makePoint(0, 1, 0) ) );

            kdTree.build(triangles);
        }


        KdTree<Triangle> kdTree;
    };

};


	TEST_F( KdTreeTest, testRayIntersect )
	{
		//_asm int 3;
		const Ray ray( makePoint(0, 0, -20), makePoint(0, 0, 1) );
		const Triangle* triangle = kdTree.findIntersection(ray);
		ASSERT_EQ( 1, kdTree.size() );
		ASSERT_TRUE( triangle != nullptr );
	}
