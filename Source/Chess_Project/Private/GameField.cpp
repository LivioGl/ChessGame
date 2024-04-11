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


// Assigning material function

void AGameField::ChangeMaterial(AChessPiece* S, bool IsBlack)
{
	UMaterialInterface* Material = Cast<UMaterialInterface>(StaticLoadObject(NULL, nullptr, IsBlack ? *S->MaterialBlack : *S->MaterialWhite));
	UStaticMeshComponent* Comp = S->GetStatMeshComp();
	Comp->SetMaterial(0, Material);
}

void AGameField::GenerateField()
{
	// Spawning Tile

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
	// Spawning White Pawns
	for (int32 b = 0; b < 8; b++)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(1, b);
		AGPawn* Pawn;
		Pawn = GetWorld()->SpawnActor<AGPawn>(GPawn, Location, FRotator::ZeroRotator);
		const float PieceScale = PieceSize / 100;
		Pawn->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		Pawn->SetGridPosition(1, b);
		ChangeMaterial(Pawn, false);
	}
	// Spawning Black Pawns
	for (int32 b = 0; b < 8; b++)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(6, b);
		AGPawn* Pawn;
		Pawn = GetWorld()->SpawnActor<AGPawn>(GPawn, Location, FRotator::ZeroRotator);
		const float PieceScale = PieceSize / 100;
		Pawn->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		Pawn->SetGridPosition(6, b);
		ChangeMaterial(Pawn, true);
	}
	// Spawning White Bishops
	for (int32 b = 2; b < 6; b+=3)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(0, b);
		ABishop* PBishop;
		PBishop = GetWorld()->SpawnActor<ABishop>(Bishop, Location, FRotator::ZeroRotator);
		const float PieceScale = PieceSize / 100;
		PBishop->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		PBishop->SetGridPosition(0, b);
		ChangeMaterial(PBishop, false);
	}
	// Spawning Black Bishops
	for (int32 b = 2; b < 6; b += 3)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(7, b);
		ABishop* PBishop;
		PBishop = GetWorld()->SpawnActor<ABishop>(Bishop, Location, FRotator::ZeroRotator);
		const float PieceScale = PieceSize / 100;
		PBishop->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		PBishop->SetGridPosition(7, b);
		ChangeMaterial(PBishop, true);
	}
	// Spawning White Rooks
	for (int32 b = 0; b < 9; b += 7)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(0, b);
		ARook* Rook1;
		Rook1 = GetWorld()->SpawnActor<ARook>(Rook, Location, FRotator::ZeroRotator);
		const float PieceScale = PieceSize / 100;
		Rook1->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		Rook1->SetGridPosition(0, b);
		ChangeMaterial(Rook1, false);
	}
	// Spawning Black Rooks
	for (int32 b = 0; b < 9; b += 7)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(7, b);
		ARook* Rook2;
		Rook2 = GetWorld()->SpawnActor<ARook>(Rook, Location, FRotator::ZeroRotator);
		const float PieceScale = PieceSize / 100;
		Rook2->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		Rook2->SetGridPosition(0, b);
		ChangeMaterial(Rook2, true);
	}
	// Spawning White King
	FVector Location1 = AGameField::GetRelativeLocationByXYPosition(0, 4);
	AKing* King1;
	King1 = GetWorld()->SpawnActor<AKing>(King, Location1, FRotator::ZeroRotator);
	const float PieceScale = PieceSize / 100;
	King1->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
	King1->SetGridPosition(0, 4);
	ChangeMaterial(King1, false);
	// Spawning Black King
	FVector Location2 = AGameField::GetRelativeLocationByXYPosition(7, 4);
	AKing* King2;
	King2 = GetWorld()->SpawnActor<AKing>(King, Location2, FRotator::ZeroRotator);
	King2->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
	King2->SetGridPosition(7, 4);
	ChangeMaterial(King2, true);
	
	// Spawning White Queen
	FVector Location3 = AGameField::GetRelativeLocationByXYPosition(0, 3);
	AQueen* Queen1;
	Queen1 = GetWorld()->SpawnActor<AQueen>(Queen, Location3, FRotator::ZeroRotator);
	Queen1->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
	Queen1->SetGridPosition(0, 3);
	ChangeMaterial(Queen1, false);
	// Spawning Black Queen
	FVector Location4 = AGameField::GetRelativeLocationByXYPosition(7, 3);
	AQueen* Queen2;
	Queen2 = GetWorld()->SpawnActor<AQueen>(Queen, Location4, FRotator::ZeroRotator);
	Queen2->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
	Queen2->SetGridPosition(7, 3);
	ChangeMaterial(Queen2, true);
	// Spawning White Knights
	for (int32 b = 1; b < 7; b += 5)
	{
		FVector Location5 = AGameField::GetRelativeLocationByXYPosition(0, b);
		AKnight* Knight1;
		Knight1 = GetWorld()->SpawnActor<AKnight>(Knight, Location5, FRotator::ZeroRotator);
		Knight1->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		Knight1->SetGridPosition(0, b);
		ChangeMaterial(Knight1, false);
	}
	// Spawning Black Knights
	for (int32 b = 1; b < 7; b += 5)
	{
		FVector Location6 = AGameField::GetRelativeLocationByXYPosition(7, b);
		AKnight* Knight2;
		Knight2 = GetWorld()->SpawnActor<AKnight>(Knight, Location6, FRotator::ZeroRotator);
		Knight2->SetActorScale3D(FVector(PieceScale, PieceScale, 0.2));
		Knight2->SetGridPosition(7, b);
		ChangeMaterial(Knight2, true);
	}
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

