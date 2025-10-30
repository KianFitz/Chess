#ifndef __H_BOARD_STATE
#define __H_BOARD_STATE

#include <bitset>
#include <stack>

constexpr auto BITBOARD_SIZE = 64;

enum Piece
{
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	KING,
	QUEEN
};

enum Colour
{
	WHITE,
	BLACK
};

struct Move
{
	Colour colour;
};

class BoardState
{

private:

	std::bitset<BITBOARD_SIZE> m_white_board = (m_white_kings | m_white_queens | m_white_rooks | m_white_bishops | m_white_knights | m_white_pawns);
	std::bitset<BITBOARD_SIZE> m_black_board = (m_black_kings | m_black_queens | m_black_rooks | m_black_bishops | m_black_knights | m_black_pawns);
	std::bitset<BITBOARD_SIZE> m_total_board = (m_white_board | m_black_board);
	std::bitset<BITBOARD_SIZE> m_occupancy = ~m_total_board;

	std::bitset<BITBOARD_SIZE> m_white_kings;
	std::bitset<BITBOARD_SIZE> m_white_queens;
	std::bitset<BITBOARD_SIZE> m_white_rooks;
	std::bitset<BITBOARD_SIZE> m_white_bishops;
	std::bitset<BITBOARD_SIZE> m_white_knights;
	std::bitset<BITBOARD_SIZE> m_white_pawns;

	std::bitset<BITBOARD_SIZE> m_black_kings;
	std::bitset<BITBOARD_SIZE> m_black_queens;
	std::bitset<BITBOARD_SIZE> m_black_rooks;
	std::bitset<BITBOARD_SIZE> m_black_bishops;
	std::bitset<BITBOARD_SIZE> m_black_knights;
	std::bitset<BITBOARD_SIZE> m_black_pawns;

	std::stack<Move> m_move_queue;
};

#endif