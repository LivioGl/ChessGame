// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInterface.h"
#include "MainGameMode.h"

// Add default functionality here for any IPlayerInterface functions that are not pure virtual.

void IPlayerInterface::AllMoves(AMainGameMode* GameMode, TArray<ChessMove>& AllMoves)
{
	for (auto Piece : this->PlayerTeam ? GameMode->Field->WhitePieces : GameMode->Field->BlackPieces)
	{
		if (Piece->bIsCaptured)
		{
			continue;
		}
		Piece->GetValidMoves();
	}
	// DeleteChecks(GameMode, Moves);
	
}

void IPlayerInterface::DeleteChecks(AMainGameMode* GameMode, TArray<ChessMove>& AllMoves)
{
	TArray<ChessMove> ToDelete;
	for (ChessMove Move : Moves)
	{
		// 
	}
}
