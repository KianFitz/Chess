#ifndef __H_SDL_RENDERER
#define __H_SDL_RENDERER

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>
#include "IRenderer.h"

class SDLRenderer: public IRenderer
{
public:
	SDLRenderer() : m_baseRenderer(nullptr) {};

	void DrawRect(const Vec2& pos, const Vec2& size, const RGB& colour) const override;
	void SetBaseRenderer(SDL_Renderer* renderer) { m_baseRenderer = renderer; }

private:
	SDL_Renderer* m_baseRenderer;
};

#endif


