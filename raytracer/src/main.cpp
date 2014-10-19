//#include "App.hpp"
#include <SDL.h>
#include <tchar.h>
#include "ScopeExit.hpp"

	int _tmain(int argc, _TCHAR* argv[])
	{
		if (::SDL_Init(SDL_INIT_VIDEO) != 0)
			return 1;

		auto sdlCleanup = ScopeExit([]{::SDL_Quit(); });

		SDL_Window* window = 
			SDL_CreateWindow(
				"raytracer",
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				640, 480,
				SDL_WINDOW_SHOWN);

		if (window == nullptr)
			return 1;

		auto windowCleanup = 
			ScopeExit([window]{
				::SDL_DestroyWindow(window); 
			});

		SDL_Renderer* renderer =
			SDL_CreateRenderer( window, -1, 0);

		if (renderer == nullptr)
			return 1;

		auto rendererCleanup = ScopeExit([renderer]{::SDL_DestroyRenderer(renderer); });

		SDL_Texture* texture =
			::SDL_CreateTexture(
				renderer, 
				SDL_PIXELFORMAT_ABGR8888, 
				SDL_TEXTUREACCESS_STREAMING, 
				640, 
				480);

		if (texture == nullptr)
			return 1;

		auto textureCleanup(ScopeExit([texture]{::SDL_DestroyTexture(texture); }));

		{
			unsigned char* pixels = nullptr;
			int pitch = 0;
			::SDL_LockTexture(
				texture,
				nullptr,
				reinterpret_cast<void**>(&pixels),
				&pitch);

			auto textureUnlock = ScopeExit([texture]{::SDL_UnlockTexture(texture); });

			for (int x = 0; x < 640; ++x)
			{
				for (int y = 0; y < 480; ++y)
				{
					pixels[y*pitch + x * 4 + 0] = static_cast<unsigned char>(x + y)*2;
					pixels[y*pitch + x * 4 + 1] = static_cast<unsigned char>(x + y)*3;
					pixels[y*pitch + x * 4 + 2] = static_cast<unsigned char>(x + y)*4;
				}
			}
		}

		bool quit = false;
		while ( !quit )
		{
			SDL_Event e;
			while (::SDL_PollEvent(&e))
			{
				if (SDL_QUIT == e.type)
					quit = true;
			}

			SDL_RenderCopy(renderer, texture, nullptr, nullptr);
			SDL_RenderPresent(renderer);
		}

		return 0;
    }
