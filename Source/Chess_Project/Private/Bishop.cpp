// Fill out your copyright notice in the Description page of Project Settings.
#include "Bishop.h"
#include "MainGameMode.h"

// Sets default values
ABishop::ABishop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);
	MaterialBlack = TEXT("/Game/Materials/MI_BlackBishop");
	MaterialWhite = TEXT("/Game/Materials/MI_WhiteBishop");
}

TArray<ATile*> ABishop::BishopValidMoves()
{
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	AGameField* Field = GameMode->Field;
	FVector BishopCurrentPosition = Field->GetRelativeLocationByXYPosition(PieceGridPosition.X, PieceGridPosition.Y);
	// New possible positions: starting from (x, y), with Bishop I can move to:
	// 0 < i < 8
	// (x+i, y+i), (x+i, y-i), (x-i, y-i), (x-i, y+i)
	// In the same positions, pieces, if present, can be captured.
	// GetTileStatus
	// Move to TileGridPosition
	// Get pointer to Tiles which represent a legal move


	return TArray<ATile*>();
}

// Called when the game starts or when spawned
void ABishop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABishop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

