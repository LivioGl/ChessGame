// Fill out your copyright notice in the Description page of Project Settings.


#include "GPawn.h"

// Sets default values
AGPawn::AGPawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);

	MaterialBlack = TEXT("/Game/Materials/MI_BlackPawn");
	MaterialWhite = TEXT("/Game/Materials/MI_WhitePawn");

}

TArray<ATile*> AGPawn::PawnValidMoves()
{
	// FVector PawnPossibleMoves = AGameField::GetRelativeLocationByXYPosition(x, y)
	// new possible positions: starting from (x, y), pawn can move to:
	// (x, y+i), with i = 1 or i = 2
	// if in (x+i, y+i) or (x-i, y+i) there's a piece, it can be captured by the pawn
	// GetTileStatus
	// Move to TileGridPosition
	// Get pointer to Tiles which represent a legal move

	return TArray<ATile*>();
}

// Called when the game starts or when spawned
void AGPawn::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AGPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

