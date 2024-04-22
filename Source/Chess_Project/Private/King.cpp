// Fill out your copyright notice in the Description page of Project Settings.


#include "King.h"
#include "MainGameMode.h"

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

void AKing::GetValidMoves()
{
	// Gamemode and Gamefield reference
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	AGameField* Field = GameMode->Field;
	// Current King position saved in this pointer
	FVector2D KingCurrentPosition(PieceGridPosition.X, PieceGridPosition.Y);
	ATile* CurrentPosition = Field->TileMap[(KingCurrentPosition)];
	// Directions of possibile moves
	FVector2D KMovements[8];
	KMovements[0] = FVector2D(0, 1);
	KMovements[1] = FVector2D(1, 1);
	KMovements[2] = FVector2D(1, 0);
	KMovements[3] = FVector2D(1, -1);
	KMovements[4] = FVector2D(0, -1);
	KMovements[5] = FVector2D(-1, -1);
	KMovements[6] = FVector2D(-1, 0);
	KMovements[7] = FVector2D(-1, 1);
	for (int i = 0; i < 8; i++)
	{
		while (auto NewTiles = Field->TileMap.Find(KingCurrentPosition + KMovements[i]))
		{
			// Check the directions where Bishop is able to move and gets empty tiles or enemy pieces
			if ((*NewTiles)->GetTileStatus() == ETileStatus::EMPTY || (*NewTiles)->GetChessPiece()->bHumanTeam != this->bHumanTeam)
			{
				// Save the move in a gamemode array
				ChessMove KingSingleMove(this, KingCurrentPosition, KingCurrentPosition + KMovements[i]);
				GameMode->ValidMoves.Add(KingSingleMove);
			}
			if ((*NewTiles)->GetTileStatus() == ETileStatus::OCCUPIED) break;
			
			i++;
		}
	}

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