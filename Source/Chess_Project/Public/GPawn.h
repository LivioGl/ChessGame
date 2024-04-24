// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessPiece.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GPawn.generated.h"

UCLASS()
class CHESS_PROJECT_API AGPawn : public AChessPiece
{
	GENERATED_BODY()
	
public:	
	FString Type;
	// Sets default values for this actor's properties
	AGPawn();
	void GetValidMoves() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
