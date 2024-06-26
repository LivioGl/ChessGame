// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessPiece.h"
#include "CoreMinimal.h"
#include "GameField.h"
#include "PlayerInterface.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

UCLASS()
class CHESS_PROJECT_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	bool IsGameOver;
	// Array of player interfaces
	TArray<IPlayerInterface*> Players;

	int32 CurrentPlayer;

	// UProperty reference to GameField
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGameField> GFieldClass;

	// Pointer to GameField object: Gamefield reference
	UPROPERTY(VisibleAnywhere)
	AGameField* Field;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 FieldSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Size;

	AMainGameMode();
 
	// Get the next player index
	int32 GetNextPlayer(int32 Player);

	// Called at the end of the game turn
	void TurnNextPlayer();
	void StartGame();

	// array that contains all valid moves
	TArray<ChessMove> ValidMoves;
	AChessPiece* MakeMove(ChessMove& Move, bool bIsRealMove);
	// function to go back after simulating a move (step necessary to check king security)
	void UnmakeMove(ChessMove& Move);
	void MovePieceToLocation(AChessPiece* CPiece, FVector2D Location) const;

	void PawnPromotion(AChessPiece* PromotedPiece);

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
