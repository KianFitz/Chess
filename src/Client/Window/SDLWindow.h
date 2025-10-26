#ifndef __H_SDLWINDOW
#define __H_SDLWINDOW

#include <SDL3/SDL.h>
#include <SDl3/SDL_main.h>
#include <memory>
#include "IWindow.h"



struct SDLWindowDeleter 
{
	void operator()(SDL_Window* window) const noexcept 
	{
		if (window)
			SDL_DestroyWindow(window);
	}
};

struct SDLRendererDeleter
{
	void operator()(SDL_Renderer* renderer) const noexcept
	{
		if (renderer)
			SDL_DestroyRenderer(renderer);
	}
};

using SDLWindowPtr = std::unique_ptr<SDL_Window, SDLWindowDeleter>;
using SDLRendererPtr = std::unique_ptr<SDL_Renderer, SDLRendererDeleter>;


class SDLWindow : public IWindow
{
public:
	SDLWindow() {}
	bool Create(const WindowCreationArgs& args) override;
	void Update() override;
	void Destroy() override;
private:
	SDLWindowPtr m_window;
	SDLRendererPtr m_renderer;
};



#endif