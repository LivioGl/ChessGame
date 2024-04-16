// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMove.h"

ChessMove::ChessMove(AChessPiece* Piece, FVector2D Initial, FVector2D Final)
{
	MovedChessPiece = Piece;
	Initial = Start;
	Final = End;
}

ChessMove::ChessMove()
{
	ChessMove Move;
}

//bool ChessMove::operator==(const ChessMove& other) const
//{
//    return false;
//}

