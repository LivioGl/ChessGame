// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ChessMove.h"
#include "Tile.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChessPiece.generated.h"

UCLASS()
class CHESS_PROJECT_API AChessPiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChessPiece();

	bool bIsCaptured = false;
	bool bHumanTeam = true;
	FString Type;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D PieceGridPosition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UStaticMeshComponent* GetStatMeshComp();

	FString MaterialWhite;
	FString MaterialBlack;
	FString MoveHint;
	virtual void GetValidMoves();

	FVector2D GetGridPosition();
	
	void SetGridPosition(const double InX, const double InY);
	void SetGridPosition(FVector2D NewPosition);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
