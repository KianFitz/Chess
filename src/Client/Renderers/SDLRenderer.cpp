#include "SDLRenderer.h"

void SDLRenderer::DrawRect(const Vec2& pos, const Vec2& size, const RGB& colour) const
{
	SDL_FRect rect;
	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = size.x;
	rect.h = size.y;

	SDL_SetRenderDrawColor(m_baseRenderer, colour.R, colour.G, colour.G, uint8_t(1));
	SDL_RenderFillRect(m_baseRenderer, &rect);
}

