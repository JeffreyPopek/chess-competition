#include "Board.h"
#include <cctype>

void Board::LoadFEN(const std::string& fen) 
{
    int row = 0, col = 0;

    for (char c : fen) 
    {
        if (c == ' ') 
            break; 

        if (c == '/') 
        {
            row++;
            col = 0;
            continue;
        }

        if (isdigit(c)) 
        {
            col += c - '0';
            continue;
        }

        PieceColor color = isupper(c) ? PieceColor::White : PieceColor::Black;
        PieceType type;

        switch (tolower(c)) 
        {
            case 'p': 
                type = PieceType::Pawn; 
                break;

            case 'n': 
                type = PieceType::Knight; 
                break;

            case 'b': 
                type = PieceType::Bishop; 
                break;

            case 'r': 
                type = PieceType::Rook; 
                break;

            case 'q': 
                type = PieceType::Queen; 
                break;

            case 'k': 
                type = PieceType::King; 
                break;

            default:  
                type = PieceType::None; 
                break;
        }

        board[row][col++] = Piece{ type, color };
    }
}

bool isInsideBoard(int row, int column) 
{
    return row >= 0 && row < 8 && column >= 0 && column < 8;
}

std::vector<Move> Board::GenerateValidMoves(PieceColor color) 
{
    std::vector<Move> moves;

    int direction;
    if (color == PieceColor::White) 
        direction = -1;
    else 
        direction = 1;
  

    for (int row = 0; row < 8; ++row) 
    {
        for (int col = 0; col < 8; ++col) 
        {
            Piece piece = board[row][col];

            if (piece.color != color) continue;

            switch (piece.type) 
            {
                case PieceType::Pawn: 
                {
                    int nextRow = row + direction;
                    if (isInsideBoard(nextRow, col) && board[nextRow][col].type == PieceType::None)
                        moves.push_back({ row, col, nextRow, col });
                 
                    break;
                }

                case PieceType::Knight:
                    // L shape
                    break;

                case PieceType::Bishop:
                    // diagonally
                    break;

                case PieceType::Rook:
                    // straight line
                    break;

                case PieceType::Queen:
                    // straight lines + diagonally
                    break;

                case PieceType::King:
                    // 1 tile in any direction
                    break;

                
                default:
                    break;
            }
        }
    }

    return moves;
}
