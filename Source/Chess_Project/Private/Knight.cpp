// Fill out your copyright notice in the Description page of Project Settings.


#include "Knight.h"
#include "MainGameMode.h"

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

void AKnight::GetValidMoves()
{
	// Gamemode and Gamefield reference
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	AGameField* Field = GameMode->Field;
	// Current Knight position saved in this pointer
	FVector2D KnightCurrentPosition(PieceGridPosition.X, PieceGridPosition.Y);
	ATile* CurrentPosition = Field->TileMap[(KnightCurrentPosition)];
	// Directions of possibile moves
	FVector2D KnMovements[8];
	KnMovements[0] = FVector2D(1, 2);
	KnMovements[1] = FVector2D(2, 1);
	KnMovements[2] = FVector2D(2, -1);
	KnMovements[3] = FVector2D(1, -2);
	KnMovements[4] = FVector2D(-1, -2);
	KnMovements[5] = FVector2D(-2, -1);
	KnMovements[6] = FVector2D(-2, 1);
	KnMovements[7] = FVector2D(-1, 2);
	for (int i = 0; i < 8; i++)
	{
		while (auto NewTiles = Field->TileMap.Find(KnightCurrentPosition + KnMovements[i]))
		{
			// Check the directions where Knight is able to move and gets empty tiles or enemy pieces
			if ((*NewTiles)->GetTileStatus() == ETileStatus::EMPTY || (*NewTiles)->GetChessPiece()->bHumanTeam != this->bHumanTeam)
			{
				// Save the move in a gamemode array
				ChessMove KnightSingleMove(this, KnightCurrentPosition, KnightCurrentPosition + KnMovements[i], (*NewTiles)->GetChessPiece());
				GameMode->ValidMoves.Add(KnightSingleMove);
			}
			if ((*NewTiles)->GetTileStatus() == ETileStatus::OCCUPIED) break;
			// Cycle to cover all the chess board
			i++;
		}
	}
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