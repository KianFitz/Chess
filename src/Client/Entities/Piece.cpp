#include "Piece.h"

void Piece::Draw(IRenderer const* renderer) const
{
	renderer->DrawTexture(m_pos, m_texture);
}

