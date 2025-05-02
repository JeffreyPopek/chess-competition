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

    // eval each leagl move with minimax    
    for (chess::Move move : moves)
    {
        board.makeMove(move);                            
        int score = MinimaxSearch(board, MAX_DEPTH, !isWhite);        
        board.unmakeMove(move);                         

        if ((isWhite && score > bestScore) || (!isWhite && score < bestScore)) 
        {
            bestScore = score;
            bestMove = move;
        }
    }

    return chess::uci::moveToUci(bestMove);
}

int ChessSimulator::MinimaxSearch(chess::Board& board, int depth, bool max) 
{
    // end of search, reached max depth allowed
    if (depth == 0) 
        return 0;

    // generate all legal moves from current board state
    chess::Movelist moves;
    chess::movegen::legalmoves(moves, board);

    // no moves, either stalemate or checkmate
    if (moves.size() == 0) 
        return 0;

    int bestScore = 0;
    if(max)
		bestScore = -9999;
    else
		bestScore = 9999;

    // recursively evaluate moves
    for (chess::Move move : moves)
    {
        board.makeMove(move);
        int score = MinimaxSearch(board, depth - 1, !max);
        board.unmakeMove(move);

        if (max)
            bestScore = std::max(bestScore, score);
        else
            bestScore = std::min(bestScore, score);
    }

    return bestScore;
}