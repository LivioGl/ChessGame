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
	TArray<FString> StringMaterials = {TEXT("MI_WhitePawn"), TEXT("MI_BlackPawn"), TEXT("MI_WhiteBishop"), TEXT("MI_BlackBishop"), TEXT("MI_WhiteRook"), TEXT("MI_BlackRook")};
	// Spawning White Pawns
	for (int32 b = 0; b < 8; b++)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(1, b);
		AGPawn* Pawn;
		Pawn = GetWorld()->SpawnActor<AGPawn>(GPawn, Location, FRotator::ZeroRotator);
		const float PawnScale = PieceSize / 100;
		Pawn->SetActorScale3D(FVector(PawnScale, PawnScale, 0.2));
		Pawn->SetGridPosition(1, b);
		ChangeMaterialPawn(StringMaterials[0], Pawn);
	}
	// Spawning Black Pawns
	for (int32 b = 0; b < 8; b++)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(6, b);
		AGPawn* Pawn;
		Pawn = GetWorld()->SpawnActor<AGPawn>(GPawn, Location, FRotator::ZeroRotator);
		const float PawnScale = PieceSize / 100;
		Pawn->SetActorScale3D(FVector(PawnScale, PawnScale, 0.2));
		Pawn->SetGridPosition(6, b);
		ChangeMaterialPawn(StringMaterials[1], Pawn);
	}
	// Spawning White Bishops
	for (int32 b = 2; b < 6; b+=3)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(0, b);
		ABishop* PBishop;
		PBishop = GetWorld()->SpawnActor<ABishop>(Bishop, Location, FRotator::ZeroRotator);
		const float PawnScale = PieceSize / 100;
		PBishop->SetActorScale3D(FVector(PawnScale, PawnScale, 0.2));
		PBishop->SetGridPosition(0, b);
		ChangeMaterialBishop(StringMaterials[2], PBishop);
	}
	// Spawning Black Bishops
	for (int32 b = 2; b < 6; b += 3)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(7, b);
		ABishop* PBishop;
		PBishop = GetWorld()->SpawnActor<ABishop>(Bishop, Location, FRotator::ZeroRotator);
		const float PawnScale = PieceSize / 100;
		PBishop->SetActorScale3D(FVector(PawnScale, PawnScale, 0.2));
		PBishop->SetGridPosition(7, b);
		ChangeMaterialBishop(StringMaterials[3], PBishop);
	}
	// Spawning White Rooks
	for (int32 b = 0; b < 9; b += 7)
	{
		FVector Location = AGameField::GetRelativeLocationByXYPosition(0, b);
		ARook* PRook;
		PRook = GetWorld()->SpawnActor<ARook>(Rook, Location, FRotator::ZeroRotator);
		const float PawnScale = PieceSize / 100;
		PRook->SetActorScale3D(FVector(PawnScale, PawnScale, 0.2));
		PRook->SetGridPosition(0, b);
	}
}

void AGameField::ChangeMaterialPawn(FString F, AGPawn* P) 
{
	UMaterialInterface* Material = Cast<UMaterialInterface>(StaticLoadObject(NULL, nullptr, *("/Game/Materials/" + F)));
	UStaticMeshComponent* Comp = P->GetStatMeshComp();
	Comp->SetMaterial(0, Material);
}
void AGameField::ChangeMaterialBishop(FString F, ABishop* B)
{
	UMaterialInterface* Material = Cast<UMaterialInterface>(StaticLoadObject(NULL, nullptr, *("/Game/Materials/" + F)));
	UStaticMeshComponent* Comp = B->GetStatMeshComp();
	Comp->SetMaterial(0, Material);
}
/*
void AGameField::ChangeMaterial(FString F, TSubclassOf<AChessPiece>* S)
{
	UMaterialInterface* Material = Cast<UMaterialInterface>(StaticLoadObject(NULL, nullptr, *("/Game/Materials/" + F)));

	UStaticMeshComponent* Comp = S->GetStatMeshComp(S);
	Comp->SetMaterial(0, Material);
}
*/
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

