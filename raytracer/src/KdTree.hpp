#pragma once
#include "BinaryTree/ConstCacheFriendlyTree.hpp"
#include "BasicTypes.hpp"
#include <limits>

    template <typename Entity>
    class KdTree {

    private :
        struct NodePayload 
		{ 
            NodePayload()
                : leafBatchBegin()
                , leafBatchEnd()
            { }

            Plane splitPlane; // Optimize representation
            size_t leafBatchBegin; // Use unsigned short instead?
            size_t leafBatchEnd; // Use unsigned short instead?
        };

        typedef BinaryTree::BasicTree<NodePayload> Tree;
        typedef BinaryTree::ConstCacheFriendlyTree<NodePayload> OptimizedTree;
        typedef typename OptimizedTree::ConstIterator OptmizedTreeIterator;


    public :
        KdTree();

        template <typename Container>
        KdTree( const Container& entities );

    public :
        template <typename Container>
        void build( const Container& container );

    public :
        const Entity* findIntersection(const Ray& ray) const;

    public :
        size_t size() const;

    private :
        const Entity* findIntersectionNonLeafNode( const Line& line, OptmizedTreeIterator nodeIt ) const;
        const Entity* findIntersectionLeafNode( const Line& line, OptmizedTreeIterator nodeIt ) const;
        const Entity* findIntersectionInternal( const Line& line, OptmizedTreeIterator nodeIt ) const;


    private :
        template <typename Container>
        void buildInternal( 
			Container& container, 
			typename Tree::Node& node, 
			const BoundingBox& bb );

        template <typename Container>
        bool isEndCriteriaMet( const Container& c ) const;


        template <typename Entity>
        struct SortAlongAxis 
		{ 
            SortAlongAxis( size_t axis )
                : axis_( axis ) 
            { 
                assert( axis_ < 3 );
            }

            bool operator()( const Entity& a, const Entity& b ) const 
			{ 
                return a.min()[axis_] < b.min()[axis_];
            }

        private :
            const size_t axis_;
        };


        template <typename Container>
        static bool findOptimalSplitPlane( 
			Container& c, 
            const BoundingBox& boundingBox,
            Plane& splitPlaneOut );

        template <typename Container>
        static Float calcSplitCost( 
			const Container& entities, 
            const BoundingBox& boundingBox, 
            const AxisAlignedPlane& splitPlane );

        template <typename Container>
        static void partition( 
			const Container& c, 
            const BoundingBox& leftBoundingBox, 
            const BoundingBox& rightBoundingBox, 
            Container& leftContainer, 
            Container& rightContainer );

        static bool isOnPositiveSideOfSplitPlane( const Entity& e, const Plane& splitPlane );
        static bool isOnNegativeSideOfSplitPlane( const Entity& e, const Plane& splitPlane );

        static bool isPartitioningSuccessful( 
			size_t total, 
            size_t leftContainerSize, 
            size_t rightContainerSize );

        template <typename Container> 
        void storeEntities( 
			typename Tree::Node& node, 
            const Container& entities );

    private :
        Tree buildPhaseTree_;
        OptimizedTree optimizedTree_;
        std::vector<Entity> leafBatches_;
    };


//


    template <typename Entity>
    KdTree<Entity>::KdTree()
    { }


    template <typename Entity>
    template <typename Container>
    KdTree<Entity>::KdTree( const Container& entities ) 
	{ 
        build( entities );
    }


    template <typename Entity>
    template <typename Container>
    void KdTree<Entity>::build( const Container& container ) 
	{
        if ( !container.empty() ) 
		{
            Container sourceContainerCopy( container );

            using namespace math3d;
            const BoundingBox boundingBox = makeBoundingBox<BoundingBox>( sourceContainerCopy.begin(), sourceContainerCopy.end() );

            buildInternal( 
				sourceContainerCopy, 
				*buildPhaseTree_.setRoot( NodePayload() ), 
				boundingBox );

            optimizedTree_.buildFromSimpleBinaryTree( buildPhaseTree_ );
            buildPhaseTree_.clear();
        }
    }


    template <typename Entity>
    const Entity* KdTree<Entity>::findIntersection(const Ray& ray) const 
	{ 
        OptimizedTree::ConstIterator nodeIt = optimizedTree_.begin();
        const Line line(ray);
        return findIntersectionInternal(line, nodeIt);
    }


    template <typename Entity>
    size_t KdTree<Entity>::size() const 
	{
        return optimizedTree_.size();
    }


    template <typename Entity>
    const Entity* KdTree<Entity>::findIntersectionNonLeafNode( 
		const Line& line, 
		OptmizedTreeIterator nodeIt ) const 
	{ 
        assert( nodeIt.isValid() );
        assert( !nodeIt.isLeaf() );

        OptmizedTreeIterator leftIt( nodeIt.getLeft() ), 
                             rightIt( nodeIt.getRight() ); 

        if ( !nodeIt->splitPlane.frontSide( line.origin() ) ) 
		{
            std::swap( leftIt, rightIt );
        }

        Float t;
        const bool lineIsSplit = line.split( nodeIt->splitPlane, t );
        if ( lineIsSplit ) 
		{ 
            const Entity* found = findIntersectionInternal( Line(line, 0, t), leftIt );
            if ( 0 == found ) {
                found = findIntersectionInternal( Line(line, t, line.length()), rightIt );
            }

            return found;
        } 

        return findIntersectionInternal( line, leftIt );
    }


    template <typename Entity>
    const Entity* KdTree<Entity>::findIntersectionLeafNode( const Line& line, OptmizedTreeIterator nodeIt ) const 
	{ 
        const NodePayload& payload = *nodeIt;
        for ( size_t i = payload.leafBatchBegin; i < payload.leafBatchEnd; ++i )
		{ 
            const Float t = leafBatches_[i].intersect( line );
            if ( t > 0 ) 
			{ 
                return &leafBatches_[i];
            }
        }

        return 0;
    }


    template <typename Entity>
    const Entity* KdTree<Entity>::findIntersectionInternal( const Line& line, OptmizedTreeIterator nodeIt ) const 
	{ 
        if ( nodeIt.isValid() ) 
		{
            if ( !nodeIt.isLeaf() ) 
                return findIntersectionNonLeafNode( line, nodeIt );
			else 
                return findIntersectionLeafNode( line, nodeIt );
        }

        return 0;
    }


    // 
    template <typename Entity>
    template <typename Container>
    void KdTree<Entity>::buildInternal( 
		Container& entities, 
        typename Tree::Node& node, 
        const BoundingBox& boundingBox ) 
	{
        if ( !isEndCriteriaMet( entities ) ) 
		{ 
            Plane splitPlane;
            if ( findOptimalSplitPlane( entities, boundingBox, splitPlane ) ) 
			{ 
                // Split bounding box.
                BoundingBox leftBoundingBox, rightBoundingBox;
                boundingBox.split( 
					AxisAlignedPlane( splitPlane ), 
                    leftBoundingBox, 
                    rightBoundingBox );

                // Partition entities by split plane into two new containers.
                Container leftEntities, rightEntities;
                partition( 
					entities, 
                    leftBoundingBox,
                    rightBoundingBox,
                    leftEntities, 
                    rightEntities );

                entities.clear(); // Not needed anymore, discard it to free resources.

                node.value().splitPlane = splitPlane;

                // Build left side.
                buildInternal( 
					leftEntities, 
					*node.addLeft(NodePayload()), 
					leftBoundingBox );

                leftEntities.clear();

                // Build right side.
                buildInternal( 
					rightEntities, 
					*node.addRight(NodePayload()), 
					rightBoundingBox );
            }
            else 
			{ 
                // Failed to find a split plane, just store all the entities as they are.
                storeEntities( node, entities );
            }

        } 
		else 
		{ 
            storeEntities( node, entities );
        }
    }


    template <typename Entity>
    template <typename Container>
    bool KdTree<Entity>::isEndCriteriaMet( const Container& c ) const 
	{ 
        const size_t PreferredMaxEntitiesPerLeafNode = 4;
        return c.size() <= PreferredMaxEntitiesPerLeafNode;
    }


    template <typename Entity>
    template <typename Container>
    static bool KdTree<Entity>::findOptimalSplitPlane( 
		Container& entities, 
		const BoundingBox& boundingBox,
		Plane& splitPlaneOut ) 
	{
        const int splitAxis = boundingBox.widestAxis();
        const Float MaxCost = boundingBox.surfaceArea()*entities.size()*2;
        Float globalCostLeast = MaxCost + 1;

        int DBGcount = 0;

        for ( Container::const_iterator it = entities.begin(); it != entities.end(); ++it ) {

            ++DBGcount;

            // Code duplication, this needs to be fixed.

            {
                const Float d = it->min()[splitAxis] - std::numeric_limits<Float>::epsilon();
                const AxisAlignedPlane splitPlane( static_cast<math3d::Axis>( splitAxis ), d );
                const Float splitCostA = calcSplitCost( entities, 
                                                        boundingBox, 
                                                        splitPlane );

                if ( splitCostA < globalCostLeast ) {
                    globalCostLeast = splitCostA;
                    splitPlaneOut = splitPlane.toPlane();
                }
            }

            {
                const Float d = it->max()[splitAxis] + std::numeric_limits<Float>::epsilon();
                const AxisAlignedPlane splitPlane = AxisAlignedPlane( static_cast<math3d::Axis>( splitAxis ), d );
                const Float splitCostB = calcSplitCost( entities,
                                                        boundingBox,
                                                        splitPlane );

                if ( splitCostB < globalCostLeast ) {
                    globalCostLeast = splitCostB;
                    splitPlaneOut = splitPlane.toPlane();
                }
            }
        }

        return globalCostLeast < MaxCost;
    }


    template <typename Entity>
    template <typename Container>
    static Float KdTree<Entity>::calcSplitCost( 
		const Container& entities, 
		const BoundingBox& boundingBox, 
		const AxisAlignedPlane& splitPlane ) 
	{
        BoundingBox leftBoundingBox, rightBoundingBox;

        boundingBox.split( 
			splitPlane, 
			leftBoundingBox, 
			rightBoundingBox );

        size_t leftCount = 0;
        size_t rightCount = 0;

        for ( Container::const_iterator primitive = entities.begin(); primitive != entities.end(); ++primitive ) {

            if ( primitive->testIntersect( leftBoundingBox ) )
                ++leftCount;

            if (  primitive->testIntersect( rightBoundingBox ) )
                ++rightCount;
        }

        if ( leftCount < entities.size() && rightCount < entities.size() ) {

            const Float leftCost = Float(leftCount)*leftBoundingBox.surfaceArea();
            const Float rightCost = Float(rightCount)*rightBoundingBox.surfaceArea();
            return leftCost + rightCost;
        }

        return Float(entities.size())*boundingBox.surfaceArea()*2;
    }


    template <typename Entity>
    template <typename Container>
    void KdTree<Entity>::partition( 
		const Container& c, 
		const BoundingBox& leftBoundingBox,
		const BoundingBox& rightBoundingBox,
		Container& leftContainer, 
		Container& rightContainer ) 
	{
        for ( Container::const_iterator entityIt = c.begin(); entityIt != c.end(); ++entityIt ) {

            if ( entityIt->testIntersect( leftBoundingBox ) ) {
                leftContainer.push_back( *entityIt );
            }

            if ( entityIt->testIntersect( rightBoundingBox ) ) {
                rightContainer.push_back( *entityIt );
            }
        }
    }


    template <typename Entity>
    bool KdTree<Entity>::isOnPositiveSideOfSplitPlane( 
		const Entity& e, 
		const Plane& splitPlane ) 
	{ 
        return splitPlane.frontSide( e.max() ) ||
            splitPlane.frontSide( e.min() );
    }


    template <typename Entity>
    bool KdTree<Entity>::isOnNegativeSideOfSplitPlane( const Entity& e, const Plane& splitPlane ) {

        // Note: Cannot be implemented in terms of isOnPositiveSideOfSplitPlane.

        return !splitPlane.frontSide( e.max() ) ||
            !splitPlane.frontSide( e.min() );
    }


    template <typename Entity>
    bool KdTree<Entity>::isPartitioningSuccessful( 
		size_t total, 
        size_t leftContainerSize, 
        size_t rightContainerSize ) 
	{ 
        if ( total > 0 ) {
            if ( leftContainerSize > 0 ) {
                if ( rightContainerSize > 0 ) {

                    // Consider the partitioning successful if container growth is below a certain level.
                    const float GrowthPercentage = ((float(leftContainerSize + rightContainerSize) / total) - 1.0f)*100.0f;
                    const float MaxGrowth = 80;
                    return GrowthPercentage < MaxGrowth;
                }
            }
        }

        return false;
    }


    template <typename Entity>
    template <typename Container>
    void KdTree<Entity>::storeEntities( 
		typename Tree::Node& node, 
		const Container& entities ) 
	{ 
        // Note: Not thread safe. Needs to be fixed if build process is going to be parallel.

        NodePayload& payload = node.value();
        payload.leafBatchBegin = leafBatches_.size();
        payload.leafBatchEnd = payload.leafBatchBegin + entities.size();

        leafBatches_.insert( leafBatches_.end(), 
                             entities.begin(), 
                             entities.end() );
    }

