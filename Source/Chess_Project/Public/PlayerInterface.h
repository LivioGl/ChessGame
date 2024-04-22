// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessMove.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"


extern class AKing;
extern class AMainGameMode;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};


class CHESS_PROJECT_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	TArray<ChessMove> Moves;
	void AllMoves(AMainGameMode* GameMode, TArray<ChessMove>& AllMoves);
	void DeleteChecks(AMainGameMode* GameMode, TArray<ChessMove>& AllMoves);
	int32 PlayerNumber;
	bool PlayerTeam;
	
	virtual void OnTurn() {};
	virtual void OnWin() {};
	virtual void OnLose() {};
	
};
