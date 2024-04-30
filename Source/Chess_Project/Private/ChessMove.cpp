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
	MovedChessPiece = Piece;
	Start = Initial;
	End = Final;
	CapturedChessPiece = nullptr;
	if (Piece->Type == PieceType::PAWN && (End.X == 0 || End.X == 7))
	{
		bIsPromotion = true;
	}
		
}

ChessMove::ChessMove(AChessPiece* Piece, FVector2D Initial, FVector2D Final, AChessPiece* Captured)
{
	MovedChessPiece = Piece;
	Start = Initial;
	End = Final;
	CapturedChessPiece = Captured;
	bIsCaptured = Captured != nullptr;
	if (Piece->Type == PieceType::PAWN && (End.X == 0 || End.X == 7))
	{
		bIsPromotion = true;
	}
}

bool ChessMove::operator==(const ChessMove& Other) const
{
	return (MovedChessPiece == Other.MovedChessPiece && Start == Other.Start && End == Other.End && CapturedChessPiece == Other.CapturedChessPiece);
}

