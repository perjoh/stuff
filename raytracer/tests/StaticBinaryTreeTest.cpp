#include "gtest.h"
#include "../src/BinaryTree/ConstCacheFriendlyTree.hpp"

    typedef BinaryTree::BasicTree<int> BinTree;
    typedef BinTree::Node Node;
    typedef BinaryTree::ConstCacheFriendlyTree<int> ConstTree;

// Have to enclose fixture in unnamed namespace otherwise fixture class will clash with other fixture classes with the same name.
namespace {

    class StaticBinaryTreeTest : public ::testing::Test {
	protected :
        StaticBinaryTreeTest() {

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

TEST_F( StaticBinaryTreeTest, testBuild ) {

    ConstTree::ConstIterator _1 = cbt.begin();
    ASSERT_EQ( 1, *_1 );
    ConstTree::ConstIterator _2 = _1; 
    _2.left();
    ConstTree::ConstIterator _3 = _1;
    _3.right();
    ConstTree::ConstIterator _4 = _2;
    _4.left();
    ConstTree::ConstIterator _5 = _2;
    _5.right();
    ASSERT_EQ( 2, *_2 );
    ASSERT_EQ( 3, *_3 );
    ASSERT_EQ( 4, *_4 );
    ASSERT_EQ( 5, *_5 );

    ConstTree::ConstIterator parent = _3;
    _3.left();
    ASSERT_EQ( 6, *_3 );
    _3 = parent;
    _3.right();
    ASSERT_EQ( 7, *_3 );
    _4.left();
    ASSERT_EQ( 8, *_4 );
    _5.right();
    ASSERT_EQ( 9, *_5 );
}

TEST_F( StaticBinaryTreeTest, testSize ) {

    ASSERT_EQ( 9, cbt.size() );
    ASSERT_EQ( 9*(4+4), cbt.sizeInBytes() );
}

TEST_F( StaticBinaryTreeTest,  testInvalid ) {

    ConstTree cbt_;
    ASSERT_TRUE( !cbt_.begin().isValid() );
}

TEST_F( StaticBinaryTreeTest,  testOneNodeIsLeaf ) {

    BinTree bt_;
    bt_.setRoot( 1 );
    ConstTree sbt_( bt_ );
    ConstTree::ConstIterator _1 = sbt_.begin();
    ASSERT_TRUE( _1.isLeaf() );
}
