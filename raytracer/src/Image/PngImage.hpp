#pragma once

#include "image.hpp"

namespace resource {
namespace png {

	void read( Image& img, const char* filename );
	void write( Image& img, const char* filename );

}
}

