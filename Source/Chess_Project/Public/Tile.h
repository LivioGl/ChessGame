// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

// Gestione delle caselle

UENUM()
enum class ETileStatus : uint8
{
	EMPTY	UMETA(DisplayName = "Empty"),
	OCCUPIED	UMETA(DisplayName = "Occupied"),
};

// Extern class used for generic tile position getter
extern class AChessPiece;

UCLASS()
class CHESS_PROJECT_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

	// set the player owner and the status of a tile
	void SetTileStatus(const int32 TileOwner, const ETileStatus TileStatus);

	// get the tile status
	ETileStatus GetTileStatus();

	// get the tile owner
	int32 GetOwner();

	// get the piece type in a specific tile
	AChessPiece* GetChessPiece();

	void SetChessPiece(AChessPiece* NewPiece);

	// set the (x, y) position
	void SetGridPosition(const double InX, const double InY);

	// get the (x, y) position
	FVector2D GetGridPosition();

	UStaticMeshComponent* GetStatMeshComp();

	// Function called to reset a material
	UFUNCTION()
	void ResetMaterial();

	const FString Black = TEXT("/Game/Materials/MI_Black");
	const FString White = TEXT("/Game/Materials/MI_Tile");

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Pointer to piece actually occupying this tile 
	AChessPiece* Piece = nullptr;

	// Componente scena
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* Scene;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ETileStatus Status;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 PlayerOwner;

	// (x, y) position of the tile
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D TileGridPosition;

public:	

	// Called every frame
	// virtual void Tick(float DeltaTime) override;

};
