#include "SDLRenderer.h"

void SDLRenderer::DrawRect(Vec2 pos, Vec2 size, RGB colour) const
{
	SDL_FRect rect;
	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = size.x;
	rect.h = size.y;

	SDL_SetRenderDrawColor(m_baseRenderer, colour.R, colour.G, colour.G, uint8_t(1));
	SDL_RenderFillRect(m_baseRenderer, &rect);
}

