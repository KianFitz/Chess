#include <Utils/Vec2.h>
#include <Utils/RGB.h>

#ifndef __H_IRENDERER
#define __H_IRENDERER

class IRenderer
{
public:
	virtual void DrawRect(Vec2 pos, Vec2 size, RGB colour) const = 0;
};


#endif
