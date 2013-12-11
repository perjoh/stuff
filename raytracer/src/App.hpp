#pragma once

#include <exception>
#include <string>
#include "GeometryDb.hpp"

namespace Raytracer {

    class AppException : public std::exception {
    public :
        AppException( const char* what )
            : what_( what ) {
        }

        const char* what() const {
            return what_.c_str();
        }

    private :
        std::string what_;
    };

    class App {
    public :
        App( int argc, char* argv[] );
        ~App();

    public :
        int run();

    private :
        GeometryDb::Db geometryDb_;
    };


}
