#include "SDLRenderer.h"

void SDLRenderer::DrawRect(const Vec2& pos, const Vec2& size, const RGB& colour) const
{
	SDL_FRect rect;
	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = size.x;
	rect.h = size.y;

	// Use proper RGB channels and full alpha (255)
	SDL_SetRenderDrawColor(m_baseRenderer, colour.R, colour.G, colour.B, uint8_t(255));
	SDL_RenderFillRect(m_baseRenderer, &rect);
}

void SDLRenderer::DrawTexture(const Vec2& pos, ITexture& texture) const
{
	SDL_FRect rect;
	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = 96;
	rect.h = 96;

	const auto& sdlTexture = static_cast<const SDLTexture&>(texture);

	SDL_RenderTexture(m_baseRenderer, sdlTexture.GetBaseTexture(), nullptr, &rect);
}

