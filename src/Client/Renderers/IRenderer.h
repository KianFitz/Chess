#ifndef __H_IRENDERER
#define __H_IRENDERER

#include <Utils/Vec2.h>
#include <Utils/RGB.h>
#include "../Textures/ITexture.h"

class IRenderer
{
public:
	virtual void DrawRect(const Vec2& pos, const Vec2& size, const RGB& colour) const = 0;
	virtual void DrawTexture(const Vec2& pos, ITexture& texture) const = 0;
};


#endif
