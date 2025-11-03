#include "SDLTextureMgr.h"
#include <cassert>

void SDLTextureMgr::LoadTexture(const IRenderer& renderer, const std::string& name, const std::string& path)
{
	const auto& sdlRenderer = static_cast<const SDLRenderer&>(renderer);
	const auto& baseRenderer = sdlRenderer.GetBaseRenderer();

	SDL_Texture* loadedTexture = IMG_LoadTexture(baseRenderer, path.c_str());
	assert(loadedTexture);

	std::unique_ptr<SDLTexture> texture = std::make_unique<SDLTexture>(loadedTexture);

	m_textures.emplace(name, std::move(texture));
}

