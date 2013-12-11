#pragma once
#include "Importer.hpp"

namespace GeometryDb
{
    class ColladaImporter : public Importer
    {
    public :
        ColladaImporter( const char* colladaDocument );

    private :
        void populateMeshes( MeshMap& );

    private :
        std::string colladaDocument_;
    };
}
