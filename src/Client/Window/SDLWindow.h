#ifndef __H_SDLWINDOW
#define __H_SDLWINDOW

#include <SDL3/SDL.h>
#include <memory>
#include "IWindow.h"
#include "../Renderers/IRenderer.h"
#include "../Renderers/SDLRenderer.h"

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
	void CheckForInput() override;

	void BeginDraw() override { SDL_RenderClear(m_baseRenderer.get()); }
	void FinishDraw() override { 
		SDL_SetRenderDrawColor(m_baseRenderer.get(), 0, 0, 0, 1);
		SDL_RenderPresent(m_baseRenderer.get()); 
	}

	IRenderer* GetRenderer() const override { return m_renderer.get(); }

	void Destroy() override;
private:
	SDLWindowPtr m_window;
	SDLRendererPtr m_baseRenderer;

	std::unique_ptr<SDLRenderer> m_renderer;
};



#endif