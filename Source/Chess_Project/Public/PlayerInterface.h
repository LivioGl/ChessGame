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

public:

	AKing* King;
	int32 PlayerNumber;
	bool PlayerTeam;

	void AllMoves(AMainGameMode* GameMode);
	void DeleteChecks(AMainGameMode* GameMode);
	
	virtual void OnTurn() {};
	virtual void OnWin() {};
	virtual void OnTie() {};
	virtual void OnLose() {};
	
};
