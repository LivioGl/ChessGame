// Fill out your copyright notice in the Description page of Project Settings.


#include "GameField.h"

// Sets default values
AGameField::AGameField()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Dimensions of the field
	Size = 8;
	TileSize = 120;
	PieceSize = 110;
}

void AGameField::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called when the game starts or when spawned
void AGameField::BeginPlay()
{
	Super::BeginPlay();
	GenerateField();
	SpawnPieces();
	
}


void AGameField::GenerateField()
{
	for (int32 x = 0; x < Size; x++)
	{
		for (int32 y = 0; y < Size; y++)
		{
			FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
			ATile* Obj;
			if ((x + y) % 2 == 0)
			{
				Obj = GetWorld()->SpawnActor<ATile>(TileClassBlack, Location, FRotator::ZeroRotator);
			}
			else
			{
				Obj = GetWorld()->SpawnActor<ATile>(TileClassWhite, Location, FRotator::ZeroRotator);
			}
			const float TileScale = TileSize / 100;
			
			Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.2));
			Obj->SetGridPosition(x, y);
			TileArray.Add(Obj);
			TileMap.Add(FVector2D(x, y), Obj);
		}
	}

}

void AGameField::SpawnPieces() 
{
	// Inizio spawn pedine
	// Parto dalla riga di pedoni bianchi
	for (int32 b = 0; b < 8; b++)
	{
		// Pointer to GameField 
		// Tiene la posizione delle pedine nella seconda riga
		FVector Location = AGameField::GetRelativeLocationByXYPosition(1, b);
		AGPawn* Pawn;
		Pawn = GetWorld()->SpawnActor<AGPawn>(GPawn, Location, FRotator::ZeroRotator);
		const float PawnScale = PieceSize / 100;
		Pawn->SetActorScale3D(FVector(PawnScale, PawnScale, 0.2));
		Pawn->SetGridPosition(1, b);
		// ChangeMaterial("MI_WhitePawn", Pawn);
	}
	
}

void AGameField::ChangeMaterial(FString F, AGPawn* P) 
{
	UMaterialInterface* Material = Cast<UMaterialInterface>(StaticLoadObject(NULL, nullptr, *("/Game/Materials/" + F)));
	// Problema funzione GetStatMeshComp()
	UStaticMeshComponent* Comp = P->GetStatMeshComp();
	Comp->SetMaterial(0, Material);
	
}


TArray<ATile*>& AGameField::GetTileArray()
{
	return TileArray;
}

FVector AGameField::GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const
{
	return TileSize * FVector(InX, InY, 0);

}

FVector2D AGameField::GetXYPositionByRelativeLocation(const FVector& Location) const
{
	const double x = Location[0] / (TileSize);
	const double y = Location[1] / (TileSize);
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("x=%f,y=%f"), x, y));
	return FVector2D(x, y);
}

inline bool AGameField::IsValidPosition(const FVector2D Position) const
{
	return 0 <= Position[0] && Position[0] < Size && 0 <= Position[1] && Position[1] < Size;
}

// Called every frame
/*
void AGameField::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

