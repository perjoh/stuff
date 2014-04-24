#include <SDL.h>
#include <vector>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include "ScopeExit.hpp"

class PixelBuffer32
{
public :
	PixelBuffer32( unsigned int width, unsigned int height )
		: width_(width)
		, height_(height)
		, pixels_( width*height, 0 )
	{ }

public :
	unsigned int width() const { return width_; }
	unsigned int height() const { return height_; }

	unsigned int pitch() const { return width()*4; }
	unsigned int sizeBytes() const { return pitch()*height(); }

	const void* pixels() const { return &pixels_[0]; }

public :
	void setPixel( unsigned int x, unsigned int y, Uint32 color )
	{
		if ( x < width() && y < height() )
		{
			pixels_[width()*y + x] = color;
		}
	}

private :
	unsigned int width_;
	unsigned int height_;

	std::vector<Uint32> pixels_;
};

class App
{
public :
	App( PixelBuffer32& pixelBuffer )
		: pixelBuffer_( pixelBuffer )
	{
	}

private :
	PixelBuffer32& pixelBuffer_;

private :
	App( const App& );
	App& operator=( const App& );
};


int main( int /*argc*/, char * /*argv*/[] ) 
{
	if ( ::SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS ) == -1 )
	{ 
		std::cout << "Failed to initialize SDL." << std::endl;
		return 1;
	}

	ScopeExit sdlQuit([]{
		::SDL_Quit();
	});

	const int ScreenWidth = 1024;
	const int ScreenHeight = 768;

	::SDL_Window* window = 
		SDL_CreateWindow( 
			"Test", 
			SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 
			ScreenWidth, 
			ScreenHeight, 
			SDL_WINDOW_SHOWN);

	if ( nullptr == window ) { 
		std::cout << "Failed to create window." << std::endl;
		return 1;
	}

	ScopeExit destroyWindow([window]{ 
		::SDL_DestroyWindow(window); 
	});

	::SDL_Renderer* renderer = ::SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if ( nullptr == renderer ) {
		std::cout << "Failed to create renderer." << std::endl;
		return 1;
	}

	ScopeExit destroyRenderer([renderer]{
		::SDL_DestroyRenderer(renderer); 
	});

	::SDL_Texture* texture = 
		::SDL_CreateTexture(
			renderer, 
			SDL_PIXELFORMAT_ARGB8888, 
			SDL_TEXTUREACCESS_STREAMING, 
			ScreenWidth, 
			ScreenHeight);

	if ( nullptr == texture ) {
		std::cout << "Failed to create texture." << std::endl;
		return 1;
	}

	ScopeExit destroyTexture([texture]{
		::SDL_DestroyTexture(texture);
	});

	PixelBuffer32 pixelBuffer( ScreenWidth, ScreenHeight );
	App app(pixelBuffer);

	bool keepRunning = true;
	while (keepRunning)
	{
		::SDL_Event e;
		while (::SDL_PollEvent(&e))
		{
			if (SDL_QUIT == e.type)
			{
				keepRunning = false;
			}
		}

		::SDL_UpdateTexture(
			texture, 
			nullptr,
			pixelBuffer.pixels(), 
			pixelBuffer.pitch());

		//::SDL_RenderClear(renderer);
		::SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		::SDL_RenderPresent(renderer);
	}

	return 0;
}
