// Fill out your copyright notice in the Description page of Project Settings.


#include "Knight.h"

// Sets default values
AKnight::AKnight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);

	MaterialBlack = TEXT("/Game/Materials/MI_BlackKnight");
	MaterialWhite = TEXT("/Game/Materials/MI_WhiteKnight");

}

TArray<ATile*> AKnight::KnightValidMoves()
{
	// FVector KnightPossibleMoves = AGameField::GetRelativeLocationByXYPosition(x, y)
	// new possible positions : starting from(x, y), knight can move to :
	// const int i = 1
	// (x+i, y+2i), (x+2i, y+i), (x+2i, y-i), (x+i, y-2i), (x-i, y-2i), (x-2i, y-i), (x-2i, y+i), (x-i, y+2i)
	// // In the same positions, pieces, if present, can be captured.
	// GetTileStatus
	// Move to TileGridPosition
	// Get pointer to Tiles which represent a legal move
	return TArray<ATile*>();
}

// Called when the game starts or when spawned
void AKnight::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKnight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}