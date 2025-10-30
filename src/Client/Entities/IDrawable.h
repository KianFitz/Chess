#ifndef __H_IDRAWABLE
#define __H_IDRAWABLE

#include "../Renderers/IRenderer.h"


#include <vector>

class IDrawable
{
public: 
	virtual void Draw(IRenderer const* renderer) const = 0;

protected:
	std::vector<IDrawable> m_children;
};

#endif