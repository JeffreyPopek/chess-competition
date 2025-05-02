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
std::unordered_map<chess::PieceType, int> PIECE_WEIGHTS =
{
    {chess::PieceType::PAWN,   1},
    {chess::PieceType::KNIGHT, 3},
    {chess::PieceType::BISHOP, 3},
    {chess::PieceType::ROOK,   5},
    {chess::PieceType::QUEEN,  9},
    {chess::PieceType::KING, 1000}
};

const int MAX_DEPTH = 3; // can change if you want
std::string Move(std::string fen);
int MinimaxSearch(chess::Board& board, int depth, bool max);
int EvalBoardState(const chess::Board& board);
}