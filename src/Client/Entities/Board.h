#ifndef __H_BOARD_DRAWABLE
#define __H_BOARD_DRAWABLE

#include "IDrawable.h"
#include <bitset>
#include <array>


class Board : public IDrawable
{
public: 
	void Draw(IRenderer const* renderer) const override;

	enum class HighlightType : size_t {
		Selected = 0,
		LegalMoves = 1,
		Hover = 2,
		LastMove = 3,
		Count = 4
	};

	using Bitboard = std::bitset<64>;

	// Set/Clear a single square highlight
	void SetHighlight(HighlightType type, int row, int col);
	void ClearHighlight(HighlightType type, int row, int col);

	// Select a single square (exclusive): clears previous Selected bits then sets this square
	void SelectSquare(int row, int col);

	// Set/Clear whole layer
	void SetHighlightBits(HighlightType type, const Bitboard& bits);
	void ClearHighlightBits(HighlightType type);

	void ClearAllHighlights();

	bool IsHighlighted(HighlightType type, int row, int col) const;

private:
	static constexpr size_t LAYER_COUNT = static_cast<size_t>(HighlightType::Count);
	std::array<Bitboard, LAYER_COUNT> m_highlightLayers{};

};


#endif