// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessPiece.h"
#include "CoreMinimal.h"

extern class AChessPiece;


// This class implements moves administration on the board
class CHESS_PROJECT_API ChessMove
{
public:
	AChessPiece* MovedChessPiece;
	FVector2D Start;
	FVector2D End;
	// Pointer to captured piece
	AChessPiece* CapturedChessPiece;

	bool bIsCaptured = false;
	bool bIsPromotion = false;

	ChessMove();
	ChessMove(AChessPiece* Piece, FVector2D Initial, FVector2D Final);
	ChessMove(AChessPiece* Piece, FVector2D Initial, FVector2D Final, AChessPiece* Captured);

	bool operator==(const ChessMove& Other) const;
};
