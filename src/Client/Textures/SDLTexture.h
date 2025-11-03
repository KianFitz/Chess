#ifndef __H_SDLTEXTURE
#define __H_SDLTEXTURE

#include "ITexture.h"
#include <memory>
#include <string>
#include <SDL3/SDL_render.h>

class SDLTexture : public ITexture
{
public:
	SDLTexture(SDL_Texture* texture) : m_baseTexture(texture) {};

	~SDLTexture() 
	{
		if (m_baseTexture)
		{
			SDL_DestroyTexture(m_baseTexture.get());
		}
	}

	SDL_Texture* GetBaseTexture() const { return m_baseTexture.get(); } 
private:
	std::unique_ptr<SDL_Texture> m_baseTexture;
};


#endif