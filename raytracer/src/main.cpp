//#include "App.hpp"
#include <SDL.h>
#include <tchar.h>
#include <exception>
#include "ScopeExit.hpp"
#include "RayTracerOutput.hpp"
#include <boost/noncopyable.hpp>

namespace raytracer {

	class GuiException 
		: public std::exception
	{
	public:
		GuiException(const char* what)
			: std::exception(what)
		{
		}
	};

	class GuiWindow : boost::noncopyable
	{
	public:
		GuiWindow(unsigned int width, unsigned int height, const char* title)
			: texture_(nullptr)
			, renderer_(nullptr)
			, window_(nullptr)
		{
			if (::SDL_Init(SDL_INIT_VIDEO) != 0)
				throw GuiException("Failed to initialize SDL.");

			InitializeCenteredWindow(width, height, title);
		}

		~GuiWindow()
		{
			if (texture_)
				::SDL_DestroyTexture(texture_);

			if (renderer_)
				::SDL_DestroyRenderer(renderer_);

			if (window_)
				::SDL_DestroyWindow(window_);

			::SDL_Quit();
		}

	public:
		bool EventHandler()
		{
			bool quit = false;
			::SDL_Event e;
			while (::SDL_PollEvent(&e))
			{
				if (SDL_QUIT == e.type)
					quit = true;
			}

			PresentWindow();

			::SDL_Delay(100);

			return !quit;
		}

	public:
		void RenderBlock(
			const RgbBlock<>& block,
			unsigned int x,
			unsigned int y)
		{
			if (texture_)
			{
				unsigned char* pixels = nullptr;
				int pitch = 0;
				::SDL_LockTexture(
					texture_,
					nullptr,
					reinterpret_cast<void**>(&pixels),
					&pitch);

				::SDL_Texture* texture = texture_;
				auto textureUnlock = ScopeExit([texture]{::SDL_UnlockTexture(texture); });

				SDL_RenderCopy(renderer_, texture_, nullptr, nullptr);
			}
		}

	private:
		void InitializeCenteredWindow(unsigned int windowWidth, unsigned int windowHeight, const char* windowTitle)
		{
			window_ =
				::SDL_CreateWindow(
				windowTitle,
				SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				windowWidth, windowHeight,
				SDL_WINDOW_SHOWN);

			if (nullptr == window_)
				throw GuiException("Failed to create window.");

			renderer_ =
				::SDL_CreateRenderer(window_, -1, 0);

			texture_ =
				::SDL_CreateTexture(
				renderer_,
				SDL_PIXELFORMAT_ABGR8888,
				SDL_TEXTUREACCESS_STREAMING,
				windowWidth,
				windowHeight);
		}

		void PresentWindow()
		{
			SDL_RenderPresent(renderer_);
		}

	private:
		SDL_Window* window_;
		SDL_Renderer* renderer_;
		SDL_Texture* texture_;
	};
}


	int _tmain(int argc, _TCHAR* argv[])
	{
		/*if (::SDL_Init(SDL_INIT_VIDEO) != 0)
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
		}*/

		try {
			raytracer::GuiWindow window(640, 480, "test");
			while (window.EventHandler())
				;

			return 0; 
		}
		catch ( const raytracer::GuiException& )
		{ }

		return 1; 
    }
