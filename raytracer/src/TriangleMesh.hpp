#pragma once

#include <vector>
#include <boost/static_assert.hpp>
#include <math3d/mathtypes.hpp>

namespace mesh {

    struct TriangleNormalArray
    {
        typedef std::vector< vec3i > TriangleArray;

        template <typename VertexArray>
        static void calcNormals( const VertexArray& vertexArray, const TriangleArray& triangleArray, PointArray& triangleNormals )
        {
            triangleNormals.reserve( triangleArray.size() );
            triangleNormals.clear();

            for ( TriangleArray::const_iterator triangleIt = triangleArray.begin(); triangleIt != triangleArray.end(); ++triangleIt )
            {
                const vec3f& p0 = vertexArray[(*triangleIt)[0]].position;
                const vec3f& p1 = vertexArray[(*triangleIt)[1]].position;
                const vec3f& p2 = vertexArray[(*triangleIt)[2]].position;

                const math3d::Triangle<float> t( p0, p1, p2 );

                triangleNormals.push_back( t.normal() );
            }
        }

        template <typename VertexArray>
        void calcNormals( const VertexArray& vertexArray, const TriangleArray& triangleArray )
        {
            calcNormals( vertexArray, triangleArray, normals );
        }

        template <typename VertexArray>
        void calcVertexNormals( const TriangleArray& triangleArray, VertexArray& vertexArray )
        {
            if ( vertexTriangleMap_.empty() )
            {
                if ( normals.empty() )
                {
                    calcNormals( vertexArray, triangleArray );
                }

                setupVertexTriangleMap( triangleArray );
            }

            assert( vertexTriangleMap_.size() <= vertexArray.size() );

            for ( size_t vertex = 0; vertex < vertexTriangleMap_.size(); ++vertex )
            {
                const IntArray& triangles = vertexTriangleMap_[ vertex ];
                if ( !triangles.empty() )
                {
                    vec3f& normal = vertexArray[ vertex ].normal;
                    normal[0] = normal[1] = normal[2] = 0.0F;
                    for ( IntArray::const_iterator triangleIt = triangles.begin(); triangleIt != triangles.end(); ++triangleIt )
                    {
                        normal += normals[*triangleIt];
                    }

                    normal /= float(triangles.size());
                }
            }
        }

        void swap( TriangleNormalArray& other ) throw ()
        {
            normals.swap( other.normals );
            vertexTriangleMap_.swap( other.vertexTriangleMap_ );
        }

        PointArray normals;

    private :
        void setupVertexTriangleMap( const TriangleArray& triangleArray )
        {
            VertexTriangleMap vertexTriangleMap;

            for ( size_t triangle = 0; triangle < triangleArray.size(); ++triangle )
            {
                const size_t numVerticesPerPoly = 3;
                for ( size_t vertexPoly = 0; vertexPoly < numVerticesPerPoly; ++vertexPoly )
                {
                    const size_t vertex = triangleArray[triangle][vertexPoly];
                    if ( !( vertex < vertexTriangleMap.size() ) )
                    {
                        vertexTriangleMap.resize( vertex+1 );
                    }

                    IntArray& vec = vertexTriangleMap[ vertex ];
                    if ( std::count( vec.begin(), vec.end(), triangle ) == 0 )
                    {
                        vec.push_back( triangle );
                    }
                }
            }

            vertexTriangleMap_.swap( vertexTriangleMap );
        }

    private :
        typedef std::vector< size_t > IntArray;
        typedef std::vector< IntArray > VertexTriangleMap; //! Keeps track of which triangles a vertex is part of. Ie. maps a vertex to the polygons it is part of.
        VertexTriangleMap vertexTriangleMap_; // FIXME: Is this really necessary to keep as a member? Seems as if it used only temporary while constructing vertex normals.
    };

    //
    template <typename Vertex>
	class TriangleMesh
	{
    public :
        typedef Vertex VertexType;
        typedef std::vector< Vertex > VertexArray;
        typedef std::vector< vec3i > TriangleArray;

    public :
        //
		TriangleMesh( ) 
		{ }

        //
        TriangleMesh( const VertexArray& va, const TriangleArray& ta ) 
            : vertexArray_( va ) 
            , triangleArray_( ta )
        { }

    public :
        size_t getVertexCount() const
        {
            return vertexArray_.size();
        }

        size_t getTriangleCount() const
        {
            return triangleArray_.size();
        }

    public :
        void addVertex( const Vertex& v ) 
        {
            vertexArray_.push_back( v );
        }

        void setVertices( const VertexArray& va )
        {
            VertexArray( va.begin(), va.end() ).swap( vertexArray_ );
        }

    public :
        void addTriangle( size_t a, size_t b, size_t c ) 
        {
            triangleArray_.push_back( vec3i::make(a,b,c) );
        }

        template <typename Triangle>
        void addTriangle( const Triangle& t ) 
        {
            triangleArray_.push_back( t[0] );
            triangleArray_.push_back( t[1] );
            triangleArray_.push_back( t[2] );
        }

        void setTriangles( const TriangleArray& ta )
        {
            TriangleArray( ta.begin(), ta.end() ).swap( triangleArray_ );
        }

    public :
        void swap( TriangleMesh& other )
        {
            vertexArray_.swap( other.vertexArray_ );
            triangleArray_.swap( other.triangleArray_ );
            triangleNormals_.swap( other.triangleNormals_ );
        }

    public :
        //! Checks if internal data is valid.
        bool integrityCheck() const 
        {
            return true;
        }

    public :
        void setupTriangleNormals()
        {
            triangleNormals_.calcNormals( vertexArray_, triangleArray_ );
        }

        void setupVertexNormals()
        {
            triangleNormals_.calcVertexNormals( triangleArray_, vertexArray_ );
        }

    public :
        const void* lockVertexArray() const 
        {
            return reinterpret_cast<const void*>( &(vertexArray_)[0] );
        }

        void unlockVertexArray() const { }

        size_t vertexArrayByteSize() const 
        {
            return vertexArray_.size()*sizeof(Vertex);
        }

        // Copy internals vertices into 'va'.
        template <typename VertexArray_>
        void copyVertexArray( VertexArray_& va ) const
        {
            VertexArray_( vertexArray_.begin(), vertexArray_.end() ).swap( va );
        }

    public :
        const void* lockTriangleArray() const {
            return reinterpret_cast<const void*>( &triangleArray_[0] );
        }

        void unlockTriangleArray() const { }

        size_t triangleArrayByteSize() const {
            return triangleArray_.size()*sizeof(TriangleArray::value_type);
        }

        size_t triangleArraySize() const {
            return triangleArray_.size();
        }

        // Copy internal triangles into 'to'.
        template <typename TriangleArray_>
        void copyTriangleArray( TriangleArray_& to ) const
        {
            TriangleArray_( triangleArray_.begin(), triangleArray_.end() ).swap( to );
        }

    public :
        //void transform( const matf& m );

        void scale( const vec3f& s )
        {
            for ( typename VertexArray::iterator it = vertexArray_.begin(); it != vertexArray_.end(); ++it )
            {
                it->position *= s;
            }
        }

        void move( const vec3f& d );

    public :
        template <typename FUN>
        void forEachTriangle( FUN& fun ) const
        {
            for ( TriangleArray::const_iterator it = triangleArray_.begin(); it != triangleArray_.end(); ++it )
            {
                fun( (*it)[0], (*it)[1], (*it)[2], vertexArray_ );
            }
        }

    public :
        // Bounding volume
		math3d::Aabb<typename Vertex::FloatType> makeBoundingBox() 
		{
			typedef math3d::vector<Vertex::FloatType> Vector;
			Vector min( vertexArray_.front().position );
			Vector max( min );

			for ( auto it : vertexArray_ )
			{
				for ( int i = 0; i < 3; ++i )
				{
					if ( min[i] < it->position[i] )
						min[i] = it->position[i];

					if ( max[i] > it->position[i] )
						max[i] = it->position[i];
				}
			}

			return math3d::Aabb<Vertex::FloatType>( min, max );
		}

    public :
        // Intersect

    private :
        VertexArray vertexArray_;
        TriangleArray triangleArray_;

        TriangleNormalArray triangleNormals_;
	};

    struct BasicVertex
    {
        BasicVertex()
            : position( vec3f::make( .0f, .0f, .0f ) )
            , normal( vec3f::make( .0f, .0f, .0f ) )
            , uv( vec2f::make( .0f, .0f ) )
        { }

        vec3f position;
        vec3f normal;
        vec2f uv;

        enum { ExpectedByteSize = (3+3+2)*4 };
		typedef float FloatType;
    };

	BOOST_STATIC_ASSERT( sizeof(float) == 4 );
    BOOST_STATIC_ASSERT( BasicVertex::ExpectedByteSize == sizeof( BasicVertex ) );

}
