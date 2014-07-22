#include "gtest.h"
#include "../src/BinaryTree/BasicTree.hpp"

typedef BinaryTree::BasicTree<int> BinTree;
typedef BinTree::Node Node;

namespace {
	class BinaryTreeTest : public ::testing::Test {
	protected :
		BinaryTreeTest()
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

TEST_F( BinaryTreeTest, testSize ) {
	EXPECT_EQ( 9, bt.size() );
}

TEST_F( BinaryTreeTest, testAssignValueToNode ) {
    BinTree bt_;
    Node& _1 = *bt_.setRoot(1);
    _1 = 2;
    //EXPECT_EQ(2, 2);
}

TEST_F( BinaryTreeTest, testBinaryTreeIterator ) 
{
    BinTree::ConstIterator it = bt.begin();
    EXPECT_EQ( 1, *it );

    ASSERT_TRUE( it.hasLeft() );
    ASSERT_TRUE( it.hasRight() );

    it.left();
    EXPECT_EQ( 2, *it );

    it--;
    EXPECT_EQ( 1, *it );

    it.right();
    EXPECT_EQ( 3, *it );

    --it;
    EXPECT_EQ( 1, *it );

    EXPECT_EQ( sizeof(int*), sizeof(BinTree::ConstIterator) );

    // Test whole tree.
    {
        it = bt.begin();

        ASSERT_TRUE( it.hasLeft() );
        ASSERT_TRUE( it.hasRight() );

        it.right();
        it.right();
        EXPECT_EQ( 7, *it );
        ASSERT_TRUE( !it.hasLeft() );
        ASSERT_TRUE( !it.hasRight() );

        --it;
        it.left();
        EXPECT_EQ( 6, *it );

        --it;
        --it;
        it.left();
        it.left();
        EXPECT_EQ( 4, *it );

        it.left();
        EXPECT_EQ( 8, *it );

        --it;
        --it;
        it.right();
        EXPECT_EQ( 5, *it );

        it.right();
        EXPECT_EQ( 9, *it );
    }

    // Test parent.
    {
        it = bt.begin();
        ASSERT_TRUE( !it.hasParent() );

        it.left();
        ASSERT_TRUE( it.hasParent() );
    }
}