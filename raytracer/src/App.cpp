#include "App.hpp"
#include "ColladaImporter.hpp"

namespace Raytracer {

    App::App( int argc, char* argv[] ) {

        _asm int 3;

        GeometryDb::ColladaImporter importer( "resources/duck.dae" );
        geometryDb_.import( importer );
    }

    App::~App() {
    }

    int App::run() {
        return 0;
    }

}
