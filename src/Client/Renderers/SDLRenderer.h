#ifndef __H_SDL_RENDERER
#define __H_SDL_RENDERER

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_rect.h>
#include "IRenderer.h"
#include "../Textures/SDLTexture.h"

class SDLRenderer: public IRenderer
{
public:
	SDLRenderer() : m_baseRenderer(nullptr) {};

	void DrawRect(const Vec2& pos, const Vec2& size, const RGB& colour) const override;
	void DrawTexture(const Vec2& pos, ITexture& texture) const override;
	void SetBaseRenderer(SDL_Renderer* renderer) { m_baseRenderer = renderer; }
	SDL_Renderer* GetBaseRenderer() const { return m_baseRenderer; }

private:
	SDL_Renderer* m_baseRenderer;
};

#endif


