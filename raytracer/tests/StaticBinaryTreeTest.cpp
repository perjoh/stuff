//#define BOOST_TEST_MODULE StaticBinaryTreeTest
#include <boost/test/unit_test.hpp>
#include "../src/BinaryTree/ConstCacheFriendlyTree.hpp"

    typedef BinaryTree::BasicTree<int> BinTree;
    typedef BinTree::Node Node;
    typedef BinaryTree::ConstCacheFriendlyTree<int> ConstTree;

// Have to enclose fixture in unnamed namespace otherwise fixture class will clash with other fixture classes with the same name.
namespace {

    struct Fixture {

        Fixture() {

            Node* _1 = bt.setRoot(1);
            Node* _2 = _1->addLeft(2);
            Node* _3 = _1->addRight(3);
            Node* _4 = _2->addLeft(4);
            Node* _5 = _2->addRight(5);
            _3->addLeft(6);
            _3->addRight(7);
            _4->addLeft(8);
            _5->addRight(9);
            cbt = ConstTree(bt);
        }

        BinTree bt;
        ConstTree cbt;
    };
};

BOOST_FIXTURE_TEST_SUITE(StaticBinaryTreeSuite, Fixture)

BOOST_AUTO_TEST_CASE( testBuild ) {

    ConstTree::ConstIterator _1 = cbt.begin();
    BOOST_CHECK_EQUAL(*_1, 1);
    ConstTree::ConstIterator _2 = _1; 
    _2.left();
    ConstTree::ConstIterator _3 = _1;
    _3.right();
    ConstTree::ConstIterator _4 = _2;
    _4.left();
    ConstTree::ConstIterator _5 = _2;
    _5.right();
    BOOST_CHECK_EQUAL( *_2, 2 );
    BOOST_CHECK_EQUAL( *_3, 3 );
    BOOST_CHECK_EQUAL( *_4, 4 );
    BOOST_CHECK_EQUAL( *_5, 5 );

    ConstTree::ConstIterator parent = _3;
    _3.left();
    BOOST_CHECK_EQUAL( *_3, 6 );
    _3 = parent;
    _3.right();
    BOOST_CHECK_EQUAL( *_3, 7 );
    _4.left();
    BOOST_CHECK_EQUAL( *_4, 8 );
    _5.right();
    BOOST_CHECK_EQUAL( *_5, 9 );
}

BOOST_AUTO_TEST_CASE( testSize ) {

    BOOST_CHECK_EQUAL( cbt.size(), 9 );
    BOOST_CHECK_EQUAL( cbt.sizeInBytes(), 9*(4+4) );
}

BOOST_AUTO_TEST_CASE( testInvalid ) {

    ConstTree cbt_;
    BOOST_CHECK( !cbt_.begin().isValid() );
}

BOOST_AUTO_TEST_CASE( testOneNodeIsLeaf ) {

    BinTree bt_;
    bt_.setRoot( 1 );
    ConstTree sbt_( bt_ );
    ConstTree::ConstIterator _1 = sbt_.begin();
    BOOST_CHECK( _1.isLeaf() );
}

BOOST_AUTO_TEST_SUITE_END()
