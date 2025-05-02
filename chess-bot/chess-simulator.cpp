#include "chess-simulator.h"
#include <random>

// disservin's lib. drop a star on his hard work!
// https://github.com/Disservin/chess-library
using namespace ChessSimulator;


std::string ChessSimulator::Move(std::string fen) 
{
    chess::Board board(fen);

    // generate all legal moves for current board state
    chess::Movelist moves;
    chess::movegen::legalmoves(moves, board);

    // exit if no moves
    if (moves.size() == 0)
        return "";

    // check who's turn for minimax
    bool isWhite = board.sideToMove() == chess::Color::WHITE;

    // set best score
    int bestScore;
    if (isWhite)
        bestScore = -9999;
    else
		bestScore = 9999;

    chess::Move bestMove = moves[0];

    // eval each leagl move with minmax    
    for (chess::Move move : moves)
    {
        board.makeMove(move);                            
        int score = MinmaxSearch(board, MAX_DEPTH, !isWhite);        
        board.unmakeMove(move);                         

        if ((isWhite && score > bestScore) || (!isWhite && score < bestScore)) 
        {
            bestScore = score;
            bestMove = move;
        }
    }

    return chess::uci::moveToUci(bestMove);
}

int ChessSimulator::MinmaxSearch(chess::Board& board, int depth, bool max) 
{
    // end of search, reached max depth allowed
    if (depth == 0) 
        return EvalBoardState(board);


    // generate all legal moves from current board state
    chess::Movelist moves;
    chess::movegen::legalmoves(moves, board);

    // no moves, either stalemate or checkmate
    if (moves.size() == 0) 
        return EvalBoardState(board);

    int bestScore = 0;
    if(max)
		bestScore = -9999;
    else
		bestScore = 9999;

    // recursively evaluate moves
    for (chess::Move move : moves)
    {
        board.makeMove(move);
        int score = MinmaxSearch(board, depth - 1, !max);
        board.unmakeMove(move);

        if (max)
            bestScore = std::max(bestScore, score);
        else
            bestScore = std::min(bestScore, score);
    }

    return bestScore;
}

int ChessSimulator::EvalBoardState(const chess::Board& board) 
{
    /*
        loop through board
        check each tile
		if piece on it then change score based on color and piece value
        return score
    */

    int score = 0;

    for (int tile = 0; tile < 64; tile++) 
    {
        chess::Piece piece = board.at(chess::Square(tile));

        // if empty then skip
        if (piece == chess::Piece::NONE)
            continue;

        int value = 0;

		if (piece.type() == chess::PieceType::PAWN)
			value = PAWN_VALUE;
		else if (piece.type() == chess::PieceType::KNIGHT)
			value = KNIGHT_VALUE;
		else if (piece.type() == chess::PieceType::BISHOP)
			value = BISHOP_VALUE;
		else if (piece.type() == chess::PieceType::ROOK)
			value = ROOK_VALUE;
		else if (piece.type() == chess::PieceType::QUEEN)
			value = QUEEN_VALUE;
		else if (piece.type() == chess::PieceType::KING)
			value = KING_VALUE;
        
        // change score based on color and piece value
        if (piece.color() == chess::Color::WHITE)
            score += value;
        else
            score -= value;
    }

    return score; 
}