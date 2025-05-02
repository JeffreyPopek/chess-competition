#pragma once
#include <string>
#include "chess.hpp"


namespace ChessSimulator {
/**
 * @brief Move a piece on the board
 *
 * @param fen The board as FEN
 * @return std::string The move as UCI
 */

const int MAX_DEPTH = 3; // can change if you want
std::string Move(std::string fen);
int MinimaxSearch(chess::Board& board, int depth, bool max);
}