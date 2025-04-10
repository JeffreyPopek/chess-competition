#pragma once
#include <ctype.h>

enum class PieceType
{
	None,
	Pawn,
	Rook,
	Knight,
	Bishop,
	Queen,
	King
};

enum class PieceColor
{
	None,
	White,
	Black
};

struct Piece 
{
	PieceType type = PieceType::None;
	PieceColor color = PieceColor::None;
};
