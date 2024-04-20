// Fill out your copyright notice in the Description page of Project Settings.
#include "Queen.h"
#include "MainGameMode.h"

// Sets default values
AQueen::AQueen()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);

	MaterialBlack = TEXT("/Game/Materials/MI_BlackQueen");
	MaterialWhite = TEXT("/Game/Materials/MI_WhiteQueen");

}

void AQueen::GetValidMoves()
{
	// Gamemode and Gamefield reference
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	AGameField* Field = GameMode->Field;
	// Current Queen position saved in this pointer
	FVector2D QueenCurrentPosition(PieceGridPosition.X, PieceGridPosition.Y);
	ATile* CurrentPosition = Field->TileMap[(QueenCurrentPosition)];
	// Directions of possible moves
	FVector2D QMovements[8];
	QMovements[0] = FVector2D(0, 1);
	QMovements[1] = FVector2D(1, 1);
	QMovements[2] = FVector2D(1, 0);
	QMovements[3] = FVector2D(1, -1);
	QMovements[4] = FVector2D(0, -1);
	QMovements[5] = FVector2D(-1, -1);
	QMovements[6] = FVector2D(-1, 0);
	QMovements[7] = FVector2D(-1, 1);

	for (int i = 0; i < 8; i++)
	{
		while (auto NewTiles = Field->TileMap.Find(QueenCurrentPosition + QMovements[i]))
		{
			// Check the directions where Queen is able to move and gets empty tiles or enemy pieces
			if ((*NewTiles)->GetTileStatus() == ETileStatus::EMPTY || (*NewTiles)->GetChessPiece()->HumanTeam != this->HumanTeam)
			{
				// Save the move in a gamemode array
				ChessMove QueenSingleMove(this, QueenCurrentPosition, QueenCurrentPosition + QMovements[i]);
				GameMode->ValidMoves.Add(QueenSingleMove);
			}
			if ((*NewTiles)->GetTileStatus() == ETileStatus::OCCUPIED) break;
			// Cycle to cover all the chess board
			QMovements[i].X > 0 ? QMovements[i].X += 1 : QMovements[i].X -= 1;
			QMovements[i].Y > 0 ? QMovements[i].Y += 1 : QMovements[i].Y -= 1;
		}
	}
}


// Called when the game starts or when spawned
void AQueen::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AQueen::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}