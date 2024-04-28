// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInterface.h"
#include "MainGameMode.h"

// Add default functionality here for any IPlayerInterface functions that are not pure virtual.

// Gets all possible moves from a player and deletes illegal moves
void IPlayerInterface::AllMoves(AMainGameMode* GameMode)
{
	for (auto Piece : this->PlayerTeam ? GameMode->Field->WhitePieces : GameMode->Field->BlackPieces)
	{
		if (Piece->bIsCaptured)
		{
			continue;
		}
		Piece->GetValidMoves();
	}
	DeleteChecks(GameMode);

}

void IPlayerInterface::DeleteChecks(AMainGameMode* GameMode)
{
	TArray<ChessMove> ToDelete;
	for (ChessMove Move : GameMode->ValidMoves)
	{
		AChessPiece* Captured = GameMode->MakeMove(Move, false);
		if (this->King->IsKingUnderCheck(GameMode->Field))
		{
			ToDelete.AddUnique(Move);
		}
		Move.bIsCaptured = (Captured != nullptr);
		Move.CapturedChessPiece = Captured;

		GameMode->UnmakeMove(Move);
	}
	for (ChessMove Move : ToDelete)
	{
		GameMode->ValidMoves.Remove(Move);
	}
}

