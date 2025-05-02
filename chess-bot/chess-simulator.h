#pragma once
#include <string>
#include <unordered_map>
#include "chess.hpp"


namespace ChessSimulator {
/**
 * @brief Move a piece on the board
 *
 * @param fen The board as FEN
 * @return std::string The move as UCI
 */

	const int PAWN_VALUE = 1;
	const int KNIGHT_VALUE = 3;
	const int BISHOP_VALUE = 3;
	const int ROOK_VALUE = 5;
	const int QUEEN_VALUE = 9;
	const int KING_VALUE = 1000;

const int MAX_DEPTH = 5; // can change if you want
std::string Move(std::string fen);
int MinmaxSearch(chess::Board& board, int depth, bool max);
int EvalBoardState(const chess::Board& board);
}