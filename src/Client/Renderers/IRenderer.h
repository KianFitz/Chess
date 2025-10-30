#include <Utils/Vec2.h>
#include <Utils/RGB.h>

#ifndef __H_IRENDERER
#define __H_IRENDERER

class IRenderer
{
public:
	virtual void DrawRect(const Vec2& pos, const Vec2& size, const RGB& colour) const = 0;
};


#endif
