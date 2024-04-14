// Fill out your copyright notice in the Description page of Project Settings.


#include "Queen.h"

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

TArray<ATile*> AQueen::QueenValidMoves()
{
	// FVector PawnPossibleMoves = AGameField::GetRelativeLocationByXYPosition(x, y)
	// new possible positions : starting from(x, y), queen can move to :
	// 0 < i < 8
	// (x-i, y-i), (x-i, y+i), (x+i, y+i), (x+i, y-i), (x, y-i), (x, y+i), (x-i, y), (x+i, y)
	// 
	// GetTileStatus
	// Move to TileGridPosition
	// Get pointer to Tiles which represent a legal move
	return TArray<ATile*>();
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

//UStaticMeshComponent* AQueen::GetStatMeshComp()
//{
//	return StaticMeshComponent;
//}