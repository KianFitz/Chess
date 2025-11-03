#ifndef __H_SDLTEXTUREMGR
#define __H_SDLTEXTUREMGR

#include "ITextureMgr.h"
#include "SDLTexture.h"
#include <SDL3_image/SDL_image.h>
#include "../Renderers/SDLRenderer.h"

class SDLTextureMgr : public ITextureMgr
{
public:
	void LoadTexture (const IRenderer& renderer, const std::string& name, const std::string& path) override;
};

#endif