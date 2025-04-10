#pragma once
#include "piece.h"
#include "move.h"

#include <vector>
#include <string>

class Board 
{
public:
    Piece board[8][8];

    void LoadFEN(const std::string& fen);
    std::vector<Move> GenerateValidMoves(PieceColor color);
};
