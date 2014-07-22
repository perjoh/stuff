#pragma once
#include "BasicTree.hpp"

namespace BinaryTree {

    // This is based on the data structure described in the book "Realtime Collision Detection" on page 272, section 6.6.2.
    //
    template <typename ValueType_>
    class ConstCacheFriendlyTree {

        struct Node;

    public :
        //typedef Iterator<ConstCacheFriendlyTree> Iterator; // Not available, this is a read only data structure.
        typedef ConstIterator<ConstCacheFriendlyTree, const Node> ConstIterator;
        typedef ValueType_ ValueType;

        friend class ConstIterator;

    public :
        ConstCacheFriendlyTree() 
        { }

        ConstCacheFriendlyTree( const BasicTree<ValueType>& simpleBt ) {
            buildFromSimpleBinaryTree( simpleBt );
        }

    public :
        void buildFromSimpleBinaryTree( const BasicTree<ValueType>& bt );

    private :
        void importNode( const typename BasicTree<ValueType>::Node* node );

    public :
        const ConstIterator begin() const {
            return ConstIterator( *this );
        }

        size_t size() const {
            return nodes_.size();
        }

        size_t sizeInBytes() const {
            return nodes_.size()*sizeof( NodeArray::value_type );
        }

        bool isEmpty() const {
            return nodes_.empty();
        }

    private :
        struct Node {
            Node( const ValueType& v )
                : value_( v )
            { }
            
            bool hasLeft() const {
                return traversal.hasLeftNode();
            }

            const Node* getLeft() const {
                assert( hasLeft() );
                return this + 1;
            }

            bool hasRight() const {
                return traversal.hasRightNode();

            }
            const Node* getRight() const {
                assert( hasRight() );
                return this + traversal.rightNodeOffset;
            }

            bool hasParent() const {
                return false;
            }
            Node* getParent() {
                return 0;
            }

            bool isLeaf() const {
                return traversal.isLeaf;
            }

            const ValueType& value() const {
                return value_;
            }

            ValueType& value() {
                return value_;
            }

            struct Traversal {
                enum { InvalidNodeOffset = ~0 };
                Traversal()
                    : hasLeftNode_( false )
                    , isLeaf( true )
                    , rightNodeOffset( InvalidNodeOffset )
                { }

                bool hasLeftNode() const {
                    return hasLeftNode_ != 0;
                }

                bool hasRightNode() const {
                    return rightNodeOffset != InvalidNodeOffset;
                }

                unsigned int hasLeftNode_ : 1;
                unsigned int isLeaf : 1;
                unsigned int rightNodeOffset : 30;
            } traversal;

        private :
            ValueType value_;
        };

        typedef std::vector<Node> NodeArray;
        NodeArray nodes_;

    private :
        const Node* root() const {

            if (!nodes_.empty())
                return &nodes_[0];
            return 0;
        }

        Node* root() {

            if (!nodes_.empty())
                return &nodes_[0];
            return 0;
        }
    };


    template <typename ValueType>
    void ConstCacheFriendlyTree<ValueType>::buildFromSimpleBinaryTree( const BasicTree<ValueType>& bt ) {

        nodes_.clear();
        nodes_.reserve( bt.size() );
        importNode( bt.root() );
    }

    template <typename ValueType>
    void ConstCacheFriendlyTree<ValueType>::importNode( const typename BasicTree<ValueType>::Node* node ) {

        if ( node ) {

            const size_t iThisNode = nodes_.size();
            nodes_.push_back( Node( node->value() ) );

            if ( node->getLeft() ) {

                nodes_[iThisNode].traversal.hasLeftNode_ = true;
                nodes_[iThisNode].traversal.isLeaf = false;

                importNode( node->getLeft() );
            }

            if ( node->getRight() ) {

                nodes_[iThisNode].traversal.rightNodeOffset = nodes_.size() - iThisNode;
                nodes_[iThisNode].traversal.isLeaf = false;

                importNode( node->getRight() );
            }
        }
    }

}
