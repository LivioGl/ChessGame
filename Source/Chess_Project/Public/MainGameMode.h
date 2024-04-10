// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessPiece.h"
#include "CoreMinimal.h"
#include "GameField.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameMode.generated.h"

/**
 *
 */
UCLASS()
class CHESS_PROJECT_API AMainGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	// Pointer to GameField: Gamefield reference
	UPROPERTY(VisibleAnywhere)
	AGameField* Field;

	// Pointer to main class ChessPiece: Piece reference
	UPROPERTY(VisibleAnywhere)
	AChessPiece* Piece;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Size;

	// Proprietà di riferimento alla classe della GameField
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGameField> GFieldClass;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
