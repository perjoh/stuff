//
//  GeometryDb - Responsible for loading geometry from disk into memory and providing quick ways of querying this data.
//
//  Requirements: 
//      Be able to load geometry and material data from collada xml files.
//      Caching of previously loaded collada xml files. (Store binary data in a sub directory.)
//      Provide ways of querying geometry data with rays as input.
//
//  Todo:
//      How to organize the data? 
//          1. Create one kd-tree for each mesh and another kd-tree used for finding which mesh to search.
//              Pros: Entities stored in tree does not have to have references to material, results in smaller tree.
//              Cons: Potentially less efficient look ups. Have to locate mesh before finding which triangle that intersects.
//          2. Lump everything together and create one huge kd-tree.
//              Pros: Simpler search logic. If tree is built well performance might be better.
//              Cons: Every entity in tree needs a reference to a material. Takes up slightly more space. More memory intensive tree construction.
//

#include <string>
#include "GeometricTypes.hpp"
#include "Importer.hpp"
#include "KdTree.hpp"

namespace GeometryDb {

    struct Entity
    {
        GeometricTypes::Triangle shape;
        //Material* material; // Only if we go with approach 2.
    };

    class Db
    {
    public :
        void import( Importer& );
    
    public :
        size_t numEntities() const;

    public :
        const Entity* queryNearest( const GeometricTypes::Ray& ray ) const;

    private :
        MeshMap meshMap_;

    private :
        // Just store each triangle as three vertices without index arrays for now. Very space inefficient but good for CPU cache. This might be ok if memory footprint is not an issue.
        // No references to materials is stored for now.
        // Normal for each triangle should be stored also for faster intersection calculations.
        typedef std::vector<GeometricTypes::Triangle> Triangles;
        Triangles triangles_;
        KdTree<GeometricTypes::Triangle> kdTree_;

        void triangleAppender( int a, 
                               int b, 
                               int c, 
                               const Mesh::VertexArray& );
    };

}
