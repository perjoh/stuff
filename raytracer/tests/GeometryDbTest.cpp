
#include <boost/test/unit_test.hpp>
#include <resource/collada/collada.hpp>
#include "../src/GeometryDb.hpp"

using namespace GeometryDb;

namespace 
{
    struct Fixture {
    };

    class TestImporter : public Importer 
    { 
        void populateMeshes( MeshMap& meshMap ) 
        { 
            resource::collada::ColladaImport colladaImport("res/duck.dae");
            colladaImport.importMeshesInto(meshMap);
        }
    };
};

BOOST_FIXTURE_TEST_SUITE( GeometryDbSuite, Fixture )

BOOST_AUTO_TEST_CASE( testConstruction ) 
{ 
    TestImporter importer;

    Db db;
    db.import(importer);
    BOOST_CHECK_EQUAL(db.numEntities(), 1);
}

BOOST_AUTO_TEST_SUITE_END()
