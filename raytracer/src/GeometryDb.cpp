#include "GeometryDb.hpp"
#include <boost/bind.hpp>

namespace GeometryDb {

    void Db::import( Importer& importer ) {

        importer.populateMeshes( meshMap_ );

        // Convert meshes into basic triangle arrays with vertices duplicated(no index arrays).
        triangles_.clear();
        for ( MeshMap::const_iterator it = meshMap_.begin(); it != meshMap_.end(); ++it ) {

            // Append all triangles into one huge polygon soup.
            it->second.forEachTriangle(
                boost::bind( &Db::triangleAppender, this, _1, _2, _3, _4 ) );
        }

        kdTree_.build( triangles_ );

        // Implement import caching.

        //imp.importMeshes();
        //imp.importMaterials();
        //
        // Generate KD-tree.

    }


    size_t Db::numEntities() const {

        return meshMap_.size();
    }


    const Entity* Db::queryNearest( const GeometricTypes::Ray& ray ) const {

        return 0;
    }


    void Db::triangleAppender( int a, 
                               int b, 
                               int c, 
                               const Mesh::VertexArray& vertices ) {

        GeometricTypes::Triangle::vector_type Vec;

        triangles_.push_back( 
            GeometricTypes::Triangle(
                vertices[ a ].position,
                vertices[ b ].position,
                vertices[ c ].position ) );
    }

}
