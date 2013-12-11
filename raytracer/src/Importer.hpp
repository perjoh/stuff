#pragma once

#include "Mesh.hpp"

namespace GeometryDb 
{
    class Importer 
    {
    public :
        virtual ~Importer() { }

    public :
        virtual void populateMeshes( MeshMap& ) = 0;
    };
}
