// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPiece.h"

// Sets default values
AChessPiece::AChessPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MoveHint = TEXT("/Game/Materials/MoveHint");
}

// Called when the game starts or when spawned
void AChessPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChessPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AChessPiece::GetValidMoves() {}

FVector2D AChessPiece::GetGridPosition()
{
	return PieceGridPosition;
}

void AChessPiece::SetGridPosition(const double InX, const double InY)
{
	PieceGridPosition.Set(InX, InY);
}

void AChessPiece::SetGridPosition(FVector2D NewPosition)
{
	this->SetGridPosition(NewPosition.X, NewPosition.Y);
}

UStaticMeshComponent* AChessPiece::GetStatMeshComp()
{
	return StaticMeshComponent;
}