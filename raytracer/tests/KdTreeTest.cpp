#include <gtest/gtest.h>
#include "../src/KdTree.hpp"

typedef BinaryTree::BasicTree<int> BinTree;
typedef BinTree::Node Node;

using namespace GeometricTypes;

class KdTreeTest : public testing::Test {
protected :
	void SetUp() {
		std::vector<Triangle> triangles;

		triangles.push_back(
			Triangle(
				makePoint(1, -1, 0), 
				makePoint(-1, -1, 0), 
				makePoint(0, 1, 0) ) );

		kdTree.build(triangles);
	}

protected :
    Point makePoint(Float x, Float y, Float z) { 
        return math3d::make_vec(x, y, z);
    }

protected :
	KdTree<Triangle> kdTree;
};

TEST_F(KdTreeTest, testRayIntersect) 
{ 
    const Ray ray( makePoint(0, 0, -20), makePoint(0, 0, 1) );
    const Triangle* triangle = kdTree.findIntersection(ray);
    EXPECT_EQ(1, kdTree.size());
    EXPECT_TRUE(triangle != 0);
}
