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

	virtual Vec2 GetPosition() const { return m_pos; }

protected:
	std::vector<IDrawable> m_children;
	Vec2 m_pos;
};

#endif