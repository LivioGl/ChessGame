// Fill out your copyright notice in the Description page of Project Settings.


#include "Rook.h"
#include "MainGameMode.h"

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

void ARook::GetValidMoves()
{
	// Gamemode and Gamefield reference
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	AGameField* Field = GameMode->Field;
	// Current Rook position saved in this pointer
	FVector2D RookCurrentPosition(PieceGridPosition.X, PieceGridPosition.Y);
	ATile* CurrentPosition = Field->TileMap[(RookCurrentPosition)];
	// Directions of possible moves
	FVector2D BMovements[4];
	BMovements[0] = FVector2D(0, 1);
	BMovements[1] = FVector2D(-1, 0);
	BMovements[2] = FVector2D(0, -1);
	BMovements[3] = FVector2D(1, 0);
	for (int i = 0; i < 4; i++)
	{
		while (auto NewTiles = Field->TileMap.Find(RookCurrentPosition + BMovements[i]))
		{
			// Check the directions where Rook is able to move and gets empty tiles or enemy pieces
			if ((*NewTiles)->GetTileStatus() == ETileStatus::EMPTY || (*NewTiles)->GetChessPiece()->bHumanTeam != this->bHumanTeam)
			{
				// Save the move in a gamemode array
				ChessMove RookSingleMove(this, RookCurrentPosition, RookCurrentPosition + BMovements[i], (*NewTiles)->GetChessPiece());
				GameMode->ValidMoves.Add(RookSingleMove);
			}
			if ((*NewTiles)->GetTileStatus() == ETileStatus::OCCUPIED) break;
			// Cycle to cover all the chess board
			BMovements[i].X == 0 ? 0 : BMovements[i].X > 0 ? BMovements[i].X += 1 : BMovements[i].X -= 1;
			BMovements[i].Y == 0 ? 0 : BMovements[i].Y > 0 ? BMovements[i].Y += 1 : BMovements[i].Y -= 1;
		}
	}
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
