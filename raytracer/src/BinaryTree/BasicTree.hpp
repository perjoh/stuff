#pragma once
#include <boost/shared_ptr.hpp>
#include "BinaryTreeIterator.hpp"

namespace BinaryTree {

    template <typename Payload>
    class BasicTree
    {
    public :
        typedef Payload ValueType;

        class Node
        {
            friend class BasicTree;
        public :
            Node(const ValueType& p, Node* parent);

        public :
            Node* addLeft(const ValueType& p);
            Node* addRight(const ValueType& p);
            Node& operator=( const ValueType& p);

        public :
            Node* getLeft();
            const Node* getLeft() const;

            Node* getRight();
            const Node* getRight() const;

            Node* getParent();
            const Node* getParent() const;

            bool isLeaf() const;

            const ValueType& value() const;
            ValueType& value();

        private :
            typedef boost::shared_ptr<Node> NodePtr;
            NodePtr     left_;
            NodePtr     right_;
            Node*       parent_;
            ValueType   value_;
        };

    public :
        typedef BinaryTree::Iterator<BasicTree> Iterator;
        typedef BinaryTree::ConstIterator<BasicTree> ConstIterator;

    public :
        Iterator begin();
        ConstIterator begin() const;

    public :
        Node*       setRoot(const ValueType& p);
        Node*       root();
        const Node* root() const;
        size_t      size() const;

        void        clear();

    private :
        size_t size(const Node* node) const;

        typename Node::NodePtr root_;
    };


    template <typename T>
    BasicTree<T>::Node::Node(const T& value, Node* parent)
        : value_( value )
        , parent_( parent )
    {
    }

    template <typename T>
    typename BasicTree<T>::Node* BasicTree<T>::Node::addLeft(const T& value) 
    {
        left_ = NodePtr(new Node(value, this));
        return left_.get();
    }

    template <typename T>
    typename BasicTree<T>::Node* BasicTree<T>::Node::addRight(const T& value) 
    {
        right_ = NodePtr(new Node(value, this));
        return right_.get();
    }

    template <typename T>
    typename BasicTree<T>::Node& BasicTree<T>::Node::operator=(const T& value) 
    {
        value_ = value;
        return *this;
    }

    template <typename T>
    typename BasicTree<T>::Node* BasicTree<T>::Node::getLeft()
    {
        return left_.get();
    }

    template <typename T>
    const typename BasicTree<T>::Node* BasicTree<T>::Node::getLeft() const
    {
        return left_.get();
    }

    template <typename T>
    typename BasicTree<T>::Node* BasicTree<T>::Node::getRight()
    {
        return right_.get();
    }

    template <typename T>
    const typename BasicTree<T>::Node* BasicTree<T>::Node::getRight() const
    {
        return right_.get();
    }

    template <typename T>
    typename BasicTree<T>::Node* BasicTree<T>::Node::getParent()
    {
        return parent_;
    }

    template <typename T>
    const typename BasicTree<T>::Node* BasicTree<T>::Node::getParent() const
    {
        return parent_;
    }

    template <typename T>
    const T& BasicTree<T>::Node::value() const 
    {
        return value_;
    }

    template <typename T>
    T& BasicTree<T>::Node::value() 
    {
        return value_;
    }


    template <typename T>
    typename BasicTree<T>::Iterator BasicTree<T>::begin()
    {
        return Iterator( *this );
    }

    template <typename T>
    typename BasicTree<T>::ConstIterator BasicTree<T>::begin() const
    {
        return ConstIterator( *this );
    }


    template <typename T>
    typename BasicTree<T>::Node* BasicTree<T>::setRoot(const T& value) 
    {
        root_ = Node::NodePtr(new Node(value, 0));
        return root_.get();
    }

    template <typename T>
    typename BasicTree<T>::Node* BasicTree<T>::root()
    {
        return root_.get();
    }

    template <typename T>
    const typename BasicTree<T>::Node* BasicTree<T>::root() const
    {
        return root_.get();
    }

    template <typename T>
    size_t BasicTree<T>::size() const 
    {
        return size(root_.get());
    }


    template <typename T>
    void BasicTree<T>::clear() {
        root_.reset();
    }

    template <typename T>
    size_t BasicTree<T>::size(const Node* node) const 
    {
        if ( node )
            return size(node->getLeft()) + size(node->getRight()) + 1;

        return 0;
    }

}
