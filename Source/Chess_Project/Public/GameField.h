// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"
#include "GPawn.h"
#include "Tile.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameField.generated.h"

// Event to reset a tile's material to the original - to be called after clearing move hints
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResetTileMaterial);

UCLASS()
class CHESS_PROJECT_API AGameField : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameField();

	// keeps track of tiles
	UPROPERTY(Transient)
	TArray<ATile*> TileArray;

	// given a position returns a tile
	UPROPERTY(Transient)
	TMap<FVector2D, ATile*> TileMap;

	// static const int32 NOT_ASSIGNED = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float NormalizedCellPadding;

	// size of field
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Size;

	// Event
	FResetTileMaterial HintClearEvent;

	// TSubclassOf template class that provides UClass type safety

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATile> TileClassBlack;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATile> TileClassWhite;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AChessPiece> GPawn;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ABishop> Bishop;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ARook> Rook;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AKing> King;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AQueen> Queen;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AKnight> Knight;

	// tile size
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TileSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PieceSize;



	// Called when an instance of this class is placed (in editor) or spawned
	virtual void OnConstruction(const FTransform& Transform) override;

	// generate an empty game field
	void GenerateField();

	// Assign black or white color to a piece
	void ChangeMaterial(AChessPiece* S, bool IsBlack);

	// return the array of black pieces
	TArray<AChessPiece*> BlackPieces;

	// return the array of white pieces
	TArray<AChessPiece*> WhitePieces;

	// Generates the pieces
	void SpawnPieces(TArray<AChessPiece*> &WPieces, TArray<AChessPiece*> &BPieces);

	// return the array of tile pointers
	TArray<ATile*>& GetTileArray();

	// return a relative position given (x,y) position
	FVector GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const;

	// return (x,y) position given a relative position
	FVector2D GetXYPositionByRelativeLocation(const FVector& Location) const;

	// checking if is a valid field position
	inline bool IsValidPosition(const FVector2D Position) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
};
