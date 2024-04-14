// Fill out your copyright notice in the Description page of Project Settings.


#include "Rook.h"

// Sets default values
ARook::ARook()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);
	MaterialBlack = TEXT("/Game/Materials/MI_BlackRook");
	MaterialWhite = TEXT("/Game/Materials/MI_WhiteRook");

}

TArray<ATile*> ARook::RookValidMoves()
{
	// FVector RookPossibleMoves = AGameField::GetRelativeLocationByXYPosition(x, y)
	// new possible positions : starting from(x, y), rook can move to :
	// 0 < i < 8
	// (x, y-i), (x, y+i), (x-i, y), (x+i, y)
	// In the same positions, pieces, if present, can be captured.
	// GetTileStatus
	// Move to TileGridPosition
	// Get pointer to Tiles which represent a legal move
	return TArray<ATile*>();
}

// Called when the game starts or when spawned
void ARook::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARook::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
