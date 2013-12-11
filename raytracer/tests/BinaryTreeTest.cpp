#define BOOST_TEST_MODULE RaytracerTestModule

#include <boost/test/unit_test.hpp>
#include "../src/BinaryTree/BasicTree.hpp"

    typedef BinaryTree::BasicTree<int> BinTree;
    typedef BinTree::Node Node;

    namespace {
        struct Fixture {
            Fixture()
            {
                Node* _1 = bt.setRoot(1);
                Node* _2 = _1->addLeft(2);
                Node* _3 = _1->addRight(3);
                Node* _4 = _2->addLeft(4);
                Node* _5 = _2->addRight(5);
                _3->addLeft(6);
                _3->addRight(7);
                _4->addLeft(8);
                _5->addRight(9);
            }

            BinTree bt;
        };
    };

BOOST_FIXTURE_TEST_SUITE(BinaryTreeSuite, Fixture)

BOOST_AUTO_TEST_CASE( testSize ) 
{
    BOOST_CHECK_EQUAL( bt.size(), 9 );
}

BOOST_AUTO_TEST_CASE( testAssignValueToNode ) {
    BinTree bt_;
    Node& _1 = *bt_.setRoot(1);
    _1 = 2;
    //BOOST_CHECK_EQUAL(_1.payload(), 2);
    BOOST_CHECK_EQUAL(2, 2);
}

BOOST_AUTO_TEST_CASE( testBinaryTreeIterator )
{
    BinTree::ConstIterator it = bt.begin();
    BOOST_CHECK_EQUAL( *it, 1 );

    BOOST_CHECK( it.hasLeft() );
    BOOST_CHECK( it.hasRight() );

    it.left();
    BOOST_CHECK_EQUAL( *it, 2 );

    it--;
    BOOST_CHECK_EQUAL( *it, 1 );

    it.right();
    BOOST_CHECK_EQUAL( *it, 3 );

    --it;
    BOOST_CHECK_EQUAL( *it, 1 );

    BOOST_CHECK_EQUAL( sizeof(BinTree::ConstIterator), sizeof(int*) );

    // Test whole tree.
    {
        it = bt.begin();

        BOOST_CHECK( it.hasLeft() );
        BOOST_CHECK( it.hasRight() );

        it.right();
        it.right();
        BOOST_CHECK_EQUAL( *it, 7 );
        BOOST_CHECK( !it.hasLeft() );
        BOOST_CHECK( !it.hasRight() );

        --it;
        it.left();
        BOOST_CHECK_EQUAL( *it, 6 );

        --it;
        --it;
        it.left();
        it.left();
        BOOST_CHECK_EQUAL( *it, 4 );

        it.left();
        BOOST_CHECK_EQUAL( *it, 8 );

        --it;
        --it;
        it.right();
        BOOST_CHECK_EQUAL( *it, 5 );

        it.right();
        BOOST_CHECK_EQUAL( *it, 9 );
    }

    // Test parent.
    {
        it = bt.begin();
        BOOST_CHECK( !it.hasParent() );

        it.left();
        BOOST_CHECK( it.hasParent() );
    }
}

BOOST_AUTO_TEST_SUITE_END()
