// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

#include "ChessPiece.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Scene component
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);

	Status = ETileStatus::EMPTY;
	Piece = nullptr;
	PlayerOwner = -1;
	TileGridPosition = FVector2D(0, 0);

}


void ATile::SetTileStatus(const int32 TileOwner, const ETileStatus TileStatus)
{
	PlayerOwner = TileOwner;
	Status = TileStatus;
}

ETileStatus ATile::GetTileStatus()
{
	return Status;
}

int32 ATile::GetOwner()
{
	return PlayerOwner;
}

AChessPiece* ATile::GetChessPiece()
{
	return Piece;
}

void ATile::SetChessPiece(AChessPiece* NewPiece)
{
	Piece = NewPiece;
	Status = NewPiece == nullptr ? ETileStatus::EMPTY : ETileStatus::OCCUPIED;
	PlayerOwner = NewPiece == nullptr ? -1 : NewPiece->bHumanTeam;
}

void ATile::SetGridPosition(const double InX, const double InY)
{
	TileGridPosition.Set(InX, InY);
}

FVector2D ATile::GetGridPosition()
{
	return TileGridPosition;
}

UStaticMeshComponent* ATile::GetStatMeshComp() 
{
	return StaticMeshComponent;
}

void ATile::ResetMaterial()
{
	bool bIsWhite = ((int)(this->GetGridPosition().X + this->GetGridPosition().Y) % 2) == 1;

	UMaterialInterface* Material = Cast<UMaterialInterface>(StaticLoadObject(NULL, nullptr, bIsWhite ? *White : *Black));
	UStaticMeshComponent* StatMeshComp = this->GetStatMeshComp();
	StatMeshComp->SetMaterial(0, Material);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

