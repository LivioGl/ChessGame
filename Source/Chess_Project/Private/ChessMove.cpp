// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessMove.h"

ChessMove::ChessMove()
{
	MovedChessPiece = nullptr;
	Start = FVector2D(0, 0);
	End = FVector2D(0, 0);
	CapturedChessPiece = nullptr;

}

ChessMove::ChessMove(AChessPiece* Piece, FVector2D Initial, FVector2D Final)
{
	Piece = MovedChessPiece;
	Initial = Start;
	Final = End;
}

ChessMove::ChessMove(AChessPiece* Piece, FVector2D Initial, FVector2D Final, AChessPiece* Captured)
{
	Piece = MovedChessPiece;
	Initial = Start;
	Final = End;
	Captured = CapturedChessPiece;


}

bool ChessMove::operator==(const ChessMove& Other) const
{
	return (MovedChessPiece == Other.MovedChessPiece && Start == Other.Start && End == Other.End && CapturedChessPiece == Other.CapturedChessPiece);
}

