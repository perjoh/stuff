#pragma once
#include "RayTracer.hpp"
#include "RayGenerator.hpp"
#include <exception>
#include <string>
#include <memory>

namespace raytracer {

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

	typedef std::pair<unsigned int, unsigned int> PixelPos;

    class App 
	{
    public :
        App( 
			const std::string& resource, 
			const PixelPos& targetDim, 
			const std::string& targetFileName );

        ~App();

    public :
        int run();

    private :
		std::pair<unsigned int, unsigned int> targetDim_;
		Camera camera_;
		RayGenerator rayGenerator_;
		RayTracableCollection rayTracables_;
		std::unique_ptr<RayTracer> rayTracer_;
    };

}
