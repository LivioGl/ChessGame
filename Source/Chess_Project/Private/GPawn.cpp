// Fill out your copyright notice in the Description page of Project Settings.

#include "GPawn.h"
#include "MainGameMode.h"

// Sets default values
AGPawn::AGPawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Scene component
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);
	// File Path to assign correct material
	MaterialBlack = TEXT("/Game/Materials/MI_BlackPawn");
	MaterialWhite = TEXT("/Game/Materials/MI_WhitePawn");
	Type = PieceType::PAWN;
}

void AGPawn::GetValidMoves()
{
	// Gamemode and Gamefield reference
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	AGameField* Field = GameMode->Field;
	// Current Pawn position saved in this pointer
	
	//ATile** NewTile;
	ATile** NewTile;
	// Checking the (x, y+1) tile
	NewTile = Field->TileMap.Find(PieceGridPosition+FVector2D(bHumanTeam ? 1 : -1, 0));
	if (NewTile && (*NewTile)->GetTileStatus() == ETileStatus::EMPTY)
	{
		GameMode->ValidMoves.Add(ChessMove(this, PieceGridPosition, (*NewTile)->GetGridPosition(), (*NewTile)->GetChessPiece()));
	}
	// Checking the (x, y+2) tile
	NewTile = Field->TileMap.Find(PieceGridPosition+FVector2D(bHumanTeam ? 2 : -2, 0));
	if (NewTile && (*NewTile)->GetTileStatus() == ETileStatus::EMPTY && this->GetGridPosition().X == (bHumanTeam ? 1 : 6))
	{
		GameMode->ValidMoves.Add(ChessMove(this, PieceGridPosition, (*NewTile)->GetGridPosition(), (*NewTile)->GetChessPiece()));
	}


	// Checking the (x+1, y+1) tile, for capturing enemy pieces
	NewTile = Field->TileMap.Find(PieceGridPosition+FVector2D(bHumanTeam ? 1 : -1, 1));
	if (NewTile && (*NewTile)->GetTileStatus() == ETileStatus::OCCUPIED && (*NewTile)->GetChessPiece()->bHumanTeam != this->bHumanTeam)
	{
		GameMode->ValidMoves.Add(ChessMove(this, PieceGridPosition, (*NewTile)->GetGridPosition(), (*NewTile)->GetChessPiece()));
	}
	// Checking the (x-1, y+1) tile, for capturing enemy pieces
	NewTile = Field->TileMap.Find(PieceGridPosition+FVector2D(bHumanTeam ? 1 : -1, -1));
	if (NewTile && (*NewTile)->GetTileStatus() == ETileStatus::OCCUPIED && (*NewTile)->GetChessPiece()->bHumanTeam != this->bHumanTeam)
	{
		GameMode->ValidMoves.Add(ChessMove(this, PieceGridPosition, (*NewTile)->GetGridPosition(), (*NewTile)->GetChessPiece()));
	}
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

