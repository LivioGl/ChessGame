// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"

// Sets default values
AKing::AKing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);
	MaterialBlack = TEXT("/Game/Materials/MI_BlackKing");
	MaterialWhite = TEXT("/Game/Materials/MI_WhiteKing");

}

TArray<ATile*> AKing::KingValidMoves()
{
	// FVector KingCurrentPosition = AGameField::GetRelativeLocationByXYPosition(x, y)
	// new possible positions: starting from (x, y), king can move to:
	// const int i = 1
	// (x, y+i), (x+i, y+i), (x+i, y), (x+i, y-i), (x, y-i), (x-i, y-i), (x-i, y), (x-i, y+i)
	// // In the same positions, pieces, if present, can be captured.
	// GetTileStatus
	// Move to TileGridPosition
	// Get pointer to Tiles which represent a legal move
	return TArray<ATile*>();
}

// Called when the game starts or when spawned
void AKing::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}