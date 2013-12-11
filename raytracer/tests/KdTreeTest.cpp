#include <boost/test/unit_test.hpp>
#include "../src/KdTree.hpp"

    typedef BinaryTree::BasicTree<int> BinTree;
    typedef BinTree::Node Node;

using namespace GeometricTypes;

namespace 
{

    const Point makePoint(Float x, Float y, Float z) 
    { 
        return math3d::make_vec(x, y, z);
    }


    struct Fixture 
    { 
        Fixture() 
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


BOOST_FIXTURE_TEST_SUITE(KdTreeSuite, Fixture)


BOOST_AUTO_TEST_CASE(testRayIntersect) 
{ 
    //_asm int 3;
    const Ray ray( makePoint(0, 0, -20), makePoint(0, 0, 1) );
    const Triangle* triangle = kdTree.findIntersection(ray);
    BOOST_REQUIRE(kdTree.size() == 1);
    BOOST_REQUIRE(triangle != 0);
}


BOOST_AUTO_TEST_SUITE_END()
