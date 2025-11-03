#ifndef __H_IDRAWABLE
#define __H_IDRAWABLE

#include "../Renderers/IRenderer.h"
#include <Utils/Vec2.h>


#include <vector>

class IDrawable
{
public: 
	virtual void Draw(IRenderer const* renderer) const = 0;
	virtual ~IDrawable() = default;

protected:
	std::vector<IDrawable> m_children;
};

#endif