#include <cassert>
#include "Board.h"
#include <Utils/RGB.h>

constexpr float X_OFFSET = 576;
constexpr float Y_OFFSET = 156;
constexpr uint32_t TILE_SIZE = 96;
constexpr uint8_t AREA = 8;

constexpr RGB WHITE = {
	.R = 255,
	.G = 253,
	.B = 208
};

constexpr RGB BLACK = {
	.R = 181,
	.G = 101,
	.B = 29
};

void Board::Draw(IRenderer const* renderer) const
{
	assert(renderer);

	for (uint32_t x = 0; x < AREA; ++x)
	{
		for (uint32_t y = 0; y < AREA; ++y)
		{
			Vec2 rectPos(X_OFFSET + (x * TILE_SIZE), Y_OFFSET + (y * TILE_SIZE));
			Vec2 rectSize(TILE_SIZE, TILE_SIZE);

			renderer->DrawRect(rectPos, rectSize, (x + y) % 2 == 0 ? BLACK : WHITE);
		}
	}


	
	for (auto const& child : m_children)
	{
		child.Draw(renderer);
	}
}

