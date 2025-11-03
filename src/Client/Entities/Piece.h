#ifndef __H_PIECE
#define __H_PIECE

#include "IDrawable.h"

class Piece : public IDrawable
{
public:
	Piece(ITexture& texture) : m_texture(texture) {};
	Piece(ITexture& texture, const Vec2& pos) : m_texture(texture), m_pos(pos) {};

	void Draw(IRenderer const* renderer) const override;

	void SetPos(float x, float y) { m_pos.x = x, m_pos.y = y; }

private:
	Vec2 m_pos;
	ITexture& m_texture;
};

#endif