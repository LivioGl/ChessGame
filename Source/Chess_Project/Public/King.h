// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "ChessPiece.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "King.generated.h"

UCLASS()
class CHESS_PROJECT_API AKing : public AChessPiece
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKing();
	void GetValidMoves() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
