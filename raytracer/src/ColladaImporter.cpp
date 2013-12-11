#include "ColladaImporter.hpp"
#include <resource/collada/collada.hpp>

namespace GeometryDb
{
    ColladaImporter::ColladaImporter( const char* colladaDocument )
        : colladaDocument_( colladaDocument )
    { }


    void ColladaImporter::populateMeshes( MeshMap& meshMap ) {

        resource::collada::ColladaImport colladaImport( colladaDocument_.c_str() );
        colladaImport.importMeshesInto( meshMap );
    }
}
