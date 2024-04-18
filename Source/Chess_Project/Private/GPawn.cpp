// Fill out your copyright notice in the Description page of Project Settings.

#include "GPawn.h"
#include "MainGameMode.h"

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

void AGPawn::ValidMoves()
{
	// Gamemode and Gamefield reference
	AMainGameMode* GameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());
	AGameField* Field = GameMode->Field;
	// Current Pawn position saved in this pointer
	FVector2D PawnCurrentPosition(PieceGridPosition.X, PieceGridPosition.Y);
	
	ATile* NewTile;
	// Checking the (x, y+1) tile
	NewTile = Field->TileMap[(PawnCurrentPosition)+FVector2D(0, HumanTeam ? 1 : -1)];
	if (NewTile && NewTile->GetTileStatus() == ETileStatus::EMPTY)
	{
		GameMode->ValidMoves.Add(ChessMove(this, PawnCurrentPosition, NewTile->GetGridPosition()));
	}
	// Checking the (x, y+2) tile
	NewTile = Field->TileMap[(PawnCurrentPosition)+FVector2D(0, HumanTeam ? 2 : -2)];
	if (NewTile && NewTile->GetTileStatus() == ETileStatus::EMPTY && this->GetGridPosition().Y == (HumanTeam ? 1 : 6))
	{
		GameMode->ValidMoves.Add(ChessMove(this, PawnCurrentPosition, NewTile->GetGridPosition()));
	}
	// Checking the (x+1, y+1) tile, for capturing enemy pieces
	NewTile = Field->TileMap[(PawnCurrentPosition)+FVector2D(HumanTeam ? 1 : -1, HumanTeam ? 1 : -1)];
	if (NewTile && NewTile->GetTileStatus() == ETileStatus::OCCUPIED && NewTile->GetChessPiece()->HumanTeam != this->HumanTeam)
	{
		GameMode->ValidMoves.Add(ChessMove(this, PawnCurrentPosition, NewTile->GetGridPosition()));
	}
	// Checking the (x-1, y+1) tile, for capturing enemy pieces
	NewTile = Field->TileMap[(PawnCurrentPosition)+FVector2D(HumanTeam ? -1 : 1, HumanTeam ? 1 : -1)];
	if (NewTile && NewTile->GetTileStatus() == ETileStatus::OCCUPIED && NewTile->GetChessPiece()->HumanTeam != this->HumanTeam)
	{
		GameMode->ValidMoves.Add(ChessMove(this, PawnCurrentPosition, NewTile->GetGridPosition()));
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

