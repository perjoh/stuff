#pragma once

#include <cassert>

namespace BinaryTree {

    template <typename Container, typename NodeType = const typename Container::Node>
    class ConstIterator
    {
    public :
        typedef typename Container::ValueType ValueType;
        typedef typename Container::Node Node;

    public :
        ConstIterator()
            : node_( 0 )
        { }

        ConstIterator( const Container& c )
            : node_( c.root() )
        { }

        ConstIterator( const Node* node )
            : node_( node )
        { }

    public :
        const ValueType& operator*() const
        {
            return node_->value();
        }

        const ValueType* operator->() const {
            return &node_->value();
        }

    public :
        bool hasLeft() const
        {
            return node_->getLeft() != 0;
        }

        void left()
        {
            assert( hasLeft() );
            node_ = node_->getLeft();
        }

        const ConstIterator getLeft() const {
            return ConstIterator( node_->getLeft() );
        }

    public :
        bool hasRight() const
        {
            return node_->getRight() != 0;
        }

        void right()
        {
            assert( hasRight() );
            node_ = node_->getRight();
        }

        const ConstIterator getRight() const {
            return ConstIterator( node_->getRight() );
        }

    public :
        bool hasParent() const
        {
            return node_->getParent() != 0;
        }

        void parent()
        {
            assert( hasParent() );
            node_ = node_->getParent();
        }

        const ConstIterator getParent() const {
            return node_->getParent();
        }

    public :
        const ConstIterator operator--(int)
        {
            ConstIterator tmp( *this );
            node_ = node_->getParent();
            return tmp;
        }

        void operator--()
        {
            node_ = node_->getParent();
        }

    public :
        bool isValid() const
        {
            return node_ != 0;
        }

        bool isLeaf() const
        {
            return node_
                ? node_->isLeaf()
                : false;
        }

    protected :
        const NodeType* node_;
    };


    template <typename Container>
    class Iterator : public ConstIterator<Container, typename Container::Node>
    {
        typedef ConstIterator<Container, typename Container::Node> Super;

    public :
        Iterator( Container& c )
            : Super( c.root() )
        { }

    public :
        typedef ConstIterator<Container, const typename Container::Node> ConvertType;
        operator ConvertType() const 
        {
            return ConvertType( node_ );
        }

    public :
        ValueType& operator*() {
            return node_->value(); 
        }

        ValueType* operator->() {
            return &node_->value();
        }

        const Iterator operator--(int)
        {
            Iterator tmp( *this );
            --(*this);
            return tmp;
        }

    private :
        //const ConstIterator<Container> operator--(int);
    };

}
