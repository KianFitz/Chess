#include <cassert>
#include "Board.h"
#include <Utils/RGB.h>
#include <array>

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

	constexpr std::array<RGB, LAYER_COUNT> LAYER_COLORS = {
		RGB{.R = 255, .G = 64,  .B = 64  },
		RGB{.R = 64,  .G = 255, .B = 64  },
		RGB{.R = 64,  .G = 64,  .B = 255 },
		RGB{.R = 255, .G = 255, .B = 64  }
	};

	for (uint8_t x = 0; x < AREA; ++x)
	{
		for (uint8_t y = 0; y < AREA; ++y)
		{
			Vec2 rectPos(X_OFFSET + (x * TILE_SIZE), Y_OFFSET + (y * TILE_SIZE));
			Vec2 rectSize(TILE_SIZE, TILE_SIZE);

			// Draw base tile
			renderer->DrawRect(rectPos, rectSize, (x + y) % 2 == 0 ? BLACK : WHITE);

			// Compute index mapping: idx = row * AREA + col (row == y)
			const int idx = (y * AREA) + x;

			// Draw highlight overlays in layer order (later indices draw on top)
			for (size_t layer = 0; layer < LAYER_COUNT; ++layer)
			{
				if (m_highlightLayers[layer].test(static_cast<size_t>(idx)))
				{
					renderer->DrawRect(rectPos, rectSize, LAYER_COLORS[layer]);
				}
			}
		}
	}

	for (auto const& child : m_children)
	{
		child.Draw(renderer);
	}
}

void Board::SetHighlight(HighlightType type, int row, int col)
{
	if (row < 0 || col < 0 || row >= AREA || col >= AREA) return;
	const int idx = (row * AREA) + col;
	m_highlightLayers[static_cast<size_t>(type)].set(static_cast<size_t>(idx));
}

void Board::ClearHighlight(HighlightType type, int row, int col)
{
	if (row < 0 || col < 0 || row >= AREA || col >= AREA) return;
	const int idx = (row * AREA) + col;
	m_highlightLayers[static_cast<size_t>(type)].reset(static_cast<size_t>(idx));
}

void Board::SelectSquare(int row, int col)
{
	if (row < 0 || col < 0 || row >= AREA || col >= AREA) return;
	// Clear any previous selected bits
	m_highlightLayers[static_cast<size_t>(HighlightType::Selected)].reset();
	const int idx = (row * AREA) + col;
	m_highlightLayers[static_cast<size_t>(HighlightType::Selected)].set(static_cast<size_t>(idx));
}

void Board::SetHighlightBits(HighlightType type, const Bitboard& bits)
{
	m_highlightLayers[static_cast<size_t>(type)] = bits;
}

void Board::ClearHighlightBits(HighlightType type)
{
	m_highlightLayers[static_cast<size_t>(type)].reset();
}

void Board::ClearAllHighlights()
{
	for (auto &b : m_highlightLayers) b.reset();
}

bool Board::IsHighlighted(HighlightType type, int row, int col) const
{
	if (row < 0 || col < 0 || row >= AREA || col >= AREA) return false;
	const int idx = (row * AREA) + col;
	return m_highlightLayers[static_cast<size_t>(type)].test(static_cast<size_t>(idx));
}

