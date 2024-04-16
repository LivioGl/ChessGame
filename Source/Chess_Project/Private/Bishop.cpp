// Fill out your copyright notice in the Description page of Project Settings.
#include "Bishop.h"
//#include "GameField.h"
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

void ABishop::BishopValidMoves(TArray<ATile*>& Moves)
{
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	AGameField* Field = GameMode->Field;
	FVector2D BishopCurrentPosition(PieceGridPosition.X, PieceGridPosition.Y);
	// Current Bishop position saved in this pointer
	ATile* CurrentPosition = Field->TileMap[(BishopCurrentPosition)];

	FVector2D BMovements[4];
	BMovements[0] = FVector2D(1, 1);
	BMovements[1] = FVector2D(-1, 1);
	BMovements[2] = FVector2D(-1, -1);
	BMovements[3] = FVector2D(1, -1);
	for (int i = 0; i < 4; i++)
	{
		while (auto NewTiles = Field->TileMap[(BishopCurrentPosition + BMovements[i])])
		{
			// Check th
			if ((NewTiles)->GetTileStatus() == ETileStatus::EMPTY || (NewTiles)->GetChessPiece()->HumanTeam != this->HumanTeam)
			{

			}
		}
	}
	// New possible positions: starting from (x, y), with Bishop I can move to:
	// 0 < i < 8
	// (x+i, y+i), (x+i, y-i), (x-i, y-i), (x-i, y+i)
	// In the same positions, pieces, if present, can be captured.
	// GetTileStatus
	// Move to TileGridPosition
	// Get pointer to Tiles which represent a legal move
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

