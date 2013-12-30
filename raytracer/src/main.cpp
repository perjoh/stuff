#include <SDL.h>
#include <vector>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include "ScopeExit.hpp"


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

	std::vector<Uint32> pixels(ScreenWidth*ScreenHeight, 0xff00ff00);

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

		::SDL_UpdateTexture(texture, nullptr, &pixels[0], ScreenWidth*sizeof(Uint32));

		//::SDL_RenderClear(renderer);
		::SDL_RenderCopy(renderer, texture, nullptr, nullptr);
		::SDL_RenderPresent(renderer);
	}

	return 0;
}
